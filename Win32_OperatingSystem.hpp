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
#include <Core/StringUtils.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The C++ facade for the Win32_OperatingSystem WMI class.

class Win32_OperatingSystem : public TypedObject<Win32_OperatingSystem>
{
public:
	//! Construction from the underlying COM object and connection.
	Win32_OperatingSystem(IWbemClassObjectPtr object, const Connection& connection);

	//! Destructor.
	virtual ~Win32_OperatingSystem();

	//
	// WMI typed properties.
	//

	//! Operating system was last booted.
	CDateTime LastBootUpTime() const;

	//! Number of kilobytes of virtual memory currently unused and available.
	uint64 FreeVirtualMemory() const;

	//! Operating system instance within a computer system.
	tstring Name() const;

	//! Number of kilobytes of virtual memory.
	uint64 TotalVirtualMemorySize() const;

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
//! Number of kilobytes of virtual memory currently unused and available.

inline uint64 Win32_OperatingSystem::FreeVirtualMemory() const
{
	tstring value = getProperty<tstring>(TXT("FreeVirtualMemory"));

	return Core::parse<uint64>(value);
}

////////////////////////////////////////////////////////////////////////////////
//! Operating system instance within a computer system.

inline tstring Win32_OperatingSystem::Name() const
{
	return getProperty<tstring>(TXT("Name"));
}

////////////////////////////////////////////////////////////////////////////////
//! Number of kilobytes of virtual memory.

inline uint64 Win32_OperatingSystem::TotalVirtualMemorySize() const
{
	tstring value = getProperty<tstring>(TXT("TotalVirtualMemorySize"));

	return Core::parse<uint64>(value);
}

//namespace WMI
}

#endif // WMI_WIN32_OPERATINGSYSTEM_HPP
