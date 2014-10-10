#ifndef __rod_time_tick_h__
#define __rod_time_tick_h__

namespace rod {
namespace time{

// microsecond
class tick {
public:
	explicit tick( const int64_t t = 0);
	tick( const tick& t );

	~tick( void );

	const tick& operator=( const int64_t& rhs );
	const tick& operator=( const tick& rhs );
	
	const int64_t value( void ) const ;

#if defined(_WIN32) || defined(_WIN64)
	explicit tick( const FILETIME& ft );
	const tick& operator=( const FILETIME& ft );
	const FILETIME   file_time(void) const;

	explicit tick( const SYSTEMTIME& st );
	const tick& operator=( const SYSTEMTIME& ft );
	const SYSTEMTIME system_time(void) const;
#elif defined( linux ) || defined ( __linux )
	explicit tick( const timespec& t );
	const tick& operator=( const timespec& t );
	const ::timespec timespec( void ) const ;
#endif
	explicit tick( const struct tm& t );
	const tick& operator=( const struct tm& t );
	const struct tm tm( void ) const;

	explicit tick( const ::timeval& t );
	const tick& operator=( const ::timeval& t );
	const ::timeval timeval( void ) const ;

	struct time_t_ref_impl {
		::time_t val;
	};

	explicit tick( const time_t_ref_impl& t );
	const tick& operator=( const time_t_ref_impl& t );
	const ::time_t time_t( void ) const ;

	static const time_t_ref_impl time_t_ref( const ::time_t t );	
	static const tick utc(void);
private:
	uint64_t _value;
/*
	union {
		struct  {
			uint32_t low;
			uint32_t high;
		} u;
		uint64_t _value;
	};
*/
public:	
	// 윈도우 시간은 1601 / 01 / 01 기준 100ns 당 1씩 증가
	// 유닉스 시간은 1970 / 01 / 01 기준 1   s 당 1식 증가
	// 1 s = 1,000,000,000 ns
	// 369 년 => 369 * 365  - 89 (1700 , 1800 , 1900 의 윤년을 제외한 89 일) => 134,774 일
	// 134,774 일 => 134,774 * 24 시간 * 60분 * 60 초 = 11,644,473,600 초 
	// 윈도우시간 / 10,000,000 - 11,644,473,600 => 유닉스 시간
	// 유닉스시간 * 10,000,000 + 116,444,736,000,000,000 -> 윈도우 시간
	static const uint64_t k_epoch_year = 1970;
	static const uint64_t k_epoch_seconds = 11644473600;
	static const uint64_t k_epoch_ticks = k_epoch_seconds * 1000 * 1000;
};

}
}


#endif