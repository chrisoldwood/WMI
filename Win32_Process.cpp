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
//! Construction from the underlying COM object.

Win32_Process::Win32_Process(IWbemClassObjectPtr object)
	: TypedObject<Win32_Process>(object)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Win32_Process::~Win32_Process()
{
}

//namespace WMI
}
