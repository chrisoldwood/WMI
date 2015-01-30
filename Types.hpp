////////////////////////////////////////////////////////////////////////////////
//! \file   Types.hpp
//! \brief  Common typedefs.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_TYPES_HPP
#define WMI_TYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/ComPtr.hpp>
#include <wbemidl.h>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
// The reference counted smart-pointer types for the WMI COM interfaces.

//! The WMI Locator COM interface.
typedef WCL::ComPtr<IWbemLocator> IWbemLocatorPtr;
//! The WMI Conection COM interface.
typedef WCL::ComPtr<IWbemServices> IWbemServicesPtr;
//! The underlying WMI iterator type.
typedef WCL::ComPtr<IEnumWbemClassObject> IEnumWbemClassObjectPtr;
//! The WMI object type.
typedef WCL::ComPtr<IWbemClassObject> IWbemClassObjectPtr;

//namespace WMI
}

#endif // WMI_TYPES_HPP
