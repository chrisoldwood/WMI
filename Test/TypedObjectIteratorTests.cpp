////////////////////////////////////////////////////////////////////////////////
//! \file   TypedObjectIteratorTests.cpp
//! \brief  The unit tests for the TypedObjectIterator class.
//! \author Chris Oldwood

#include "Common.hpp"
#include <Core/UnitTest.hpp>
#include <WMI/TypedObjectIterator.hpp>
#include <WMI/Connection.hpp>
#include <WMI/Win32_OperatingSystem.hpp>

static WMI::Connection s_connection;

TEST_SET(TypedObjectIterator)
{
	typedef WMI::TypedObjectIterator<WMI::Win32_OperatingSystem> Win32OperatingSystemIterator;

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
	Win32OperatingSystemIterator it;
	Win32OperatingSystemIterator end;

	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("an iterator not at the end compares equal with itself")
{
	Win32OperatingSystemIterator it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it == it);
}
TEST_CASE_END

TEST_CASE("an iterator not at the end does not compare equal with the sequence end")
{
	Win32OperatingSystemIterator end;
	Win32OperatingSystemIterator it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it != end);
}
TEST_CASE_END

TEST_CASE("an iterator can be advanced to the end of the sequence")
{
	Win32OperatingSystemIterator end;
	Win32OperatingSystemIterator it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	ASSERT(it != end);

	++it;

	TEST_TRUE(it == end);
}
TEST_CASE_END

TEST_CASE("an end iterator throws if dereferenced")
{
	Win32OperatingSystemIterator	end;

	TEST_THROWS(*end);
}
TEST_CASE_END

TEST_CASE("an iterator not at the end can be dereferenced")
{
	Win32OperatingSystemIterator it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE((*it).Name() != TXT(""));
}
TEST_CASE_END

TEST_CASE("an end iterator throws if the ptr-to-member is invoked")
{
	Win32OperatingSystemIterator end;

	TEST_THROWS(end->Name());
}
TEST_CASE_END

TEST_CASE("an iterator not at the end can be invoked via the ptr-to-member operator")
{
	Win32OperatingSystemIterator it = s_connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it->Name() != TXT(""));
}
TEST_CASE_END

}
TEST_SET_END
