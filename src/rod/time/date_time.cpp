#include "stdafx.h"
#include <rod/time/data_time.hpp>
#include <rod/time/time_util.hpp>

namespace rod {

date_time::date_time( void ) {

}

date_time::date_time( const date_time& rhs ) 
	:_tick( rhs._tick )
{	
}

date_time::date_time( const int64_t tick ) 
	:_tick( tick )
{
}

date_time::date_time( const int year
		, const int month 
		, const int day 
		, const int hour
		, const int minute 
		, const int sec 
		, const int millisec 
		, const int microsec 
		, const date_time::kind_type k )
{
	_tick = time::util::number_of_days_between( 1970 , year - 1 )
		  + time::util::number_of_days_between( year , 1 , month - 1 )
		  + ( day - 1 );
	_tick *= 24;
	_tick += hour;
	_tick *= 60;
	_tick += minute;
	_tick *= 60;
	_tick += sec;
	_tick *= 1000;
	_tick += millisec;
	_tick *= 1000;
	_tick += microsec;
	if ( k == date_time::kind_type::local ) {
		_tick *= -1;
	}
}

date_time::~date_time(void) {

}

const date_time& date_time::operator=( const date_time& rhs ) {
	_tick = rhs._tick;
	return *this;
}

const date_time::kind_type date_time::kind( void ) const {
	if ( _tick < 0 ) {
		return date_time::kind_type::local;
	}
	return date_time::kind_type::utc;
}

void date_time::kind( date_time::kind_type k ) {
	if ( kind() == k )
		return;
	_tick *= -1;
}

const int64_t date_time::tick( void ) const {
	return abs( _tick );
}

const date_time date_time::utc_time( void ) const {
	if ( kind() == date_time::kind_type::utc ) {
		return *this;
	}
	// UTC - LOCAL = TZ_DIFF
	// UTC = TZ_DIFF + LOCAL
	int64_t tick = this->tick() + tz_diff().delta();
	return date_time(tick);
}

const date_time date_time::local_time( void ) const {
	if ( kind() == date_time::kind_type::local ) {
		return *this;
	}
	// UTC - LOCAL = TZ_DIFF
	// LOCAL = UTC - TZ_DIFF
	int64_t tick = this->tick() - tz_diff().delta();
	return date_time(tick);
}


bool date_time::operator==( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return tick() == rhs.tick();
	}
	return utc_time().tick() == rhs.utc_time().tick();
}

bool date_time::operator!=( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return tick() != rhs.tick();
	}
	return utc_time().tick() != rhs.utc_time().tick();
}

bool date_time::operator> ( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return tick() > rhs.tick();
	}
	return utc_time().tick() > rhs.utc_time().tick();
}

bool date_time::operator>=( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return tick() >= rhs.tick();
	}
	return utc_time().tick() >= rhs.utc_time().tick();
}

bool date_time::operator< ( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return tick() < rhs.tick();
	}
	return utc_time().tick() < rhs.utc_time().tick();
}

bool date_time::operator<=( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return tick() <= rhs.tick();
	}
	return utc_time().tick() <= rhs.utc_time().tick();
}

date_time  date_time::operator+ ( const time_span& rhs ) const {
	int64_t tick = this->tick() + rhs.delta();
	date_time dt(tick);
	dt.kind( kind ());
	return dt;
}

date_time& date_time::operator+=( const time_span& rhs )  {
	int multi = _tick < 0 ? -1 : 1;
	_tick *= multi;
	_tick += rhs.delta();
	_tick *= multi;
	return *this;
}

date_time  date_time::operator- ( const time_span& rhs ) const {
	int64_t tick = this->tick() - rhs.delta();
	date_time dt(tick);
	dt.kind( kind());
	return dt;
}

date_time& date_time::operator-=( const time_span& rhs )  {
	int multi = _tick < 0 ? -1 : 1;
	_tick *= multi;
	_tick -= rhs.delta();
	_tick *= multi;
	return *this;
}

time_span  date_time::operator- ( const date_time& rhs ) const {
	if ( kind() == rhs.kind() ) {
		return time_span(tick() - rhs.tick());
	}
	return time_span(utc_time().tick() - rhs.utc_time().tick());
}

void date_time::system_time( systemtime& st ) {
	int64_t tick = this->tick();
	tick /= 1000;
	st.wMilliseconds = tick % 1000;
	tick /= 1000;
	st.wSecond = tick % 60;
	tick /= 60;
	st.wMinute = tick % 60;
	tick /= 60;
	st.wHour = tick % 24;
	tick /= 24;
	st.wDayOfWeek = ( tick + 4 ) % 7;
	st.wYear = 1970;
	for(;;) {
		int number_of_days = time::util::is_leap_year( st.wYear ) ? 366 : 365;
		if ( tick < number_of_days )
			break;
		++st.wYear;
		tick -= number_of_days;
	}
	st.wMonth = 1;
	for(;;) {
		int number_of_days = time::util::number_of_days( st.wYear , st.wMonth  );
		if ( tick < number_of_days )
			break;
		++st.wMonth ;
		tick -= number_of_days;
	}
	st.wDay = static_cast<int>(tick + 1);
}

int32_t date_time::year( void ) const {
	int64_t tick_day = this->tick() / ( (int64_t)1000 * 1000 * 60 * 60 * 24 );
	int year = 1970;
	for(;;) {
		int day_per_year = time::util::is_leap_year( year ) ? 366 : 365;
		if ( tick_day < day_per_year )
			break;
		++year;
		tick_day -= day_per_year;
	}
	return year;
}

int32_t date_time::month( void ) const{
	int64_t tick_day = this->tick() / ( (int64_t)1000 * 1000 * 60 * 60 * 24 );
	int year = 1970;
	for(;;) {
		int number_of_days = time::util::is_leap_year( year ) ? 366 : 365;
		if ( tick_day < number_of_days )
			break;
		++year;
		tick_day -= number_of_days;
	}
	int month = 1;
	for(;;) {
		int number_of_days = time::util::number_of_days( year , month );
		if ( tick_day < number_of_days )
			break;
		++month;
		tick_day -= number_of_days;
	}
	return month;
}

int32_t date_time::day( void ) const{
	int64_t tick_day = this->tick() / ( (int64_t)1000 * 1000 * 60 * 60 * 24 );
	int year = 1970;
	for(;;) {
		int number_of_days = time::util::is_leap_year( year ) ? 366 : 365;
		if ( tick_day < number_of_days )
			break;
		++year;
		tick_day -= number_of_days;
	}
	int month = 1;
	for(;;) {
		int number_of_days = time::util::number_of_days( year , month );
		if ( tick_day < number_of_days )
			break;
		++month;
		tick_day -= number_of_days;
	}
	return static_cast<int32_t>(tick_day) + 1;
}

int32_t date_time::hour( void ) const{
	int64_t tick_hour = this->tick() / ( (int64_t)1000 * 1000 * 60 * 60 );
	return tick_hour % 24;
}

int32_t date_time::minute( void ) const{
	int64_t tick_minute = this->tick() / ( (int64_t)1000 * 1000 * 60 );
	return tick_minute % 60;
}

int32_t date_time::second( void ) const{
	int64_t tick_second = this->tick() / ( (int64_t)1000 * 1000 );
	return tick_second % 60;
}

date_time::day_of_the_week date_time::wday( void ) const{
	// 0 day thursday
	int64_t tick_day = this->tick() / ( (int64_t)1000 * 1000 * 60 * 60 * 24 ) + 4;
	return static_cast< date_time::day_of_the_week >( tick_day % 7 );
}

date_time date_time::from( const filetime& t , const date_time::kind_type k) {
	int64_t tick = ((int64_t) t.dwHighDateTime << 32 ) + t.dwLowDateTime;
	tick /= 10;					// 100 ns to microsec
	tick -= k_epoch_ticks;	
	if ( k == date_time::kind_type::local )
		tick *= -1;
	return date_time(tick);
}

date_time date_time::from( const systemtime& t , const date_time::kind_type k) {
	return date_time( t.wYear
	 , t.wMonth 
	 , t.wDay
	 , t.wHour
	 , t.wMinute 
	 , t.wSecond 
	 , t.wMilliseconds 
	 , 0 
	 , k );
}

date_time date_time::from( const timespec& t , const date_time::kind_type k) {
	int64_t tick = t.tv_sec;
	tick *= 1000 * 1000;
	tick += ( t.tv_nsec / 1000 );
	if ( k == date_time::kind_type::local )
		tick *= -1;
	return date_time(tick);
}

date_time date_time::from( const struct tm& t , const date_time::kind_type k) {
	return date_time( t.tm_year + 1900
	 , t.tm_mon + 1
	 , t.tm_mday
	 , t.tm_hour
	 , t.tm_min 
	 , t.tm_sec 
	 , 0
	 , 0 
	 , k );
}

date_time date_time::from( const struct timeval& t , const date_time::kind_type k) {
	int64_t tick = t.tv_sec * 1000 * 1000 + t.tv_usec;
	if ( k == date_time::kind_type::local )
		tick *= -1;
	return date_time(tick);
}

date_time date_time::from( const time_t& t , const date_time::kind_type k) {
	int64_t tick = t * 1000 * 1000;
	if ( k == date_time::kind_type::local )
		tick *= -1;
	return date_time(tick);
}

date_time date_time::utc_now( void )  {
#if defined(_WIN32) || defined(_WIN64)
	FILETIME ft;
    GetSystemTimeAsFileTime( &ft );
	return date_time::from(ft);
#else
    struct timespec ts;
    if( clock_gettime( CLOCK_REALTIME , &ts ) == -1 ) {
        time_t v = std::time(nullptr);
        return tick(tick::time_t_ref(v));
    }
    return date_time::from(ts);
#endif
}

date_time date_time::local_now( void ) {
	return utc_now().local_time();
}

time_span date_time::tz_diff( void ) {
	static time_span diff( time_span::infinite );
#if defined( _WIN32)	
	if ( diff == time_span::infinite ) {
		FILETIME ft;
		FILETIME ftlocal;
		GetSystemTimeAsFileTime( &ft );
		FileTimeToLocalFileTime( &ft , &ftlocal );
		date_time ftd = date_time::from(ft);
		date_time ftld = date_time::from(ftlocal);
		diff = ftd - ftld;
	}
#else
	return time_span();
#endif
	return diff;
}


}