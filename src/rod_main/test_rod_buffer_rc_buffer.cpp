#include "stdafx.h"
#include <rod/buffer/rc_buffer.hpp>

TEST(rc_buffer, alloc) {
	rod::buffer::rc_buffer buffer(1024);
	ASSERT_EQ(buffer.refrence_count(), 1);
	ASSERT_GE(buffer.capacity(), (std::size_t)1024);
	{
		rod::buffer::rc_buffer ref(buffer);
		ASSERT_EQ(buffer.refrence_count(), 2);
		ASSERT_EQ(ref.refrence_count(), 2);
		ASSERT_EQ(buffer.ptr(), ref.ptr());
	}
	ASSERT_EQ(buffer.refrence_count(), 1);
	{
		rod::buffer::rc_buffer ref(1024);
		ref = buffer;
		ASSERT_EQ(buffer.refrence_count(), 2);
		ASSERT_EQ(ref.refrence_count(), 2);
		ASSERT_EQ(buffer.ptr(), ref.ptr());
	}
	ASSERT_EQ(buffer.refrence_count(), 1);
}