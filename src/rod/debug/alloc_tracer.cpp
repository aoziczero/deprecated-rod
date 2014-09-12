#include "stdafx.h"
#include <rod/debug/alloc_tracer.hpp>

namespace rod{
namespace debug{

alloc_tracer::alloc_tracer(void) {

}

alloc_tracer::~alloc_tracer(void){

}

void* alloc_tracer::alloc(const std::size_t size) {
	void* ptr = operator new[](size);
	_allocated.insert(ptr);
	return ptr;
}

void alloc_tracer::free(void* ptr) {
	auto it = _allocated.find(ptr);
	if (it != _allocated.end()) {
		_allocated.erase(it);
	}
	operator delete[](ptr);
}

int  alloc_tracer::allocated_count(void) {
	return _allocated.size();
}

}
}