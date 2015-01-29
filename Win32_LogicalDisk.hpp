////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_LogicalDisk.hpp
//! \brief  The Win32_LogicalDisk class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_WIN32_LOGICALDISK_HPP
#define WMI_WIN32_LOGICALDISK_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "TypedObject.hpp"

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The C++ facade for the Win32_LogicalDisk WMI class.

class Win32_LogicalDisk : public TypedObject<Win32_LogicalDisk>
{
public:
	//! Construction from the underlying COM object and connection.
	Win32_LogicalDisk(IWbemClassObjectPtr object, const Connection& connection);

	//! Destructor.
	virtual ~Win32_LogicalDisk();

	//
	// WMI typed properties.
	//

	//! Unique identifier of the logical disk from other devices on the system.
	tstring DeviceID() const;

	//! Space available on the logical disk.
	uint64 FreeSpace() const;

	//! Size of the disk drive.
	uint64 Size() const;
	
	//
	// Constants.
	//

	//! The WMI class name this type mirrors.
	static const tchar* WMI_CLASS_NAME;
};

////////////////////////////////////////////////////////////////////////////////
//! Unique identifier of the logical disk from other devices on the system.

inline tstring Win32_LogicalDisk::DeviceID() const
{
	return getProperty<tstring>(TXT("DeviceID"));
}

////////////////////////////////////////////////////////////////////////////////
//! Space available on the logical disk.

inline uint64 Win32_LogicalDisk::FreeSpace() const
{
	tstring value = getProperty<tstring>(TXT("FreeSpace"));

	return Core::parse<uint64>(value);
}

////////////////////////////////////////////////////////////////////////////////
//! Size of the disk drive.

inline uint64 Win32_LogicalDisk::Size() const
{
	tstring value = getProperty<tstring>(TXT("Size"));

	return Core::parse<uint64>(value);
}
	
//namespace WMI
}

#endif // WMI_WIN32_LOGICALDISK_HPP
