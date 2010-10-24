////////////////////////////////////////////////////////////////////////////////
//! \file   ExceptionTests.cpp
//! \brief  The unit tests for the Exception class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Exception.hpp>
#include <wbemidl.h>
#include <WCL/ComPtr.hpp>

TEST_SET(Exception)
{

TEST_CASE("exception can be constructed with a generic HRESULT and message")
{
	const HRESULT result = E_FAIL;
	const tchar* message = TXT("Unit Test");

	WMI::Exception e(result, message);

	TEST_TRUE(e.m_result == result);
	TEST_TRUE(tstrstr(e.twhat(), message) != nullptr);
}
TEST_CASE_END

TEST_CASE("exception constructed with a WMI error code has WMI error message")
{
	typedef WCL::ComPtr<IWbemLocator> IWbemLocatorPtr;

	const HRESULT result = WBEM_E_DATABASE_VER_MISMATCH;
	const tchar* myMessage = TXT("Unit Test");
	const tchar* wmiMessage = TXT("version mismatch");

	IWbemLocatorPtr locator(CLSID_WbemAdministrativeLocator);

	WMI::Exception e(result, locator, myMessage);

	TEST_TRUE(e.m_result == result);
	TEST_TRUE(tstrstr(e.twhat(), myMessage) != nullptr);
	TEST_TRUE(tstrstr(e.twhat(), wmiMessage) != nullptr);
}
TEST_CASE_END

}
TEST_SET_END
