#include "stdafx.h"

#include <rod/rod.hpp>

TEST(rod_base , linkage ) {
	ASSERT_EQ(42, rod::return_magic_number());
}