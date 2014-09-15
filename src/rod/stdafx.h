// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if defined( _WIN32 )
#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN 
#define NOMINMAX
#include <WinSock2.h>
#include <MSWSOCK.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <winbase.h>
#endif

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <rod/rod.hpp>