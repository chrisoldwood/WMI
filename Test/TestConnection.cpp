////////////////////////////////////////////////////////////////////////////////
//! \file   TestConnection.cpp
//! \brief  The unit tests for the Connection class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Connection.hpp>

TEST_SET(Connection)
{

TEST_CASE(Connection, closedOpenClosed)
{
	WMI::Connection connection;

	TEST_FALSE(connection.isOpen());

	connection.open();

	TEST_TRUE(connection.isOpen());

	connection.close();

	TEST_FALSE(connection.isOpen());
}
TEST_CASE_END

TEST_CASE(Connection, invalidNamsespace)
{
	WMI::Connection connection;

	TEST_THROWS(connection.open(WMI::Connection::LOCALHOST, TXT("invalid namespace")));
}
TEST_CASE_END

TEST_CASE(Connection, queryExecutes)
{
	WMI::Connection connection;

	connection.open();
	connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));
}
TEST_CASE_END

}
TEST_SET_END
