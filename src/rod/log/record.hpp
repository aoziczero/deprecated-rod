#ifndef __rod_log_record_h__
#define __rod_log_record_h__

namespace rod {
namespace log {

enum class level {
	log_debug = 0,
	log_info  ,
	log_warn  ,
	log_error ,
	log_fatal ,
};

struct record{
	rod::log::level lv;

};

}}


#endif