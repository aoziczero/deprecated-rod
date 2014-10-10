#include "stdafx.h"
#include <rod/time/tick.hpp>

TEST(time_tick, file_time_convert) {
	FILETIME ft;
    GetSystemTimeAsFileTime( &ft );
	FILETIME ft11;
	
	rod::time::tick ts(ft);

	FILETIME ft2 = ts.file_time();

	ASSERT_EQ( ft.dwHighDateTime , ft2.dwHighDateTime );
	ASSERT_TRUE( ft.dwLowDateTime >= ft2.dwLowDateTime );
	ASSERT_TRUE( ft.dwLowDateTime - ft2.dwLowDateTime <= 10);

	SYSTEMTIME st = ts.system_time();
	SYSTEMTIME st2;
	FileTimeToSystemTime( &ft , &st2 );

}