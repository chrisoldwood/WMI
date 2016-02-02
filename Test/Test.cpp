////////////////////////////////////////////////////////////////////////////////
//! \file   Test.cpp
//! \brief  The test harness entry point.
//! \author Chris Oldwood

#include "Common.hpp"
#include <tchar.h>
#include <Core/UnitTest.hpp>
#include <WCL/AutoCom.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	TEST_SUITE(argc, argv)
	{
		WCL::AutoCom oCom(COINIT_APARTMENTTHREADED);

		TEST_SUITE_RUN();
	}
	TEST_SUITE_END
}
