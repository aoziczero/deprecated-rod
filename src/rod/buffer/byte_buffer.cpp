#include "stdafx.h"
#include <rod/buffer/byte_buffer.hpp>

namespace rod {
namespace buffer{

	byte_buffer::byte_buffer(void)
		: _capacity(0)
	{

	}

	byte_buffer::byte_buffer(std::size_t cap)
		: _capacity(cap)
	{

	}

	byte_buffer::~byte_buffer(void){

	}

	std::size_t byte_buffer::capacity(void){
		return _capacity;
	}
}
}