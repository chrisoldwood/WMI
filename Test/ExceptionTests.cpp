////////////////////////////////////////////////////////////////////////////////
//! \file   TestException.cpp
//! \brief  The unit tests for the Exception class.
//! \author Chris Oldwood

#include "stdafx.h"
#include <Core/UnitTest.hpp>
#include <WMI/Exception.hpp>
#include <wbemidl.h>
#include <WCL/ComPtr.hpp>

TEST_SET(Exception)
{

TEST_CASE(Exception, standardResultCode)
{
	WMI::Exception e(E_FAIL, TXT("Unit Test"));

	TEST_TRUE(e.m_result == E_FAIL);
	TEST_TRUE(tstrstr(e.twhat(), TXT("Unit Test")) != nullptr);
}
TEST_CASE_END

TEST_CASE(Exception, wmiResultCode)
{
	typedef WCL::ComPtr<IWbemLocator> IWbemLocatorPtr;

	IWbemLocatorPtr locator(CLSID_WbemAdministrativeLocator);

	WMI::Exception e(WBEM_E_ACCESS_DENIED, locator, TXT("Unit Test"));

	TEST_TRUE(e.m_result == WBEM_E_ACCESS_DENIED);
	TEST_TRUE(tstrstr(e.twhat(), TXT("Unit Test")) != nullptr);
}
TEST_CASE_END

}
TEST_SET_END
