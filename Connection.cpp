////////////////////////////////////////////////////////////////////////////////
//! \file   Connection.cpp
//! \brief  The Connection class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Connection.hpp"
#include <WCL/ComStr.hpp>
#include "Exception.hpp"
#include <Core/StringUtils.hpp>

#ifdef _MSC_VER
// Add .lib to linker.
#pragma comment(lib, "wbemuuid.lib")
#endif

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
// Constants.

//! The local computer path.
const tstring Connection::LOCALHOST = TXT(".");
//! The default namespace.
const tstring Connection::DEFAULT_NAMESPACE = TXT("\\root\\cimv2");

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
	open(LOCALHOST, TXT(""), TXT(""), DEFAULT_NAMESPACE);
}

////////////////////////////////////////////////////////////////////////////////
//! Open a connection to a specific host using the current credentials.

void Connection::open(const tstring& host)
{
	open(host, TXT(""), TXT(""), DEFAULT_NAMESPACE);
}

////////////////////////////////////////////////////////////////////////////////
//! Open a connection to a specific host.

void Connection::open(const tstring& host, const tstring& login, const tstring& password)
{
	open(host, login, password, DEFAULT_NAMESPACE);
}

////////////////////////////////////////////////////////////////////////////////
//! Open a connection to a specific host and namespace.

void Connection::open(const tstring& host, const tstring& login, const tstring& password, const tstring& nmspace)
{
	ASSERT(!isOpen());

	// Format the full connection path.
	tstring path = host + nmspace;

	if (path.compare(0, 2, TXT("\\\\")) != 0)
		path = TXT("\\\\") + path;

	// Create the connection.
	IWbemServicesPtr	services;
	IWbemLocatorPtr		locator(CLSID_WbemLocator);
	WCL::ComStr			bstrPath(path);
	WCL::ComStr			bstrAuth(TXT(""));
	HRESULT				result;

	if (login.empty())
	{
		result = locator->ConnectServer(bstrPath.Get(), nullptr, nullptr, nullptr, 0,
										bstrAuth.Get(), nullptr, AttachTo(services));
	}
	else
	{
		WCL::ComStr	bstrLogin(login);
		WCL::ComStr	bstrPassword(password);

		result = locator->ConnectServer(bstrPath.Get(), bstrLogin.Get(), bstrPassword.Get(), nullptr, 0,
										bstrAuth.Get(), nullptr, AttachTo(services));
	}

	if (FAILED(result))
		throw Exception(result, locator, Core::fmt(TXT("Failed to connect to the WMI provider on '%s'"), host.c_str()).c_str());

	// Enable impersonation on the connection.
    result = ::CoSetProxyBlanket(services.get(), RPC_C_AUTHN_DEFAULT, RPC_C_AUTHZ_DEFAULT, nullptr,
									RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
									nullptr, EOAC_NONE);

	if (FAILED(result))
		throw Exception(result, locator, TXT("Failed to enable impersonation on the WMI connection"));

	// Update state.
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

ObjectIterator Connection::execQuery(const tchar* query)
{
	ASSERT(isOpen());

	WCL::ComStr	language(L"WQL");
	WCL::ComStr	queryText(query);
	long		flags(WBEM_FLAG_RETURN_IMMEDIATELY | WBEM_FLAG_FORWARD_ONLY);

	IEnumWbemClassObjectPtr enumerator;

	// Execute it.
	HRESULT result = m_services->ExecQuery(language.Get(), queryText.Get(), flags,
											nullptr, AttachTo(enumerator));

	if (FAILED(result))
		throw Exception(result, m_services, TXT("Failed to execute a WMI query"));

	return ObjectIterator(enumerator);
}

//namespace WMI
}
