#include "stdafx.h"
#include <rod/detail/platform_error_category.hpp>

TEST(platform_error_category, platform_error) {
	std::error_code ec = rod::platform_error();
	std::string msg = ec.message();
	EXPECT_FALSE( msg.c_str() != nullptr ) << msg;
}