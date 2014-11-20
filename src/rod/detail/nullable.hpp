#ifndef __rod_nullable_h__
#define __rod_nullable_h__

#include <rod/tmp/compile_time_error.hpp>
#include <rod/tmp/is_bool.hpp>
#include <rod/detail/aligned_storage.hpp>
#include <type_traits>

namespace rod {

template < typename object_t >
class nullable;

namespace impl {
struct empty {};
}

template <>
class nullable<impl::empty> {
};
/*
template <>
class nullable<bool>{
	DISALLOW_CONSTRUCTOR_AND_COPY( nullable );
};
*/
static nullable<impl::empty> nullable_null;

template < typename object_t >
class nullable {
public: 
	
public:
	nullable(void)
		: _is_null(true) {
		STATIC_CHECK( rod::tmp::is_bool<object_t>::value == 0  , bool_is_not_allowed );
	}	

	nullable(const object_t& rhs) 
		: _is_null(false)
	{
		STATIC_CHECK( rod::tmp::is_bool<object_t>::value == 0  , bool_is_not_allowed );
		new (_storage.data()) object_t(rhs);
	}

	explicit nullable(object_t&& rhs)
		: _is_null(false)
	{
		STATIC_CHECK( rod::tmp::is_bool<object_t>::value == 0  , bool_is_not_allowed );
		new (_storage.data()) object_t(std::move(rhs));
	}

	nullable( const nullable<impl::empty>& null ) 
		: _is_null(true)
	{		
	}

	const nullable& operator=(const nullable<impl::empty>& null)
	{
		destroy();
		return *this;
	}
	
	const nullable& operator=(const object_t& rhs)
	{
		if (_is_null) {
			new (_storage.data()) object_t(rhs);
			_is_null = false;
		} else {
			object_t* obj = get();
			*obj = rhs;
		}
		return *this;
	}

	const nullable& operator=(object_t&& rhs)
	{
		if (_is_null) {
			new (_storage.data()) object_t(std::move(rhs));
			_is_null = false;
		} else {
			object_t* obj = get();
			*obj = std::move(rhs);
		}
		return *this;
	}

	nullable(const nullable& rhs) 
		: _is_null( rhs._is_null )
	{
		STATIC_CHECK( rod::tmp::is_bool<object_t>::value == 0  , bool_is_not_allowed );	
		if ( _is_null )
			return;
		new (_storage.data()) object_t(*rhs);
	}

	nullable(nullable&& rhs)
		: _is_null(rhs._is_null)
	{
		STATIC_CHECK( rod::tmp::is_bool<object_t>::value == 0  , bool_is_not_allowed );	
		if ( _is_null )
			return;

		new (_storage.data()) object_t(std::move(*rhs));
		rhs._is_null = true;
	}

	const nullable& operator=(const nullable& rhs)
	{
		if (rhs._is_null) {
			destroy();	
			return *this;
		} 					
		object_t* rhs_obj = rhs.get();
		if (_is_null) {
			new (_storage.data()) object_t(*rhs_obj);
			_is_null = false;
		} else {
			object_t* obj = get();
			*obj = *rhs_obj;
		}
		return *this;
	}

	const nullable& operator=(nullable&& rhs)
	{
		if (rhs._is_null) {
			destroy();	
			return *this;
		} 	
		object_t* rhs_obj = rhs.get();
		if (_is_null) {
			new (_storage.data())object_t(std::move(*rhs_obj));
			_is_null = false;
		} else {
			object_t* obj = get();				
			*obj = std::move( *rhs_obj);
		}
		return *this;
	}

	~nullable(void) {
		destroy();
	}		

	explicit operator bool(void) const {
		return !_is_null;
	}

	object_t* get(void) const {
		if (_is_null) {
			return nullptr;
		}
		return reinterpret_cast< object_t* >( _storage.data());		
	}

	object_t* operator->(void) const {
		return get();
	}

	object_t& operator*(void) const {
		rod_assert(get() != nullptr, "rod nullable object is null");
		return *get();
	}

	void construct( void ) {
		destroy();
		new (_storage.data()) object_t();
		_is_null = false;
	}

	void construct( const object_t& obj ) {
		destroy();
		new (_storage.data()) object_t(obj);
		_is_null = false;
	}

	void destroy( void ){
		if (_is_null) 
			return;			
		object_t* obj = reinterpret_cast< object_t*>(_storage.data());
		obj->~object_t();
		_is_null = true;
	}
private:	
	aligned_storage< sizeof(object_t) , 8 > _storage;
	bool _is_null;
	/*
	int bool_type(void)const {return 0;}
	typedef int (nullable::*unspecfied_bool_type)(void) const;
	operator unspecfied_bool_type(void) const {
	return _is_placed ? &nullable::bool_type : nullptr;
	}
	*/
};



}

#endif