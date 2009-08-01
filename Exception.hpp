////////////////////////////////////////////////////////////////////////////////
//! \file   Exception.hpp
//! \brief  The Exception class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_EXCEPTION_HPP
#define WMI_EXCEPTION_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/ComException.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The exception type thrown by the WMI library.

class Exception : public WCL::ComException
{
public:
	//! Construction from a non-IErrorInfo supported error.
	Exception(HRESULT result, const tchar* operation);

	//! Construction from an IErrorInfo supported error.
	template<typename T>
	Exception(HRESULT result, WCL::IFacePtr<T>& object, const tchar* operation);

	//! Destructor.
	virtual ~Exception() throw();
	
private:
	//
	// Internal methods.
	//

	//! Format the error using the WMI or IErrorInfo details.
	void formatError(HRESULT result, IUnknown* object, const IID& iid, const tchar* operation);

	//! Format the WMI specific HRESULT error.
	tstring formatWmiError(HRESULT error);
};

////////////////////////////////////////////////////////////////////////////////
//! Construction from an IErrorInfo supported error.

template<typename T>
inline Exception::Exception(HRESULT result, WCL::IFacePtr<T>& object, const tchar* operation)
	: WCL::ComException(result)
{
	formatError(result, object.get(), WCL::IFaceTraits<T>::uuidof(), operation);
}

//namespace WMI
}

#endif // WMI_EXCEPTION_HPP
