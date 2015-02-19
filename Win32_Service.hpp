////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_Service.hpp
//! \brief  The Win32_Service class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_WIN32_SERVICE_HPP
#define WMI_WIN32_SERVICE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "TypedObject.hpp"

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The C++ facade for the Win32_Service WMI class.

class Win32_Service : public TypedObject<Win32_Service>
{
public:
	//! Construction from the underlying COM object and connection.
	Win32_Service(IWbemClassObjectPtr object, const Connection& connection);

	//! Destructor.
	virtual ~Win32_Service();

	//
	// WMI typed properties.
	//

	//! The description of the service.
	tstring Description() const;

	//! The display name of the service.
	tstring DisplayName() const;

	//! The unique name of the service.
	tstring Name() const;

	//! The type of the service.
	tstring ServiceType() const;

	//! The start mode of the service.
	tstring StartMode() const;

	//! The current state of the service.
	tstring State() const;

	//
	// WMI propety helpers.
	//

	//! Is the service disabled?
	bool IsDisabled() const;

	//! Is the service started manually?
	bool IsManual() const;

	//! Does the service start automatically?
	bool IsAutomatic() const;

	//! Is the service running?
	bool IsStopped() const;

	//! Is the service running?
	bool IsRunning() const;

	//
	// WMI methods.
	//

	//! Start the service.
	uint32 StartService();

	//! Stop the service.
	uint32 StopService();

	//
	// Constants.
	//

	//! The WMI class name this type mirrors.
	static const tchar* WMI_CLASS_NAME;
};

////////////////////////////////////////////////////////////////////////////////
//! The description of the service.

inline tstring Win32_Service::Description() const
{
	return getProperty<tstring>(TXT("Description"));
}

////////////////////////////////////////////////////////////////////////////////
//! The display name of the service.

inline tstring Win32_Service::DisplayName() const
{
	return getProperty<tstring>(TXT("DisplayName"));
}

////////////////////////////////////////////////////////////////////////////////
//! The unique name of the service.

inline tstring Win32_Service::Name() const
{
	return getProperty<tstring>(TXT("Name"));
}

////////////////////////////////////////////////////////////////////////////////
//! The type of the service.

inline tstring Win32_Service::ServiceType() const
{
	return getProperty<tstring>(TXT("ServiceType"));
}

////////////////////////////////////////////////////////////////////////////////
//! The start mode of the service.

inline tstring Win32_Service::StartMode() const
{
	return getProperty<tstring>(TXT("StartMode"));
}

////////////////////////////////////////////////////////////////////////////////
//! The current state of the service.

inline tstring Win32_Service::State() const
{
	return getProperty<tstring>(TXT("State"));
}

////////////////////////////////////////////////////////////////////////////////
//! Is the service disabled?

inline bool Win32_Service::IsDisabled() const
{
	return (StartMode() == TXT("Disabled"));
}

////////////////////////////////////////////////////////////////////////////////
//! Is the service started manually?

inline bool Win32_Service::IsManual() const
{
	return (StartMode() == TXT("Manual"));
}

////////////////////////////////////////////////////////////////////////////////
//! Does the service start automatically?

inline bool Win32_Service::IsAutomatic() const
{
	return (StartMode() == TXT("Auto"));
}

////////////////////////////////////////////////////////////////////////////////
//! Is the service running? 

inline bool Win32_Service::IsStopped() const
{
	return (State() == TXT("Stopped"));
}

////////////////////////////////////////////////////////////////////////////////
//! Is the service running? 

inline bool Win32_Service::IsRunning() const
{
	return (State() == TXT("Running"));
}

//namespace WMI
}

#endif // WMI_WIN32_SERVICE_HPP
