#include "stdafx.h"
#include <rod/buffer/rc_buffer.hpp>

namespace rod {
namespace buffer {

	// todo allocator 붙일것
	// class level allocator 가 나아보임
	rc_buffer::rc_buffer(std::size_t cap)
		:_ptr(operator new[](cap + sizeof(std::atomic<int>)))
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

	const rc_buffer& rc_buffer::operator=(const rc_buffer& rhs)
	{
		_remove_reference();
		_ptr = rhs._ptr;
		_capacity = rhs._capacity;
		_add_refrence();
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
				operator delete[](_ptr);
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
		return static_cast<char*>(_ptr)+sizeof(std::atomic<int>);
	}

	int rc_buffer::refrence_count(void) {
		auto val = _refrence_counter();
		if (val != nullptr) {
			return val->load();
		}
		return 0;
	}

}
}