#ifndef __rod_time_date_time_h__
#define __rod_time_date_time_h__
#include <rod/time/time_span.hpp>
namespace rod {
// if date_time::_value > 0 then utc time
// else local time
class date_time{
public:
	enum kind_type {
		utc ,
		local ,
	};

#if defined(_WIN32) || defined(_WIN64)
	typedef SYSTEMTIME systemtime;
	typedef FILETIME filetime;
	struct timespec{
        time_t   tv_sec;   /* seconds */
        long     tv_nsec;  /* nanoseconds */
    };
#else
	struct systemtime {
		uint16_t wYear;
		uint16_t wMonth;
		uint16_t wDayOfWeek;
		uint16_t wDay;
		uint16_t wHour;
		uint16_t wMinute;
		uint16_t wSecond;
		uint16_t wMilliseconds;
	};
	struct filetime {
		uint32_t dwLowDateTime;
		uint32_t dwHighDateTime;
	};
#endif
public:
	date_time( void );
	date_time( const date_time& rhs );
	date_time( const int64_t tick);
	date_time( const int year 
			, const int month 
			, const int day 
			, const int hour = 0
			, const int minute = 0
			, const int sec = 0
			, const int millisec = 0
			, const int microsec = 0 
			, const date_time::kind_type k = kind_type::utc );
	~date_time(void);

	const date_time& operator=( const date_time& rhs );

	const date_time::kind_type kind( void ) const;
	void kind( date_time::kind_type k ) ;

	const int64_t tick( void ) const;

	const date_time utc_time( void ) const;
	const date_time local_time( void ) const;

	bool operator==( const date_time& rhs ) const;
    bool operator!=( const date_time& rhs ) const;
    bool operator> ( const date_time& rhs ) const;
    bool operator>=( const date_time& rhs ) const;
    bool operator< ( const date_time& rhs ) const;
    bool operator<=( const date_time& rhs ) const;

    date_time  operator+ ( const time_span& rhs ) const;
    date_time& operator+=( const time_span& rhs ) ;
    date_time  operator- ( const time_span& rhs ) const;
    date_time& operator-=( const time_span& rhs ) ;
    time_span  operator- ( const date_time& rhs ) const;


	void system_time( systemtime& st );

	enum class day_of_the_week {
		sunday	    = 0, 
		monday	    = 1, 
		tuesday		= 2, 
		wednesday	= 3, 
		thursday	= 4, 
		friday		= 5, 
		saturday	= 6,
    };	
	int32_t year( void ) const;
	int32_t month( void ) const;
	int32_t day( void ) const; 
	int32_t hour( void ) const; 
	int32_t minute( void ) const;
	int32_t second( void ) const;
	day_of_the_week wday( void ) const;	

	

public:

	static date_time from( const filetime& t , const date_time::kind_type k = kind_type::utc );
	static date_time from( const systemtime& t , const date_time::kind_type k = kind_type::utc );
	static date_time from( const timespec& t , const date_time::kind_type k = kind_type::utc );
	static date_time from( const struct tm& t , const date_time::kind_type k = kind_type::utc );
	static date_time from( const struct timeval& t , const date_time::kind_type k = kind_type::utc );
	static date_time from( const time_t& t , const date_time::kind_type k = kind_type::utc );

	static date_time utc_now( void ) ;
	static date_time local_now( void ) ; 

	static time_span tz_diff( void );
private:
	// microsecond �ð�
	int64_t _tick;
public:
	// ������ �ð��� 1601 / 01 / 01 ���� 100ns �� 1�� ����
	// ���н� �ð��� 1970 / 01 / 01 ���� 1   s �� 1�� ����
	// 1 s = 1,000,000,000 ns
	// 369 �� => 369 * 365  - 89 (1700 , 1800 , 1900 �� ������ ������ 89 ��) => 134,774 ��
	// 134,774 �� => 134,774 * 24 �ð� * 60�� * 60 �� = 11,644,473,600 �� 
	// ������ð� / 10,000,000 - 11,644,473,600 => ���н� �ð�
	// ���н��ð� * 10,000,000 + 116,444,736,000,000,000 -> ������ �ð�
	static const uint64_t k_epoch_year = 1970;
	static const uint64_t k_epoch_seconds = 11644473600;
	static const uint64_t k_epoch_ticks = k_epoch_seconds * 1000 * 1000;
};

}


#endif