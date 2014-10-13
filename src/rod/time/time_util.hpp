#ifndef __rod_time_util_h__
#define __rod_time_util_h__

namespace rod {
namespace time {

class util {
public:
	static bool is_leap_year( int year );
	// [year_start , year_end]
	static int  number_of_days_between( int year_start , int year_end );
	// [mon_start , mon_end]
	static int  number_of_days_between( int year , int mon_start , int mon_end );
	static int  number_of_days( int year , int month );
};

}}


#endif