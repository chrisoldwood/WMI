////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_OperatingSystemTests.cpp
//! \brief  The unit tests for the Win32_OperatingSystem class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Connection.hpp>
#include <WMI/Win32_OperatingSystem.hpp>

TEST_SET(Win32_OperatingSystem)
{
	WMI::Connection	connection;
	connection.open();

TEST_CASE("object can be constructed from untyped WMI object")
{
	WMI::ObjectIterator	it = connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));
	
	WMI::Win32_OperatingSystem object((*it).get());

	TEST_PASSED("object constructed");
}
TEST_CASE_END

TEST_CASE("construction from incorrect untyped WMI object throws an exception")
{
	WMI::ObjectIterator	it = connection.execQuery(TXT("SELECT * FROM Win32_LogicalMemoryConfiguration"));

	TEST_THROWS(WMI::Win32_OperatingSystem((*it).get()));
}
TEST_CASE_END

TEST_CASE("select returns an iterator to a sequence of Win32_OperatingSystem objects")
{
	WMI::Win32_OperatingSystem::Iterator it = WMI::Win32_OperatingSystem::select(connection);
	WMI::Win32_OperatingSystem::Iterator end;

	TEST_TRUE(it != end);
}
TEST_CASE_END

TEST_CASE("LastBootUpTime converts a WMI string property to a datetime")
{
	WMI::Win32_OperatingSystem::Iterator it = WMI::Win32_OperatingSystem::select(connection);

	CDateTime lastBootUpTime = it->LastBootUpTime();

	TEST_TRUE(lastBootUpTime.Date().Year() > 2010);
}
TEST_CASE_END

}
TEST_SET_END
