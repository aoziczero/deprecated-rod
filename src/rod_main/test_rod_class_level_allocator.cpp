#include "stdafx.h"
#include <rod/allocator.hpp>

class c1 : public rod::class_level_allocator<c1> {
public:
	c1(void){

	}
};


class c2 : public rod::class_level_allocator<c2> {
public:
	c2(void){

	}
};


namespace rod {

	rod::allocator* c1::_allocator = rod::allocator::default_allocator();
	rod::allocator* c2::_allocator = rod::allocator::default_allocator();

}

TEST(class_level_allocator, class_allocator_seperate) {
	ASSERT_EQ(c1::class_allocator(), c2::class_allocator());
	ASSERT_NE(c1::test_val(), c2::test_val());
}
