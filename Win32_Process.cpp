////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_Process.cpp
//! \brief  The Win32_Process class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Win32_Process.hpp"

namespace WMI
{

//! The WMI class name this type mirrors.
const tchar* Win32_Process::WMI_CLASS_NAME = TXT("Win32_Process");

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object and connection.

Win32_Process::Win32_Process(IWbemClassObjectPtr object, const Connection& connection)
	: TypedObject<Win32_Process>(object, connection)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Win32_Process::~Win32_Process()
{
}

//namespace WMI
}
