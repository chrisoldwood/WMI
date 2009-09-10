////////////////////////////////////////////////////////////////////////////////
//! \file   ObjectIterator.cpp
//! \brief  The unit tests for the ObjectIterator class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/ObjectIterator.hpp>
#include <WMI/Connection.hpp>

TEST_SET(ObjectIterator)
{

TEST_CASE(ObjectIterator, comparison)
{
	WMI::ObjectIterator	it;
	WMI::ObjectIterator	end;
	WMI::Connection		connection;

	TEST_TRUE(it == end);

	connection.open();
	it = connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it == it);
	TEST_TRUE(it != end);
}
TEST_CASE_END

TEST_CASE(ObjectIterator, operators)
{
	WMI::Connection connection;
	connection.open();

	WMI::ObjectIterator	end;
	WMI::ObjectIterator	it = connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	ASSERT(it != end);

	WMI::Object object = *it;

	++it;

	TEST_TRUE(it == end);
}
TEST_CASE_END

}
TEST_SET_END
