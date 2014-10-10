#include "stdafx.h"
#include <rod/detail/aligned_storage.hpp>

TEST( aligned_storage , basic ) {
	rod::aligned_storage< 16 , 4 > align_4;
	ASSERT_EQ( align_4.size() , 16 );
	EXPECT_TRUE(((uintptr_t)align_4.data() % 4) == 0 );	

	rod::aligned_storage< 16 , 8 > align_8;
	ASSERT_EQ( align_4.size() , 16 );
	EXPECT_TRUE(((uintptr_t)align_8.data() % 4 ) == 0 );
	EXPECT_TRUE(((uintptr_t)align_8.data() % 8 ) == 0 );
	
	rod::aligned_storage< 16 , 16 > align_16;
	ASSERT_EQ( align_4.size() , 16 );
	EXPECT_TRUE(((uintptr_t)align_16.data() % 4 ) == 0 );
	EXPECT_TRUE(((uintptr_t)align_16.data() % 8 ) == 0 );
	EXPECT_TRUE(((uintptr_t)align_16.data() % 16) == 0 );
}

TEST( aligned_storage , array ) {
	rod::aligned_storage< 16 , 16 > align_16[8];
	for ( int i = 0 ; i < 8 ; ++i ) {
		ASSERT_TRUE( ((uintptr_t)align_16[i].data() % 16 ) == 0 );
	}
}