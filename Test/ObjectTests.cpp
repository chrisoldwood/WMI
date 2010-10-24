////////////////////////////////////////////////////////////////////////////////
//! \file   Object.cpp
//! \brief  The unit tests for the Object class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Object.hpp>
#include <WMI/Connection.hpp>

TEST_SET(Object)
{
	WMI::Connection	connection;
	connection.open();

	WMI::ObjectIterator	end;
	WMI::ObjectIterator	it = connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	ASSERT(it != end);

	WMI::Object object = *it;

TEST_CASE(Object, defaultPropertyNames)
{
	WMI::Object::PropertyNames names;

	object.getPropertyNames(names/*, WMI::Object::NONSYSTEM_PROPERTIES*/);

	TEST_TRUE(names.find(TXT("LastBootUpTime")) != names.end());
	TEST_FALSE(names.find(TXT("__CLASS")) != names.end());
}
TEST_CASE_END

TEST_CASE(Object, systemPropertyNames)
{
	WMI::Object::PropertyNames names;

	object.getPropertyNames(names, WMI::Object::SYSTEM_PROPERTIES);

	TEST_FALSE(names.find(TXT("LastBootUpTime")) != names.end());
	TEST_TRUE(names.find(TXT("__CLASS")) != names.end());
}
TEST_CASE_END

TEST_CASE(Object, allPropertyNames)
{
	WMI::Object::PropertyNames names;

	object.getPropertyNames(names, WMI::Object::ALL_PROPERTIES);

	TEST_TRUE(names.find(TXT("LastBootUpTime")) != names.end());
	TEST_TRUE(names.find(TXT("__CLASS")) != names.end());
}
TEST_CASE_END

TEST_CASE(Object, getProperty)
{
	WCL::Variant value;

	object.getProperty(TXT("__CLASS"), value);

	TEST_TRUE(wcscmp(V_BSTR(&value), L"Win32_OperatingSystem") == 0);

	TEST_THROWS(object.getProperty(TXT("__INVALID_PROPERTY_NAME__"), value));
}
TEST_CASE_END

TEST_CASE(Object, getTypedProperty)
{
	TEST_TRUE(object.getProperty<tstring>(TXT("__CLASS")) == TXT("Win32_OperatingSystem"));

	TEST_TRUE(object.getProperty<bool>(TXT("Distributed")) == false); // Not a cluster node.
}
TEST_CASE_END

}
TEST_SET_END
