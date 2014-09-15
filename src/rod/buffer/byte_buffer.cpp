#include "stdafx.h"
#include <rod/buffer/byte_buffer.hpp>

#include <cassert>

namespace rod {
namespace buffer{

byte_buffer::byte_buffer(const std::size_t cap)
	: _buffer(cap)
	, _rd_pos(0) 
	, _wr_pos(0)
{

}

byte_buffer::byte_buffer(const byte_buffer& rhs) 
	: _buffer(rhs._buffer)
	, _rd_pos(rhs._rd_pos)
	, _wr_pos(rhs._wr_pos)
{

}

byte_buffer::byte_buffer(byte_buffer&& rhs) 
	: _buffer(std::move(rhs._buffer))
	, _rd_pos(rhs._rd_pos)
	, _wr_pos(rhs._wr_pos)
{
	rhs._rd_pos = 0;
	rhs._wr_pos = 0;
}

const byte_buffer& byte_buffer::operator=(const byte_buffer& rhs) {
	do {
		byte_buffer buf(rhs);
		swap(buf);
	} while (0);
	return *this;
}

const byte_buffer& byte_buffer::operator=(byte_buffer&& rhs){
	if (this != &rhs) {
		_buffer = std::move(rhs._buffer);
		_rd_pos = rhs._rd_pos;
		_wr_pos = rhs._wr_pos;
		rhs._rd_pos = 0;
		rhs._wr_pos = 0;
	}
	return *this;
}

byte_buffer::~byte_buffer(void){

}

std::size_t byte_buffer::capacity(void){
	return _buffer.capacity();
}

void byte_buffer::swap(byte_buffer& buffer) {
	_buffer.swap(buffer._buffer);
	std::swap(_rd_pos, buffer._rd_pos);
	std::swap(_wr_pos, buffer._wr_pos);
}


// writable pointer
uint8_t* byte_buffer::wr_ptr(void) {
	assert( _buffer.ptr() != nullptr && "wr_ptr buffer is nullptr" );
	return static_cast< uint8_t* >(_buffer.ptr()) + _wr_pos;
}

int byte_buffer::wr_ptr(const int move){
	int realmove = 0;
	if (move >= 0) {
		assert( move <= (int)space() && "wr_ptr move gt space()" );
		realmove = std::min(move, (int)space());
		_wr_pos += realmove;
	} else {
		assert(-move <= (int)length() && "wr_ptr move lt length()");
		realmove = std::max(move, -(int)length());
		_wr_pos += realmove;
	}
	return realmove;
}

// readable pointer
uint8_t* byte_buffer::rd_ptr(void){
	assert(_buffer.ptr() != nullptr && "rd_ptr buffer is nullptr");
	return static_cast< uint8_t* >(_buffer.ptr()) + _rd_pos;
}

int byte_buffer::rd_ptr(const int move){
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

int byte_buffer::reserve(const std::size_t newsz){
	return _buffer.reserve(newsz);
}

// adjust data
int byte_buffer::adjust(void){
	_buffer.reserve(_buffer.capacity());
	int ret = (int)_rd_pos;
	memmove(_buffer.ptr(), rd_ptr(), length());
	_wr_pos = length();
	_rd_pos = 0;
	return ret;
}

// data size
std::size_t byte_buffer::length(void){
	return _wr_pos - _rd_pos;
}

// writable size
std::size_t byte_buffer::space(void){
	return capacity() - _wr_pos;
}

std::size_t byte_buffer::read(void* dst, const std::size_t sz) {
	std::size_t cpysize = peak( dst , sz );
	rd_ptr(cpysize);
	return cpysize;
}

std::size_t byte_buffer::peak(void* dst, const std::size_t sz){
	std::size_t cpysize = std::min(sz, length());
	std::copy(rd_ptr(), rd_ptr() + cpysize, static_cast<uint8_t*>(dst));
	return cpysize;
}

std::size_t byte_buffer::write(void* src, const std::size_t sz){
	std::size_t cpysize = std::min(sz, space());
	uint8_t* srcp = static_cast< uint8_t* >(src);
	std::copy( srcp , srcp + cpysize , wr_ptr() );
	return wr_ptr(cpysize);
}

}}