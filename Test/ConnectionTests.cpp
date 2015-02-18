////////////////////////////////////////////////////////////////////////////////
//! \file   ConnectionTests.cpp
//! \brief  The unit tests for the Connection class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Connection.hpp>
#include <WMI/ObjectIterator.hpp>

TEST_SET(Connection)
{

TEST_CASE("a connection transitions from closed to open to closed")
{
	WMI::Connection connection;

	TEST_FALSE(connection.isOpen());

	connection.open();

	TEST_TRUE(connection.isOpen());

	connection.close();

	TEST_FALSE(connection.isOpen());
}
TEST_CASE_END

TEST_CASE("open throws when invalid namespace specified")
{
	WMI::Connection connection;

	TEST_THROWS(connection.open(WMI::Connection::LOCALHOST, TXT(""), TXT(""), TXT("invalid namespace")));
}
TEST_CASE_END

TEST_CASE("an open connection can execute a query")
{
	WMI::Connection		connection;
	WMI::ObjectIterator	end;

	connection.open();
	WMI::ObjectIterator it = connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	TEST_TRUE(it != end);
}
TEST_CASE_END

TEST_CASE("an object can be queried using it's path")
{
	const uint32  pid = ::GetCurrentProcessId();
	const tstring querySelf = Core::fmt(TXT("SELECT * FROM Win32_Process WHERE ProcessId=%u"), pid);

	WMI::Connection connection;
	connection.open();

	WMI::ObjectIterator	end;
	WMI::ObjectIterator it = connection.execQuery(querySelf);

	TEST_TRUE(it != end);

	const tstring     path = it->relativePath();
	const WMI::Object object = connection.getObject(path);

	TEST_TRUE(object.relativePath() == path);
}
TEST_CASE_END

}
TEST_SET_END
