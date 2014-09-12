#include "stdafx.h"
#include <rod/allocator.hpp>
#include <memory>

namespace rod {

allocator::allocator(void) {

}

allocator::~allocator(void) {

}

void* allocator::alloc(const std::size_t sz) {
	return std::malloc(sz);
}

void  allocator::free(void* ptr) {
	return std::free(ptr);
}

void*  allocator::realloc(void* ptr, const std::size_t newsz) {
	return std::realloc(ptr,newsz);
}

rod::allocator* allocator::default_allocator(void){
	static rod::allocator _default_allocator;
	return &_default_allocator;
}
	
}