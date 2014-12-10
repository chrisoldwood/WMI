////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_Process.hpp
//! \brief  The Win32_Process class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_WIN32_PROCESS_HPP
#define WMI_WIN32_PROCESS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "TypedObject.hpp"
#include "DateTime.hpp"
#include <Core/StringUtils.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! The C++ facade for the Win32_Process WMI class.

class Win32_Process : public TypedObject<Win32_Process>
{
public:
	//! Construction from the underlying COM object.
	Win32_Process(IWbemClassObjectPtr object);

	//! Destructor.
	virtual ~Win32_Process();

	//
	// WMI typed properties.
	//

	//! The number of handles it has open.
	int32 HandleCount() const;

	//! The name of the process.
	tstring Name() const;

	//! The number of threads it has running.
	int32 ThreadCount() const;

	//
	// Constants.
	//

	//! The WMI class name this type mirrors.
	static const tchar* WMI_CLASS_NAME;
};

////////////////////////////////////////////////////////////////////////////////
//! The number of handles it has open.

inline int32 Win32_Process::HandleCount() const
{
	return getProperty<int32>(TXT("HandleCount"));
}

////////////////////////////////////////////////////////////////////////////////
//! The name of the process.

inline tstring Win32_Process::Name() const
{
	return getProperty<tstring>(TXT("Name"));
}

////////////////////////////////////////////////////////////////////////////////
//! The number of threads it has running.

inline int32 Win32_Process::ThreadCount() const
{
	return getProperty<int32>(TXT("ThreadCount"));
}

//namespace WMI
}

#endif // WMI_WIN32_PROCESS_HPP
