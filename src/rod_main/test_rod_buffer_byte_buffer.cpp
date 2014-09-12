#include "stdafx.h"
#include <rod/buffer/byte_buffer.hpp>
#include <rod/buffer/byte_buffer_ref.hpp>

TEST(byte_buffer, construct ){
	rod::buffer::byte_buffer buffer(1024);
	ASSERT_TRUE(buffer.capacity()>= 1024);
}

TEST(byte_buffer, wr_ptr) {
	rod::buffer::byte_buffer buffer(1024);
	std::size_t cap = buffer.capacity();
	buffer.wr_ptr( 10 );
	ASSERT_EQ(buffer.length() ,10);
	ASSERT_EQ( cap - 10 , buffer.space() );
	buffer.wr_ptr(-8 );
	ASSERT_EQ(buffer.length(), 2);
	ASSERT_EQ(cap - 2, buffer.space());
	buffer.wr_ptr(-2);
	ASSERT_EQ(buffer.length(), 0);
	ASSERT_EQ(cap, buffer.space());
}

TEST(byte_buffer, rd_ptr) {
	rod::buffer::byte_buffer buffer(1024);
	std::size_t cap = buffer.capacity();
	buffer.wr_ptr(100);
	buffer.rd_ptr(10);
	ASSERT_EQ(buffer.length(), 90);
	buffer.rd_ptr(-8);
	ASSERT_EQ(buffer.length(), 98);
	buffer.rd_ptr(-2);
	ASSERT_EQ(buffer.length(), 100);
}

TEST(byte_buffer, read_write) {
	char* msg = "testmsg";
	rod::buffer::byte_buffer buffer(1024);
	buffer.write(msg, strlen(msg)+1);
	ASSERT_STREQ(msg, (char*)buffer.rd_ptr());
	char buff[1024];
	buffer.peak(buff, buffer.length());
	ASSERT_STREQ(msg, (char*)buffer.rd_ptr());
	ASSERT_STREQ(msg, buff);	

	buffer.read(buff, buffer.length());
	buffer.adjust();
	ASSERT_EQ(buffer.length() , 0 );
	ASSERT_TRUE(buffer.space() == buffer.capacity());
}

TEST(byte_buffer_ref, basic) {
	char buffer[1024];
	char* buf = "testmsg";
	rod::buffer::byte_buffer_ref ref(buffer, 1024);
	ASSERT_EQ(ref.capacity(), 1024);
	ASSERT_EQ(ref.length(), 0);

	ref.write(buf, strlen(buf) + 1);

	ASSERT_STREQ(buffer, buf);

	ASSERT_EQ(ref.length(), strlen(buf) + 1);
}