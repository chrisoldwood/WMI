////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.cpp
//! \brief  The Exception class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Exception.hpp"
#include <WCL/ComPtr.hpp>
#include <WCL/ComStr.hpp>
#include <wbemidl.h>
#include <WCL/StrCvt.hpp>
#include <Core/StringUtils.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! Construction from a non-IErrorInfo supported error.

Exception::Exception(HRESULT result, const tchar* operation)
	: WCL::ComException(result, operation)
{
}


////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Exception::~Exception() throw()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Format the error using the WMI or IErrorInfo details.

void Exception::formatError(HRESULT result, IUnknown* object, const IID& iid, const tchar* operation)
{
	tstring wmiText(formatWmiError(result));

	if (!wmiText.empty())
	{
		m_details = Core::fmt(TXT("%s [0x%08X - %s]"), operation, result, wmiText.c_str());
	}
	else
	{
		tstring source;
		tstring description;

		// Query for IErrorInfo details.
		extractErrorInfo(object, iid, source, description);

		tstring resultCode(CStrCvt::FormatError(result));

		// Format the error string.
		if (!source.empty() || !description.empty())
			m_details = Core::fmt(TXT("%s [0x%08X - %s] {%s : %s}"), operation, result, resultCode.c_str(), source.c_str(), description.c_str());
		else
			m_details = Core::fmt(TXT("%s [0x%08X - %s]"), operation, result, resultCode.c_str());
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Format the WMI specific HRESULT error.

tstring Exception::formatWmiError(HRESULT error)
{
	typedef WCL::ComPtr<IWbemStatusCodeText> IWbemStatusCodeTextPtr;
	
	WCL::ComStr text;

	// Use the WMI error lookup first.
	IWbemStatusCodeTextPtr converter(CLSID_WbemStatusCodeText);

	HRESULT result = converter->GetErrorCodeText(error, 0, 0, AttachTo(text));

	if (SUCCEEDED(result))
		return Core::trimCopy(W2T(text.Get()));

	// Fallback to using the standard error formatter.
	return tstring(CStrCvt::FormatError(error));
}

//namespace WMI
}
