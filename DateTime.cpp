////////////////////////////////////////////////////////////////////////////////
//! \file   DateTime.cpp
//! \brief  Helper functions for parsing WMI datetime values.
//! \author Chris Oldwood

#include "Common.hpp"
#include "DateTime.hpp"
#include <Core/StringUtils.hpp>
#include <Core/ParseException.hpp>

namespace WMI
{

////////////////////////////////////////////////////////////////////////////////
//! Try and convert a string into a datetime. The format of a WMI datetime is:-
//! YYYYMMDDHHMMSS.FFFFFF+TZO e.g. 20101008181758.546000+060

bool tryParseDateTime(const tstring& value, CDateTime& datetime, tstring& offset)
{
	if (value.size() != 25)
		return false;

	tstring::const_iterator it = value.begin();
	tstring::const_iterator end = value.end();

	size_t digits = 8 + 6; // Date + Time digits.

	while ( (digits != 0) && (it != end) )
	{
		if (!isdigit(*it))
			return false;

		--digits;
		++it;
	}

	if (*it != '.')
		return false;
	else
		++it;

	digits = 6; // Time fraction digits.

	while ( (digits != 0) && (it != end) )
	{
		if (!isdigit(*it))
			return false;

		--digits;
		++it;
	}

	if ( (*it != '+') && (*it != '-') )
		return false;
	else
		++it;

	digits = 3; // Time-zone offset digits.

	while ( (digits != 0) && (it != end) )
	{
		if (!isdigit(*it))
			return false;

		--digits;
		++it;
	}

	const int year       = Core::parse<int>(value.substr( 0, 4));
	const int month      = Core::parse<int>(value.substr( 4, 2));
	const int day        = Core::parse<int>(value.substr( 6, 2));
	const int hours      = Core::parse<int>(value.substr( 8, 2));
	const int minutes    = Core::parse<int>(value.substr(10, 2));
	const int seconds    = Core::parse<int>(value.substr(12, 2));

	if ((year < CDate::MIN_YEAR) || (year > CDate::MAX_YEAR))
		return false;

	if ((month < CDate::MIN_MONTH) || (month > CDate::MAX_MONTH))
		return false;

	if ((day < CDate::MIN_DAY) || (day > CDate::MAX_DAY))
		return false;

	if ((hours < CTime::MIN_HOURS) || (hours > CTime::MAX_HOURS))
		return false;

	if ((minutes < CTime::MIN_MINS) || (minutes > CTime::MAX_MINS))
		return false;

	if ((seconds < CTime::MIN_SECS) || (seconds > CTime::MAX_SECS))
		return false;

	datetime = CDateTime(day, month, year, hours, minutes, seconds);
	offset   = value.substr(21, 4);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//! Convert a string into a datetime or throw an exception if the format is
//! invalid.

CDateTime parseDateTime(const tstring& value)
{
	CDateTime datetime;
	tstring   offset;

	if (!tryParseDateTime(value, datetime, offset))
		throw Core::ParseException(Core::fmt(TXT("Failed to parse WMI datetime - '%s'"), value.c_str()));

	return datetime;
}

//namespace WMI
}
