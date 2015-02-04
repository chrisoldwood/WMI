////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_Process.cpp
//! \brief  The Win32_Process class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Win32_Process.hpp"
#include "Exception.hpp"

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

////////////////////////////////////////////////////////////////////////////////
//! Terminate the process.

uint32 Win32_Process::Terminate(uint32 reason)
{
	const tchar* TERMINATE = TXT("Terminate");

	IWbemClassObjectPtr arguments = createArgumentsObject(WMI_CLASS_NAME, TERMINATE);

	setArgument(arguments, TXT("Reason"), WCL::Variant((int32)reason));

	WCL::Variant returnValue;

	execMethod(TERMINATE, arguments, returnValue);

	return WCL::getValue<uint32>(WCL::Variant(returnValue, VT_UI4));
}

//namespace WMI
}
