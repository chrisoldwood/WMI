////////////////////////////////////////////////////////////////////////////////
//! \file   ObjectIteratorTests.cpp
//! \brief  The unit tests for the ObjectIterator class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/ObjectIterator.hpp>
#include <WMI/Connection.hpp>

static WMI::Connection s_connection;

TEST_SET(ObjectIterator)
{

TEST_CASE_SETUP()
{
	s_connection.open();
}
TEST_CASE_SETUP_END

TEST_CASE_TEARDOWN()
{
	s_connection.close();
}
TEST_CASE_TEARDOWN_END

TEST_CASE("default construction creates an iterator at the end of the sequence")
{
	WMI::ObjectIterator	it;
	WMI::ObjectIterator	end;

	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("an iterator not at the end compares equal with itself")
{
	WMI::ObjectIterator	it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it == it);
}
TEST_CASE_END

TEST_CASE("an iterator not at the end does not compare equal with the sequence end")
{
	WMI::ObjectIterator	end;
	WMI::ObjectIterator	it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it != end);
}
TEST_CASE_END

TEST_CASE("an iterator can be advanced to the end of the sequence")
{
	WMI::ObjectIterator	end;
	WMI::ObjectIterator	it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	ASSERT(it != end);

	WMI::Object object = *it;

	++it;

	TEST_TRUE(it == end);
}
TEST_CASE_END

}
TEST_SET_END
