#ifndef __rod_debug_alloc_tracer_h__
#define __rod_debug_alloc_tracer_h__

#include <set>
#include <rod/allocator.hpp>

namespace rod{
namespace debug{

class alloc_tracer : public rod::allocator {
public:
	alloc_tracer(void);
	virtual ~alloc_tracer(void);

	virtual void* alloc( const std::size_t size );
	virtual void free(void* ptr);
	int  allocated_count(void);
private:
	std::set< void* > _allocated;
};

}}
#endif