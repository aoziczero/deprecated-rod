#ifndef __rod_allocator_h__
#define __rod_allocator_h__

namespace rod {

class allocator {
public:
	allocator(void);
	virtual ~allocator( void );

	virtual void* alloc( const std::size_t sz );
	virtual void  free( void* ptr );
	virtual void* realloc(void* ptr, const std::size_t newsz);

	static rod::allocator* default_allocator(void);
private:
};

template < typename object >
class class_level_allocator {
public:
	class_level_allocator(void)
	{	
	}
protected:
	~class_level_allocator(void) {

	}
public:
	static rod::allocator* class_allocator(void) {
		return _allocator;	
	}
	static rod::allocator* class_allocator(rod::allocator* newallocator) {
		auto val = _allocator;
		_allocator = newallocator;
		return val;
	}
	static rod::allocator** test_val() {
		return &_allocator;
	}
private:	
	static rod::allocator* _allocator;
};

}

#endif