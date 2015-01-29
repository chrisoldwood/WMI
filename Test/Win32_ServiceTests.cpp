////////////////////////////////////////////////////////////////////////////////
//! \file   Win32_Service.cpp
//! \brief  The tests for the Win32_Service class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Connection.hpp>
#include <WMI/Win32_Service.hpp>

TEST_SET(Win32_Service)
{
	WMI::Connection	connection;
	connection.open();

/*
** These tests were written to aid in testing the ability to invoke a WMI method.
** I could not find an obvious universal method to safely invoke every time the
** tests are run so they have to be invoked manually as they may need to be
** tweaked to match the target system.
*/

/*
TEST_CASE("a method taking no arguments can be invoked")
{
	const tchar* query = TXT("select * from Win32_Service where name='MSSQL$SQLEXPRESS'");

	WMI::Win32_Service::Iterator end;
	WMI::Win32_Service::Iterator it = connection.execQuery(query);

	TEST_TRUE(it != end);

	WMI::Win32_Service service = *it;

	uint32 result = service.StopService();

	TEST_TRUE(result == 0 || result == 5);
}
TEST_CASE_END
*/
}
TEST_SET_END
