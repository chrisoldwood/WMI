////////////////////////////////////////////////////////////////////////////////
//! \file   ObjectTests.cpp
//! \brief  The unit tests for the Object class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Object.hpp>
#include <WMI/Connection.hpp>
#include <WMI/ObjectIterator.hpp>

TEST_SET(Object)
{
	WMI::Connection	connection;
	connection.open();

	WMI::ObjectIterator	end;
	WMI::ObjectIterator	it = connection.execQuery(TXT("SELECT * FROM Win32_OperatingSystem"));

	ASSERT(it != end);

	WMI::Object object = *it;

TEST_CASE("default list of property names does not include system properties")
{
	WMI::Object::PropertyNames names;

	object.getPropertyNames(names/*, WMI::Object::NONSYSTEM_PROPERTIES*/);

	TEST_TRUE(names.find(TXT("LastBootUpTime")) != names.end());
	TEST_FALSE(names.find(TXT("__CLASS")) != names.end());
}
TEST_CASE_END

TEST_CASE("requesting system property names only does not include non-system properties")
{
	WMI::Object::PropertyNames names;

	object.getPropertyNames(names, WMI::Object::SYSTEM_PROPERTIES);

	TEST_FALSE(names.find(TXT("LastBootUpTime")) != names.end());
	TEST_TRUE(names.find(TXT("__CLASS")) != names.end());
}
TEST_CASE_END

TEST_CASE("requesting all property names includes both system and non-system properties")
{
	WMI::Object::PropertyNames names;

	object.getPropertyNames(names, WMI::Object::ALL_PROPERTIES);

	TEST_TRUE(names.find(TXT("LastBootUpTime")) != names.end());
	TEST_TRUE(names.find(TXT("__CLASS")) != names.end());
}
TEST_CASE_END

TEST_CASE("property values are retrieved using the Variant type")
{
	WCL::Variant value;

	object.getProperty(TXT("__CLASS"), value);

	TEST_TRUE(wcscmp(V_BSTR(&value), L"Win32_OperatingSystem") == 0);
}
TEST_CASE_END

TEST_CASE("fetching the value for an unknown property throws an exception")
{
	WCL::Variant value;

	TEST_THROWS(object.getProperty(TXT("__INVALID_PROPERTY_NAME__"), value));
}
TEST_CASE_END

TEST_CASE("property values can be coerced to a specific type")
{
	TEST_TRUE(object.getProperty<tstring>(TXT("__CLASS")) == TXT("Win32_OperatingSystem"));

	TEST_TRUE(object.getProperty<bool>(TXT("Distributed")) == false); // Not a cluster node.
}
TEST_CASE_END

TEST_CASE("the object can be queried to see if a property exists")
{
	TEST_TRUE(object.hasProperty(TXT("LastBootUpTime")));
	TEST_FALSE(object.hasProperty(TXT("__INVALID_PROPERTY_NAME__")));
}
TEST_CASE_END

}
TEST_SET_END
