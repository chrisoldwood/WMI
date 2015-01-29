////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_LogicalDisk.cpp
//! \brief  The Win32_LogicalDisk class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Win32_LogicalDisk.hpp"

namespace WMI
{

//! The WMI class name this type mirrors.
const tchar* Win32_LogicalDisk::WMI_CLASS_NAME = TXT("Win32_LogicalDisk");

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object and connection.

Win32_LogicalDisk::Win32_LogicalDisk(IWbemClassObjectPtr object, const Connection& connection)
	: TypedObject<Win32_LogicalDisk>(object, connection)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Win32_LogicalDisk::~Win32_LogicalDisk()
{
}

//namespace WMI
}
