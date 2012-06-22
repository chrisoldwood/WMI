////////////////////////////////////////////////////////////////////////////////
//! \file   DateTime.hpp
//! \brief  Helper functions for parsing WMI datetime values.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef WMI_DATETIME_HPP
#define WMI_DATETIME_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/DateTime.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
// Try and convert a string into a datetime. The format of a WMI datetime is:-
// YYYYMMDDHHMMSS.FFFFFF+TZO e.g. 20101008181758.546000+060

bool tryParseDateTime(const tstring& value, CDateTime& datetime, tstring& offset);

////////////////////////////////////////////////////////////////////////////////
// Convert a string into a datetime or throw an exception if the format is
// invalid.

CDateTime parseDateTime(const tstring& value); // throws(Core::ParseException)

//namespace WMI
}

#endif // WMI_DATETIME_HPP
