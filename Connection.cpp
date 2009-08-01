////////////////////////////////////////////////////////////////////////////////
//! \file   Connection.cpp
//! \brief  The Connection class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Connection.hpp"
#include <WCL/ComStr.hpp>
#include "Exception.hpp"
#include <Core/BadLogicException.hpp>

#ifdef _MSC_VER
// Add .lib to linker.
#pragma comment(lib, "wbemuuid.lib")
#endif

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
// Constants.

//! The local computer path.
const tstring Connection::LOCALHOST = TXT("\\\\.");
//! The default namespace.
const tstring Connection::DEFAULT_NAMESPACE = TXT("\\root\\default");

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

Connection::Connection()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Connection::~Connection()
{
	close();
}

////////////////////////////////////////////////////////////////////////////////
//! Query if the connection is open.

bool Connection::isOpen() const
{
	return ((m_locator.get() != nullptr) && (m_services.get() != nullptr));
}

////////////////////////////////////////////////////////////////////////////////
//! Open a connection to the current host.

void Connection::open()
{
	open(LOCALHOST, DEFAULT_NAMESPACE);
}

////////////////////////////////////////////////////////////////////////////////
//! Open a connection to a specific host and namespace.

void Connection::open(const tstring& host, const tstring& nmspace)
{
	// Already open?
	if (isOpen())
		throw Core::BadLogicException(TXT("WMI connection already open"));

	// Create the connection.
	IWbemServicesPtr	services;
	IWbemLocatorPtr		locator(CLSID_WbemAdministrativeLocator);
	WCL::ComStr			path(host + nmspace);

	HRESULT result = locator->ConnectServer(path.Get(), nullptr, nullptr, nullptr, 0, nullptr, nullptr, AttachTo(services));

	if (FAILED(result))
		throw Exception(result, locator, TXT("Failed to connect to the local WMI provider"));

	m_locator  = locator;
	m_services = services;
}

////////////////////////////////////////////////////////////////////////////////
//! Close the connection.

void Connection::close()
{
	m_services.Release();
	m_locator.Release();
}

////////////////////////////////////////////////////////////////////////////////
//! Execute the query.

void Connection::execQuery(const tchar* query)
{
	// Connection open?
	if (!isOpen())
		throw Core::BadLogicException(TXT("WMI connection is closed"));

	WCL::ComStr	language(L"WQL");
	WCL::ComStr	queryText(query);
	long		flags(WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY);

	IEnumWbemClassObjectPtr enumerator;

	// Execute it.
	HRESULT result = m_services->ExecQuery(language.Get(), queryText.Get(), flags,
											nullptr, AttachTo(enumerator));

	if (FAILED(result))
		throw Exception(result, m_services, TXT("Failed to execute a WMI query"));

//	return ResultSet(enumerator);
}

//namespace WMI
}
