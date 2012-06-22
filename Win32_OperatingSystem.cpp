////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_OperatingSystem.cpp
//! \brief  The Win32_OperatingSystem class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Win32_OperatingSystem.hpp"

namespace WMI
{

//! The WMI class name this type mirrors.
const tchar* Win32_OperatingSystem::WMI_CLASS_NAME = TXT("Win32_OperatingSystem");

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object.

Win32_OperatingSystem::Win32_OperatingSystem(IWbemClassObjectPtr object)
	: TypedObject<Win32_OperatingSystem>(object)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Win32_OperatingSystem::~Win32_OperatingSystem()
{
}

//namespace WMI
}
