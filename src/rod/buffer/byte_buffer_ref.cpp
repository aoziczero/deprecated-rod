#include "stdafx.h"
#include <rod/buffer/byte_buffer_ref.hpp>


namespace rod {
namespace buffer{

byte_buffer_ref::byte_buffer_ref(void* ptr, const std::size_t cap) {

}

byte_buffer_ref::byte_buffer_ref(byte_buffer_ref&& rhs) {

}

const byte_buffer_ref& byte_buffer_ref::operator=(byte_buffer_ref&& rhs) {

}

byte_buffer_ref::~byte_buffer_ref(void) {

}

std::size_t byte_buffer_ref::capacity(void);
uint8_t* byte_buffer_ref::wr_ptr(void);
int byte_buffer_ref::wr_ptr(const int move);

uint8_t* byte_buffer_ref::rd_ptr(void);
int byte_buffer_ref::rd_ptr(const int move);

std::size_t byte_buffer_ref::length(void);

std::size_t byte_buffer_ref::space(void);

std::size_t byte_buffer_ref::read(void* dst, const std::size_t sz);
std::size_t byte_buffer_ref::peak(void* dst, const std::size_t sz);
std::size_t byte_buffer_ref::write(void* src, const std::size_t sz);

}}