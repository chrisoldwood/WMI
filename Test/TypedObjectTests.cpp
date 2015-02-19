////////////////////////////////////////////////////////////////////////////////
//! \file   TypedObjectTests.cpp
//! \brief  The unit tests for the TypedObject class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/TypedObject.hpp>
#include <WMI/Connection.hpp>
#include <WCL/Event.hpp>

class TestClass : public WMI::TypedObject<TestClass>
{
public:
	TestClass(WMI::IWbemClassObjectPtr object, const WMI::Connection& connection)
		: WMI::TypedObject<TestClass>(object, connection)
	{ }

	uint32 ProcessId() const
	{
		return getProperty<int32>(TXT("ProcessId"));
	}

	uint32 HandleCount() const
	{
		return getProperty<int32>(TXT("HandleCount"));
	}

	static const tchar* WMI_CLASS_NAME;
};

const tchar* TestClass::WMI_CLASS_NAME = TXT("Win32_Process");

static WMI::Connection s_connection;

TEST_SET(TypedObject)
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

TEST_CASE("select returns an iterator to a sequence of typed WMI objects")
{
	TestClass::Iterator end;
	TestClass::Iterator it = TestClass::select(s_connection);

	TEST_TRUE(it != end);
}
TEST_CASE_END

TEST_CASE("a typed object's state can be refreshed")
{
	typedef Core::SharedPtr<CEvent> EventPtr;
	typedef std::vector<EventPtr> Events;

	const uint32  pid = ::GetCurrentProcessId();
	const tstring querySelf = Core::fmt(TXT("SELECT * FROM Win32_Process WHERE ProcessId=%u"), pid);

	TestClass::Iterator it = s_connection.execQuery(querySelf);
	TestClass           object = *it;

	const uint32 processId = object.ProcessId();

	TEST_TRUE(processId == pid);

	const uint32 handlesBefore = object.HandleCount();

	TEST_TRUE(handlesBefore != 0);

	// create a few more handles.
	Events handles;

	for (size_t i = 0; i != 25; ++i)
		handles.push_back(EventPtr(new CEvent(CEvent::MANUAL, CEvent::NOT_SIGNALLED)));

	object.refresh();

	const uint32 handlesAfter = object.HandleCount();

	TEST_TRUE(handlesAfter != handlesBefore);
}
TEST_CASE_END

}
TEST_SET_END
