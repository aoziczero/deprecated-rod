#include "stdafx.h"
#include <rod/detail/platform_error_category.hpp>
#include <sstream>

namespace rod {

platform_error_category::platform_error_category(void){

}

platform_error_category::~platform_error_category(void) {

}

const char* platform_error_category::name() const {
	return "platform";
}

std::string platform_error_category::message(int ec) const {
#if defined ( _WIN32 ) 
	const size_t buffer_size = 4096;
	DWORD dwFlags = FORMAT_MESSAGE_FROM_SYSTEM;
	LPCVOID lpSource = NULL;
	char buffer[buffer_size] = { 0, };
	unsigned long result;
	result = ::FormatMessageA(
		dwFlags,
		lpSource,
		ec,
		0,
		buffer,
		buffer_size,
		NULL);

	if (result == 0) {
		std::ostringstream os;
		os << "Unable to get an error message for error code: " << ec << ".";
		return os.str();
	}
	return std::string(buffer);

#elif defined( linux ) || defined ( __linux )
	const size_t buffer_size = 4096;
	char buffer[buffer_size] = { 0, };
	char* msg = strerror_r(_Errval, buffer, buffer_size);
	return std::string(msg);
#elif defined ( __MACOSX__ ) || defined ( __APPLE__ ) 
#else
#endif
}

std::error_category& platform_error_category::instance(void) {
	static platform_error_category instance;
	return instance;
}
 

std::error_code platform_error() {
#if defined ( _WIN32 ) 
	return platform_error(GetLastError());
#else
	return platform_error(errno);
#endif
}

std::error_code platform_error(int ec) {
	return std::error_code(ec, platform_error_category::instance());
}

}