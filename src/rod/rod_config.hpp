#ifndef __rod_config_h__
#define __rod_config_h__

#if defined ( _WIN32 ) 

#if !defined(LIB_ROD) && defined(_MSC_VER)
#pragma comment( lib , "ws2_32" )
#pragma comment( lib , "mswsock" )
#pragma comment( lib , "rod.lib")
#endif

#ifndef noexcept
#define noexcept throw ()
#endif

#pragma warning( disable : 4819 )

#elif defined( linux ) || defined ( __linux )

#ifndef __stdcall
#define __stdcall
#endif

#elif defined ( __MACOSX__ ) || defined ( __APPLE__ ) 

#else

#endif

#ifndef rod_assert
#define rod_assert( expr , msg ) assert( expr && msg )
#endif


#ifndef DISALLOW_COPY
#define DISALLOW_COPY( class_name ) \
	class_name(const class_name& rhs); \
	class_name& operator=(const class_name& rhs);
#endif

#ifndef DISALLOW_CONSTRUCTOR
#define DISALLOW_CONSTRUCTOR( class_name ) \
	class_name(void); \
	~class_name(void);
#endif

#ifndef DISALLOW_CONSTRUCTOR_AND_COPY
#define DISALLOW_CONSTRUCTOR_AND_COPY( class_name )\
	DISALLOW_CONSTRUCTOR(class_name); \
	DISALLOW_COPY(class_name);
#endif

namespace rod {

typedef std::basic_string<TCHAR
	, std::char_traits<TCHAR>
	, std::allocator<TCHAR> > tstring;

}

#include <rod/tmp/compile_time_error.hpp>

#define STATIC_CHECK( expr , msg ) { rod::tmp::compile_time_error< (expr) != 0 > ERROR_##msg;(void)ERROR_##msg;}




#endif


/*
Darwin	 DARWIN						Darwin is not necessarily OS X, see below
FreeBSD	 __FreeBSD__				Consider using the BSD macro
Linux	 linux or __linux			I also found LINUX
MacOS X	 __MACOSX__ or __APPLE__
NetBSD	 __NetBSD__					Consider using the BSD macro
OpenBSD	 __OpenBSD__				Consider using the BSD macro
Solaris	 sun or __sun				SunOS versions < 5 will not have __SVR4 or __svr4__ defined
Windows	 _WIN32 or __WIN32__
*/
