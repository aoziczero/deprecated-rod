// rod_main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#if defined (_DEBUG) 
#pragma comment( lib , "gtest/lib/gtestd.lib")
#else
#pragma comment( lib , "gtest/lib/gtest.lib")
#endif

#include <rod/rod.hpp>

int _tmain(int argc, _TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

