#include "stdafx.h"
#include <rod/buffer/byte_buffer.hpp>

TEST(byte_buffer_t1, byte_buffer){
	rod::buffer::byte_buffer buffer(1024);
	ASSERT_EQ(buffer.capacity(), 1024);
}