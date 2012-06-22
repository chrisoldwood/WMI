////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_OperatingSystem.hpp
//! \brief  The Win32_OperatingSystem class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_WIN32_OPERATINGSYSTEM_HPP
#define WMI_WIN32_OPERATINGSYSTEM_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "TypedObject.hpp"
#include "DateTime.hpp"

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The C++ version of the Win32_OperatingSystem WMI class.

class Win32_OperatingSystem : public TypedObject<Win32_OperatingSystem>
{
public:
	//! Construction from the underlying COM object.
	Win32_OperatingSystem(IWbemClassObjectPtr object);

	//! Destructor.
	virtual ~Win32_OperatingSystem();

	//
	// WMI typed properties.
	//

	//! Operating system was last booted.
	CDateTime LastBootUpTime() const;

	//! Operating system instance within a computer system.
	tstring Name() const;
	
	//
	// Constants.
	//

	//! The WMI class name this type mirrors.
	static const tchar* WMI_CLASS_NAME;
};

////////////////////////////////////////////////////////////////////////////////
//! Operating system was last booted.

inline CDateTime Win32_OperatingSystem::LastBootUpTime() const
{
	return parseDateTime(getProperty<tstring>(TXT("LastBootUpTime")));
}

////////////////////////////////////////////////////////////////////////////////
//! Operating system instance within a computer system.

inline tstring Win32_OperatingSystem::Name() const
{
	return getProperty<tstring>(TXT("Name"));
}
	
//namespace WMI
}

#endif // WMI_WIN32_OPERATINGSYSTEM_HPP
