////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_Service.cpp
//! \brief  The Win32_Service class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Win32_Service.hpp"

namespace WMI
{

//! The WMI class name this type mirrors.
const tchar* Win32_Service::WMI_CLASS_NAME = TXT("Win32_Service");

////////////////////////////////////////////////////////////////////////////////
//! Construction from the underlying COM object.

Win32_Service::Win32_Service(IWbemClassObjectPtr object)
	: TypedObject<Win32_Service>(object)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Win32_Service::~Win32_Service()
{
}

//namespace WMI
}
