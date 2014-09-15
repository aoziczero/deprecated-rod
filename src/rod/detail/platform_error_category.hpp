#ifndef __rod_platform_error_category__
#define __rod_platform_error_category__

#include <system_error>

namespace rod {

class platform_error_category : public std::error_category {
public:
	platform_error_category( void );
	virtual ~platform_error_category( void );
	virtual const char* name() const ;
	virtual std::string message(int ec) const;
	static std::error_category& instance(void);
};

std::error_code platform_error();
std::error_code platform_error( int ec );

}
#endif