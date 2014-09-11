#include "stdafx.h"
#include <rod/buffer/rc_buffer.hpp>
#include <algorithm>

namespace rod {

rod::allocator* buffer::rc_buffer::_allocator = rod::allocator::default_allocator();

namespace buffer {

rc_buffer::rc_buffer(std::size_t cap)
	:_ptr(class_allocator()->alloc(cap + sizeof(std::atomic<int>)))
	, _capacity(cap)
{
	_refrence_counter()->store(1);
}

rc_buffer::rc_buffer(const rc_buffer& rhs)
	: _ptr(rhs._ptr)
	, _capacity(rhs._capacity)
{
	_add_refrence();
}

rc_buffer::rc_buffer(rc_buffer&& rhs)
	: _ptr(rhs._ptr)
	, _capacity(rhs._capacity)
{
	rhs._ptr = nullptr;
	rhs._capacity = 0;
}

const rc_buffer& rc_buffer::operator=(const rc_buffer& rhs)
{
	do {
		rc_buffer buffer(rhs);
		this->swap(buffer);
	} while (0);
	return *this;
}

const rc_buffer& rc_buffer::operator=( rc_buffer&& rhs)
{
	if (this != &rhs) {
		rc_buffer buffer(std::move(*this));
		this->swap(rhs);
	}
	return *this;
}

rc_buffer::~rc_buffer(void) {
	_remove_reference();
}

int rc_buffer::_add_refrence(void) {
	auto val = _refrence_counter();
	if (val != nullptr) {
		return val->fetch_add(1) + 1;
	}
	return 0;
}

int rc_buffer::_remove_reference(void) {
	auto val = _refrence_counter();
	if (val != nullptr) {
		auto ret = val->fetch_sub(1);
		if (ret == 1) {
			class_allocator()->free(_ptr);
			_ptr = nullptr;
		}
		return ret;
	}
	return 0;
}

std::atomic<int>* rc_buffer::_refrence_counter(void) {
	if (_ptr == nullptr)
		return nullptr;
	return reinterpret_cast<std::atomic<int>*>(_ptr);
}

std::size_t rc_buffer::capacity(void) {
	return _capacity;
}

void* rc_buffer::ptr(void) {
	if (_ptr == nullptr)
		return nullptr;
	return static_cast<char*>(_ptr)+sizeof(std::atomic<int>);
}

int rc_buffer::refrence_count(void) {
	auto val = _refrence_counter();
	if (val != nullptr) {
		return val->load();
	}
	return 0;
}

void rc_buffer::swap(rc_buffer& buf) {
	std::swap(_ptr, buf._ptr);
	std::swap(_capacity, buf._capacity);
}

int rc_buffer::reserve(const std::size_t newsz) {
	if (refrence_count() != 1 || _capacity < newsz ) {
		rc_buffer new_buf(newsz);
		memcpy(new_buf.ptr(), ptr(), std::min( newsz , _capacity ));
		swap(new_buf);
		return 1;
	}
	return 0;
}

}
}