////////////////////////////////////////////////////////////////////////////////
//! \file   Connection.hpp
//! \brief  The Connection class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_CONNECTION_HPP
#define WMI_CONNECTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "Types.hpp"
#include <WCL/Variant.hpp>

namespace WMI
{

// Forward declarations.
class ObjectIterator;

////////////////////////////////////////////////////////////////////////////////
//! A connection to the WMI provider on a host.

class Connection
{
public:
	//! Default constructor.
	Connection();

	//! Open a connection to a specific host using the current credentials.
	Connection(const tstring& host); // throw(WMI::Exception)

	//! Destructor.
	~Connection();
	
	//
	// Properties.
	//

	//! Query if the connection is open.
	bool isOpen() const;

	//! Get the underlying COM connection.
	IWbemServicesPtr get() const;

	//
	// Methods.
	//

	//! Open a connection to the current host.
	void open(); // throw(WMI::Exception)

	//! Open a connection to a specific host using the current credentials.
	void open(const tstring& host); // throw(WMI::Exception)

	//! Open a connection to a specific host.
	void open(const tstring& host, const tstring& login, const tstring& password); // throw(WMI::Exception)

	//! Open a connection to a specific host and namespace.
	void open(const tstring& host, const tstring& login, const tstring& password, const tstring& nmspace); // throw(WMI::Exception)

	//! Close the connection.
	void close();

	//! Execute the query.
	ObjectIterator execQuery(const tchar* query) const; // throw(WMI::Exception)

	//
	// Methods.
	//

	//! Execute a method on an object.
	static void execMethod(IWbemServicesPtr connection, IWbemClassObjectPtr object,
							const tchar* path, const tchar* method, WCL::Variant& returnValue); // throw(WMI::Exception)

	//
	// Constants.
	//

	//! The local computer path.
	static const tstring LOCALHOST;
	//! The default namespace.
	static const tstring DEFAULT_NAMESPACE;

private:
	//
	// Members.
	//
	IWbemLocatorPtr				m_locator;		//!< The underlyng WMI locator.
	mutable IWbemServicesPtr	m_services;		//!< The underlying WMI connection.
};

////////////////////////////////////////////////////////////////////////////////
//! Get the underlying COM connection.

inline IWbemServicesPtr Connection::get() const
{
	return m_services;
}

//namespace WMI
}

#endif // WMI_CONNECTION_HPP
