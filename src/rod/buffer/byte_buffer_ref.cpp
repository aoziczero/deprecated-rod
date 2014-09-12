#include "stdafx.h"
#include <rod/buffer/byte_buffer_ref.hpp>
#include <algorithm>
#include <cassert>

namespace rod {
namespace buffer{

byte_buffer_ref::byte_buffer_ref(void* ptr, const std::size_t cap) 
	: _ptr(ptr)
	, _capacity(cap)
	, _rd_pos(0)
	, _wr_pos(0)
{
}

byte_buffer_ref::byte_buffer_ref(byte_buffer_ref&& rhs) 
	: _ptr(rhs._ptr) 
	, _capacity(rhs._capacity)
	, _rd_pos(rhs._rd_pos)
	, _wr_pos(rhs._wr_pos)
{
	rhs._ptr = nullptr;
	rhs._capacity = 0;
	rhs._rd_pos = 0;
	rhs._wr_pos = 0;
}

const byte_buffer_ref& byte_buffer_ref::operator=(byte_buffer_ref&& rhs) {
	if (this != &rhs) {
		_ptr = rhs._ptr;
		_capacity = rhs._capacity;
		_rd_pos = rhs._rd_pos;
		_wr_pos = rhs._wr_pos;
		rhs._ptr = nullptr;
		rhs._capacity = 0;
		rhs._rd_pos = 0;
		rhs._wr_pos = 0;
	}
	return *this;
}

byte_buffer_ref::~byte_buffer_ref(void) {
	
}

std::size_t byte_buffer_ref::capacity(void) {
	return _capacity;
}

uint8_t* byte_buffer_ref::wr_ptr(void) {
	assert(_ptr != nullptr && "wr_ptr buffer is nullptr");
	return static_cast< uint8_t* >(_ptr)+_wr_pos;
}

int byte_buffer_ref::wr_ptr(const int move) {
	int realmove = 0;
	if (move >= 0) {
		assert(move <= (int)space() && "wr_ptr move gt space()");
		realmove = std::min(move, (int)space());
		_wr_pos += realmove;
	}
	else {
		assert(-move <= (int)length() && "wr_ptr move lt length()");
		realmove = std::max(move, -(int)length());
		_wr_pos += realmove;
	}
	return realmove;
}

uint8_t* byte_buffer_ref::rd_ptr(void){
	assert(_ptr != nullptr && "rd_ptr buffer is nullptr");
	return static_cast< uint8_t* >(_ptr)+_rd_pos;
}

int byte_buffer_ref::rd_ptr(const int move){
	int realmove = 0;
	if (move >= 0) {
		assert(move <= (int)length() && "rd_ptr move gt length()");
		realmove = std::min(move, (int)length());
		_rd_pos += realmove;
	}
	else {
		assert(-move <= (int)_rd_pos && "rd_ptr move lt _rd_pos");
		realmove = std::max(move, -(int)_rd_pos);
		_rd_pos += realmove;
	}
	return realmove;
}

std::size_t byte_buffer_ref::length(void){
	return _wr_pos - _rd_pos;
}

std::size_t byte_buffer_ref::space(void){
	return capacity() - _wr_pos;
}

std::size_t byte_buffer_ref::read(void* dst, const std::size_t sz){
	std::size_t cpysize = peak(dst, sz);
	rd_ptr(cpysize);
	return cpysize;
}

std::size_t byte_buffer_ref::peak(void* dst, const std::size_t sz){
	std::size_t cpysize = std::min(sz, length());
	std::copy(rd_ptr(), rd_ptr() + cpysize, static_cast<uint8_t*>(dst));
	return cpysize;
}

std::size_t byte_buffer_ref::write(void* src, const std::size_t sz){
	std::size_t cpysize = std::min(sz, space());
	uint8_t* srcp = static_cast< uint8_t* >(src);
	std::copy(srcp, srcp + cpysize, wr_ptr());
	return wr_ptr(cpysize);
}

}}