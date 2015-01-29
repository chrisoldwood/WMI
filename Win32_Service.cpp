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
//! Construction from the underlying COM object and connection.

Win32_Service::Win32_Service(IWbemClassObjectPtr object, const Connection& connection)
	: TypedObject<Win32_Service>(object, connection)
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Win32_Service::~Win32_Service()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Start the service.

uint32 Win32_Service::StartService()
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
//! Stop the service.

uint32 Win32_Service::StopService()
{
	WCL::Variant returnValue;

	execMethod(TXT("StopService"), returnValue);

	return WCL::getValue<uint32>(WCL::Variant(returnValue, VT_UI4));
}

//namespace WMI
}
