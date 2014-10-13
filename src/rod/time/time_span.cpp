#include "stdafx.h"
#include <rod/time/time_span.hpp>

namespace rod {

const time_span time_span::infinite( 0x7FFFFFFFFFFFFFFF );

const int64_t number_of_microseconds_in_millisecond	= (int64_t)1000 * 1000;
const int64_t number_of_microseconds_in_second		= (int64_t)1000 * 1000;
const int64_t number_of_microseconds_in_minute		= (int64_t)1000 * 1000 * 60;
const int64_t number_of_microseconds_in_hour		= (int64_t)1000 * 1000 * 60 * 60 ;
const int64_t number_of_microseconds_in_day			= (int64_t)1000 * 1000 * 60 * 60 * 24;

time_span::time_span( void ) 
	:_delta(0)
{

}

time_span::time_span( const time_span& rhs ) 
	: _delta(rhs._delta)
{
}

time_span::time_span( const int64_t delta ) 
	: _delta(delta)
{
}


time_span::time_span( const int days
			 , const int hours
			 , const int minutes
			 , const int seconds
			 , const int milliseconds 
			 , const int microseconds )
{
	_delta = days;
	_delta *= 24;
	_delta += hours;
	_delta *= 60;
	_delta += minutes;
	_delta *= 60;
	_delta += seconds;
	_delta *= 1000;
	_delta += milliseconds;
	_delta *= 1000;
	_delta += microseconds;
}		

const time_span& time_span::operator=( const time_span& rhs ) {
	_delta = rhs._delta;
	return *this;
}

time_span::~time_span( void ) {

}

const int64_t time_span::delta( void ) const {
	return _delta;
}

int64_t time_span::total_micro_seconds( void ) const  {
	return _delta;
}

int64_t time_span::total_milli_seconds( void ) const  {
	return _delta / 1000;
}

int64_t time_span::total_seconds( void ) const {
	return _delta / number_of_microseconds_in_second;
}

int64_t time_span::total_minutes( void ) const {
	return _delta / number_of_microseconds_in_minute;
}

int64_t time_span::total_hours( void ) const {
	return _delta / number_of_microseconds_in_hour;
}

int64_t time_span::total_days( void ) const {
	return _delta / number_of_microseconds_in_day;
}

bool time_span::operator==( const time_span& rhs ) const {
	return _delta == rhs._delta;
}
bool time_span::operator!=( const time_span& rhs ) const {
	return _delta != rhs._delta;
}
bool time_span::operator> ( const time_span& rhs ) const {
	return _delta > rhs._delta;
}
bool time_span::operator>=( const time_span& rhs ) const {
	return _delta >= rhs._delta;
}
bool time_span::operator< ( const time_span& rhs ) const {
	return _delta < rhs._delta;
}
bool time_span::operator<=( const time_span& rhs ) const {
	return _delta <= rhs._delta;
}

time_span  time_span::operator+ ( const time_span& rhs ) const {
	return time_span( _delta + rhs._delta );
}

time_span  time_span::operator- ( const time_span& rhs ) const {
	return time_span( _delta - rhs._delta );
}

time_span  time_span::operator* (const int times ) const {
	return time_span( _delta * times );
}

time_span  time_span::operator/ (const int times ) const {
	return time_span( _delta / times );
}

time_span& time_span::operator+=( const time_span& rhs ) {
	_delta += rhs._delta;
	return *this;
}

time_span& time_span::operator-=( const time_span& rhs ) {
	_delta -= rhs._delta;
	return *this;
}

time_span& time_span::operator*=(const int times ) {
	_delta *= times;
	return *this;
}

time_span& time_span::operator/=(const int times ) {
	_delta /= times;
	return *this;
}
    
time_span  time_span::operator-( void ) const {
	return time_span(-_delta);
}

time_span time_span::from_micro_seconds( const int64_t v ) {
	return time_span(v);
}

time_span time_span::from_milli_seconds( const int64_t v ) {
	return time_span(v * number_of_microseconds_in_millisecond );
}

time_span time_span::from_seconds( const int32_t v ) {
	return time_span(v * number_of_microseconds_in_second );
}

time_span time_span::from_minutes( const int32_t v ) {
	return time_span(v * number_of_microseconds_in_minute);
}

time_span time_span::from_hours( const int32_t v ) {
	return time_span(v * number_of_microseconds_in_hour );
}

time_span time_span::from_days( const int32_t v ) {
	return time_span(v * number_of_microseconds_in_day );
}

}