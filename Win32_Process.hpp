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
	//! Construction from the underlying COM object and connection.
	Win32_Process(IWbemClassObjectPtr object, const Connection& connection);

	//! Destructor.
	virtual ~Win32_Process();

	//
	// WMI typed properties.
	//

	//! The command line.
	tstring CommandLine() const;

	//! The number of handles it has open.
	uint32 HandleCount() const;

	//! The name of the process.
	tstring Name() const;

	//! The number of privately allocated pages.
	uint64 PrivatePageCount() const;

	//! The unique ID of the process.
	uint32 ProcessId() const;

	//! The number of threads it has running.
	uint32 ThreadCount() const;

	//! The amount of virtual address space used, in bytes.
	uint64 VirtualSize() const;

	//! The size of its working set, in bytes.
	uint64 WorkingSetSize() const;

	//
	// WMI methods.
	//

	//! Terminate the process.
	uint32 Terminate(uint32 reason = 0);

	//
	// Constants.
	//

	//! The WMI class name this type mirrors.
	static const tchar* WMI_CLASS_NAME;
};

////////////////////////////////////////////////////////////////////////////////
//! The command line.

inline tstring Win32_Process::CommandLine() const
{
	return getProperty<tstring>(TXT("CommandLine"));
}

////////////////////////////////////////////////////////////////////////////////
//! The number of handles it has open.

inline uint32 Win32_Process::HandleCount() const
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
//! The number of privately allocated pages.

inline uint64 Win32_Process::PrivatePageCount() const
{
	// 64-bit values are passed as BSTR values.
	const tstring value = getProperty<tstring>(TXT("PrivatePageCount"));
	return Core::parse<uint64>(value);
}

////////////////////////////////////////////////////////////////////////////////
//! The unique ID of the process.

inline uint32 Win32_Process::ProcessId() const
{
	return getProperty<int32>(TXT("ProcessId"));
}

////////////////////////////////////////////////////////////////////////////////
//! The number of threads it has running.

inline uint32 Win32_Process::ThreadCount() const
{
	return getProperty<int32>(TXT("ThreadCount"));
}

////////////////////////////////////////////////////////////////////////////////
//! The amount of virtual address space used, in bytes.

inline uint64 Win32_Process::VirtualSize() const
{
	// 64-bit values are passed as BSTR values.
	const tstring value = getProperty<tstring>(TXT("VirtualSize"));
	return Core::parse<uint64>(value);
}

////////////////////////////////////////////////////////////////////////////////
//! The size of its working set in bytes.

inline uint64 Win32_Process::WorkingSetSize() const
{
	// 64-bit values are passed as BSTR values.
	const tstring value = getProperty<tstring>(TXT("WorkingSetSize"));
	return Core::parse<uint64>(value);
}

//namespace WMI
}

#endif // WMI_WIN32_PROCESS_HPP
