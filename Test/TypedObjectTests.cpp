////////////////////////////////////////////////////////////////////////////////
//! \file   TypedObjectTests.cpp
//! \brief  The unit tests for the TypedObject class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/TypedObject.hpp>
#include <WMI/Connection.hpp>
#include <WMI/Win32_OperatingSystem.hpp>

static WMI::Connection s_connection;

TEST_SET(TypedObject)
{
	typedef WMI::TypedObject<WMI::Win32_OperatingSystem> TestType;

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

TEST_CASE("select returns an iterator to a sequence of typed WMI objects")
{
	TestType::Iterator it = TestType::select(s_connection);
	TestType::Iterator end;

	TEST_TRUE(it != end);
}
TEST_CASE_END

}
TEST_SET_END
