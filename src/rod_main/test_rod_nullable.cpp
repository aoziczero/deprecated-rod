#include "stdafx.h"
#include <rod/detail/nullable.hpp>

namespace impl {

class testing_tracer {
public:
	testing_tracer(int* v) 
		: _val(v)
	{
		++(*_val);
	}

	testing_tracer(const testing_tracer& rhs)
		: _val(rhs._val) {
		++(*_val);
	}

	testing_tracer(testing_tracer&& rhs)
		: _val(rhs._val) {
		rhs._val = nullptr;
	}

	~testing_tracer(void){
		if ( _val ) 
			--(*_val);
	}

	int value() {
		if ( _val ) 
			return *_val;
		return 0;
	}
private:
	int* _val;

};
}

TEST(rod_nullable, basic) {
	rod::nullable< int > nullobj;
	EXPECT_FALSE( nullobj );
}


TEST(rod_nullable, object_trace) {
	int trace_val = 0;
	do {
		impl::testing_tracer tracer(&trace_val);
		rod::nullable< impl::testing_tracer > obj(tracer);
		EXPECT_TRUE(obj);
		ASSERT_EQ( trace_val , 2 );
		ASSERT_EQ(obj->value() , 2 );
	} while (0);
	ASSERT_EQ(trace_val, 0);

	do {
		rod::nullable< impl::testing_tracer > obj;
		ASSERT_TRUE(obj.get() == nullptr);
		EXPECT_FALSE(obj);
		do {
			impl::testing_tracer tracer(&trace_val);
			ASSERT_EQ(trace_val, 1);
			obj = tracer;
			ASSERT_EQ(trace_val, 2);
		} while (0);
		EXPECT_TRUE(obj);
		ASSERT_EQ(trace_val, 1);
	} while (0);
	ASSERT_EQ(trace_val, 0);

	do {
		impl::testing_tracer tracer(&trace_val);
		rod::nullable< impl::testing_tracer > obj(std::move(tracer));
		EXPECT_TRUE(obj);
		ASSERT_EQ(trace_val, 1);
	} while (0);
	ASSERT_EQ(trace_val, 0);
}

TEST( rod_nullable , reset ) {
	int trace_val = 0;
	rod::nullable< impl::testing_tracer > obj;
	do {
		impl::testing_tracer tracer(&trace_val);
		ASSERT_EQ( trace_val , 1);
		obj = tracer;
		ASSERT_EQ( trace_val , 2);
	} while (0);
	ASSERT_EQ( trace_val , 1);
	obj.destroy();
	ASSERT_EQ( trace_val , 0);
}

struct point {
	int x;
	int y;
};

rod::nullable< point > make_point( int x , int y , bool make ) {
	rod::nullable< point > p;
	if ( make ) {
		p.construct();
		p->x = x;
		p->y = y;
		return p;
	}
	return rod::nullable_null;
}

TEST( rod_nullable , function_return ) {
	rod::nullable< point > valid = make_point(1,2,true);
	ASSERT_TRUE(valid);
	ASSERT_EQ( valid->x , 1 );
	ASSERT_EQ( valid->y , 2 );
	rod::nullable< point > invalid = make_point(1,2,false);
	ASSERT_FALSE(invalid);
	//bool is not allowed
	//rod::nullable<bool> ttt;
}

