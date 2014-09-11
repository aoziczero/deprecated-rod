#include "stdafx.h"
#include <rod/buffer/rc_buffer.hpp>
#include <rod/debug/alloc_tracer.hpp>

TEST(rc_buffer, alloc) {
	rod::debug::alloc_tracer tracer;
	rod::allocator* old = rod::buffer::rc_buffer::class_allocator( &tracer );
	do {
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
	} while (0);

	rod::buffer::rc_buffer::class_allocator(old);
	ASSERT_EQ(tracer.allocated_count() , 0);
}

TEST(rc_buffer, self_assign) {
	rod::debug::alloc_tracer tracer;
	rod::allocator* old = rod::buffer::rc_buffer::class_allocator(&tracer);
	do {
		rod::buffer::rc_buffer buffer(1024);
		rod::buffer::rc_buffer* pself = &buffer;
		void* ptr = buffer.ptr();
		buffer = *pself;
		ASSERT_EQ(buffer.refrence_count(), 1);
		ASSERT_EQ(ptr, buffer.ptr());
	} while (0);

	rod::buffer::rc_buffer::class_allocator(old);
	ASSERT_EQ(tracer.allocated_count(), 0);
}

TEST(rc_buffer, move) {
	rod::debug::alloc_tracer tracer;
	rod::allocator* old = rod::buffer::rc_buffer::class_allocator(&tracer);

	do{
		rod::buffer::rc_buffer buffer(1024);
		void* original = buffer.ptr();
		rod::buffer::rc_buffer moved(std::move(buffer));
		ASSERT_EQ(buffer.ptr(), nullptr);
		ASSERT_EQ(moved.ptr(), original);
		ASSERT_EQ(moved.refrence_count(), 1);

		rod::buffer::rc_buffer move_assign(1024);
		move_assign = std::move(moved);
		ASSERT_EQ(moved.ptr(), nullptr);
		ASSERT_EQ(move_assign.ptr(), original);
		ASSERT_EQ(move_assign.refrence_count(), 1);
	} while (0);

	rod::buffer::rc_buffer::class_allocator(old);
	ASSERT_EQ(tracer.allocated_count(), 0);
}

TEST(rc_buffer, reserve) {
	rod::buffer::rc_buffer buf(1024);
	// grow buffer
	void* ori = buf.ptr();
	auto sz = buf.capacity();
	buf.reserve(2048);
	ASSERT_NE(buf.ptr() , ori);
	ASSERT_NE(buf.capacity(),sz);

	// make sure buffer size
	ori = buf.ptr();
	sz = buf.capacity();
	buf.reserve(2048);
	ASSERT_EQ(buf.ptr(), ori);
	ASSERT_EQ(buf.capacity(), sz);
	
	
	auto add_ref(buf);	
	ori = buf.ptr();
	sz = buf.capacity();
	buf.reserve(2048);
	ASSERT_NE(buf.ptr(), ori);
}