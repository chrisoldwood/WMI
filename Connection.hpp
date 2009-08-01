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

#include <WCL/ComPtr.hpp>
#include <wbemidl.h>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! A connection to the WMI provider on a host.

class Connection
{
public:
	//! Default constructor.
	Connection();

	//! Destructor.
	~Connection();
	
	//
	// Properties.
	//

	//! Query if the connection is open.
	bool isOpen() const;

	//
	// Methods.
	//

	//! Open a connection to the current host.
	void open(); // throw(WMI::Exception)

	//! Open a connection to a specific host and namespace.
	void open(const tstring& host, const tstring& nmspace); // throw(WMI::Exception)

	//! Close the connection.
	void close();

	//! Execute the query.
	void execQuery(const tchar* query); // throw(WMI::Exception)

	//
	// Constants.
	//

	//! The local computer path.
	static const tstring LOCALHOST;
	//! The default namespace.
	static const tstring DEFAULT_NAMESPACE;

private:
	//! The WMI Locator COM interface.
	typedef WCL::ComPtr<IWbemLocator> IWbemLocatorPtr;
	//! The WMI Conection COM interface.
	typedef WCL::ComPtr<IWbemServices> IWbemServicesPtr;
	//! The WMI query result type.
	typedef WCL::ComPtr<IEnumWbemClassObject> IEnumWbemClassObjectPtr;

	//
	// Members.
	//
	IWbemLocatorPtr		m_locator;		//!< The underlyng WMI locator.
	IWbemServicesPtr	m_services;		//!< The underlying WMI connection.
};

//namespace WMI
}

#endif // WMI_CONNECTION_HPP
