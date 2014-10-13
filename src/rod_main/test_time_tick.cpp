#include "stdafx.h"
#include <rod/time/tick.hpp>
#include <rod/time/data_time.hpp>

TEST(time_tick, file_time_convert) {
	FILETIME ft;
    GetSystemTimeAsFileTime( &ft );
	
	rod::time::tick ts(ft);

	FILETIME ft2 = ts.file_time();

	ASSERT_EQ( ft.dwHighDateTime , ft2.dwHighDateTime );
	ASSERT_TRUE( ft.dwLowDateTime >= ft2.dwLowDateTime );
	ASSERT_TRUE( ft.dwLowDateTime - ft2.dwLowDateTime <= 10);

	SYSTEMTIME st = ts.system_time();
	SYSTEMTIME st2;
	FileTimeToSystemTime( &ft , &st2 );

}

TEST( time , file_time_to_local_file_time ) {

	FILETIME ft;
    GetSystemTimeAsFileTime( &ft );

	FILETIME ftlocal;
	FileTimeToLocalFileTime( &ft , &ftlocal );

	SYSTEMTIME st;
	SYSTEMTIME stlocal;
	FileTimeToSystemTime( &ft , &st );
	FileTimeToSystemTime( &ftlocal , &stlocal );
}

TEST( time , date_time ) {
	rod::date_time dt = rod::date_time::local_now();
	rod::date_time::systemtime st;
	dt.system_time(st);
}