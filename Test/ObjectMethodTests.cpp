////////////////////////////////////////////////////////////////////////////////
//! \file   ObjectMethodTests.cpp
//! \brief  The unit tests for the methods aspect of the Object class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Object.hpp>
#include <WMI/Connection.hpp>
#include <WMI/ObjectIterator.hpp>
#include <WCL/Path.hpp>
#include <WCL/Event.hpp>

TEST_SET(ObjectMethod)
{
	WMI::Connection	connection;
	connection.open();

	const WMI::ObjectIterator end;

TEST_CASE("invoking a method on the object taking no arguments returns a value")
{
	const uint32 ACCESS_DENIED = 2;

	CPath ourFolder = CPath::ApplicationDir();

	ourFolder.Replace(TXT('\\'), TXT("\\\\"));

	tstring query = Core::fmt(TXT("SELECT * FROM Win32_Directory WHERE Name='%s'"), ourFolder.c_str());

	WMI::ObjectIterator	it = connection.execQuery(query);

	TEST_TRUE(it != end);

	WMI::Object object = *it;

	// Try and delete ourselves!
	WCL::Variant returnValue;

	object.execMethod(TXT("Delete"), returnValue);

	const uint32 result = WCL::getValue<uint32>(WCL::Variant(returnValue, VT_UI4));

	TEST_TRUE(result == ACCESS_DENIED);
}
TEST_CASE_END

TEST_CASE("an object's state can be refreshed")
{
	typedef Core::SharedPtr<CEvent> EventPtr;
	typedef std::vector<EventPtr> Events;

	const uint32  pid = ::GetCurrentProcessId();
	const tstring querySelf = Core::fmt(TXT("SELECT * FROM Win32_Process WHERE ProcessId=%u"), pid);

	WMI::ObjectIterator it = connection.execQuery(querySelf);
	WMI::Object         object = *it;

	const uint32 processId = object.getProperty<int32>(TXT("ProcessId"));

	TEST_TRUE(processId == pid);

	const uint32 handlesBefore = object.getProperty<int32>(TXT("HandleCount"));

	TEST_TRUE(handlesBefore != 0);

	// create a few more handles.
	Events handles;

	for (size_t i = 0; i != 25; ++i)
		handles.push_back(EventPtr(new CEvent(CEvent::MANUAL, CEvent::NOT_SIGNALLED)));

	object.refresh();

	const uint32 handlesAfter = object.getProperty<int32>(TXT("HandleCount"));

	TEST_TRUE(handlesAfter != handlesBefore);
}
TEST_CASE_END

}
TEST_SET_END
