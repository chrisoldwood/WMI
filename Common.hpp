////////////////////////////////////////////////////////////////////////////////
//! \file   Common.hpp
//! \brief  Wrapper to include the most common WMI library headers.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_COMMON_HPP
#define WMI_COMMON_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
// Library documentation
//
//! \namespace WMI
//! \brief     The Windows Management Instrumentation namespace.
//!
//! \mainpage  Windows Management Instrumentation C++ Library
//! \section   introduction Introduction
//! This library is a Wrapper Facade for using the WMI COM library.

////////////////////////////////////////////////////////////////////////////////
// Standard headers.

#include <Core/Common.hpp>		// Core library common headers.
#include <WCL/Common.hpp>		// Windows C++ library common headers.

////////////////////////////////////////////////////////////////////////////////
// Library headers.

#include "Types.hpp"

#endif // WMI_COMMON_HPP
