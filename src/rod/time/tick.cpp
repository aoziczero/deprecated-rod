#include "stdafx.h"
#include <rod/time/tick.hpp>
#include <time.h>

namespace rod {
namespace time{

tick::tick(const int64_t t )
	: _value(t)
{
}

tick::~tick( void ) {
}

tick::tick( const tick& t ) 
	: _value(t._value)
{

}

const tick& tick::operator=( const int64_t& rhs ) {
	_value = rhs;
	return *this;
}

const tick& tick::operator=( const tick& rhs ) {
	_value = rhs._value;
	return *this;
}

const int64_t tick::value( void ) const  {
	return _value;
}

const tick tick::utc(void) {
#if defined(_WIN32) || defined(_WIN64)
	FILETIME ft;
    GetSystemTimeAsFileTime( &ft );
	return tick(ft);
#else
    struct timespec ts;
    if( clock_gettime( CLOCK_REALTIME , &ts ) == -1 ) {
        time_t v = std::time(nullptr);
        return tick(tick::time_t_ref(v));
    }
    return tick(ts);
#endif
}

const tick::time_t_ref_impl tick::time_t_ref( const ::time_t t ) {
	tick::time_t_ref_impl ref;
	ref.val = t;
	return ref;
}

#if defined(_WIN32) || defined(_WIN64)
tick::tick( const FILETIME& ft ) {
	_value = ((uint64_t) ft.dwHighDateTime << 32 ) + ft.dwLowDateTime;
	_value /= 10;					// 100 ns to microsec
	_value -= tick::k_epoch_ticks;	
}

const tick& tick::operator=( const FILETIME& ft ) {
	_value = ((uint64_t) ft.dwHighDateTime << 32 ) + ft.dwLowDateTime;
	_value /= 10;					// 100 ns to microsec
	_value -= tick::k_epoch_ticks;	
	return *this;
}

tick::tick( const SYSTEMTIME& st ) {
	FILETIME ft;
	SystemTimeToFileTime( &st , &ft );
	this->operator=(ft);
}

const tick& tick::operator=( const SYSTEMTIME& st ) {
	FILETIME ft;
	SystemTimeToFileTime( &st , &ft );
	return this->operator=(ft);
}

const SYSTEMTIME tick::system_time(void) const {
	FILETIME ft = file_time();
	SYSTEMTIME st;
	FileTimeToSystemTime( &ft , &st );
	return st;
}

const FILETIME   tick::file_time(void) const {
	uint64_t val = _value;
	val  += tick::k_epoch_ticks;
	val *= 10; 
	FILETIME ft;
	ft.dwHighDateTime = val >> 32;
	ft.dwLowDateTime  = val & 0xffffffff;
	return ft;
}
#elif defined( linux ) || defined ( __linux )
tick::tick( const timespec& t ) 
{
	_value = t.tv_sec;
	_value *= 1000;
	_value *= 1000;
	_value += ( ts.tv_nsec / 1000 );
}
const tick& tick::operator=( const timespec& t ) {
	_value = t.tv_sec;
	_value *= 1000;
	_value *= 1000;
	_value += ( ts.tv_nsec / 1000 );
	return *this;
}
const ::timespec tick::timespec( void ) const  {
	::timespec ts;
	ts.tv_sec = _value / ( 1000 * 1000 );
	ts.tv_nsec = ( _value % ( 1000 * 1000 )) * 1000;
	return ts;
}
#endif

tick::tick( const struct tm& t ) {
	// mktime return localtime
	::time_t ts = ::mktime( const_cast< struct tm* >(&t)) - timezone;
	this->operator=(tick::time_t_ref(ts));
}

const tick& tick::operator=( const struct tm& t ) {
	::time_t ts = ::mktime( const_cast< struct tm* >(&t)) - timezone;
	return this->operator=(tick::time_t_ref(ts));
}

const struct tm tick::tm( void ) const {
	::time_t tt = this->time_t();
	struct tm ts;
	gmtime_s( &ts , &tt );
	return ts;
}

tick::tick( const ::timeval& t ) {
	_value =  ( t.tv_sec * 1000 * 1000	) + t.tv_usec;
}

const tick& tick::operator=( const ::timeval& t ) {
	_value =  ( t.tv_sec * 1000 * 1000	) + t.tv_usec;
	return *this;
}

const ::timeval tick::timeval( void ) const  {
	::timeval tv;
	tv.tv_usec = _value % ( 1000 * 1000 );
	tv.tv_sec = static_cast<long>(_value / ( 1000 * 1000 ));
	return tv;
}

tick::tick( const time_t_ref_impl& t ) {
	_value = t.val * 1000 * 1000;
}

const tick& tick::operator=( const time_t_ref_impl& t ) {
	_value = t.val * 1000 * 1000;
	return *this;
}

const ::time_t tick::time_t( void ) const {
	return _value / 1000 / 1000;
}

}}