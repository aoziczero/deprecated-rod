#ifndef __rod_log_tag_h__
#define __rod_log_tag_h__

#include <rod/rod_config.hpp>

namespace rod {
namespace log {

class tag{
public:
	tag( const rod::tstring& tag );
private:
	rod::tstring _tag;
};

}}


#endif