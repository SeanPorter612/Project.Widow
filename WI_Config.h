#pragma once

#ifndef __WI_CommonDef__
#define __WI_CommonDef__

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// define this version of the Widow development system
#define			_WI_VER_MGR			3										// version major
#define			_WI_VER_MNR			8										// version minor
#define			_WI_VER_REV			25										// version revision

//////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------
// this version of the Widow development system
#define			_WI_VER				_WI_VER_MGR._WI_VER_MNR._WI_VER_REV
#define			_WI_VER_STR			"3.8.25"

#include <io.h>
#include <direct.h>
#include <malloc.h>
#include <float.h>
#include <stdarg.h>
#include <process.h>
#include <new>
#include <cstdlib>
#include <exception>
#include <limits>
#include <stack>
#include <stdexcept>

#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <stack>

#include <algorithm>
#include <memory.h>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <time.h>
#include <math.h>
#include <string.h>
#include <cstring>
#include <string>
#include <ctype.h>

#include <random>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <wtypes.h> //For BSTR
#include <comdef.h> //For _bstr_t

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// Widow uses the std name space
using namespace std;

#if !( defined ( __ppc__ ) || defined ( __USE_DOUBLE_PRECISION__ ) || defined ( _SCALAR_ARITHMETIC_ONLY ) )
	#define WI_BUILD_WI_CODE
#endif

#if ( defined ( _WIN32 ) || defined ( _WIN64 ) )

	#define		WI_WIN_BUILD

	#if ( defined ( _WIN32 ) )

		#define WI_X32
	#elif defined ( _WIN64 ) )

		#define WI_X64
	#endif

	#if defined _MSC_VER

		#define WI_VCPP

	#endif

	#if ( _MSC_VER >= 1400 )
		#pragma warning ( disable : 4995 )
		#pragma warning ( disable : 4005 )
		#pragma warning ( disable : 4224 )
		#pragma warning ( disable : 4244 )
		#pragma warning ( disable : 4305 )
		#pragma warning ( disable : 4251 )
		#pragma warning ( disable : 4786 )
		#pragma warning ( disable : 4788 )

		#pragma warning ( disable : 4006 )
		#pragma warning ( disable : 4217 )
		#pragma warning ( disable : 4049 )
		#pragma warning ( disable : 4088 )

		#pragma warning ( disable : 4324 )
		#pragma warning ( disable : 4100 )
		#pragma warning ( disable : 4725 )
		#pragma warning ( disable : 4201 )
		#pragma warning ( disable : 4217 )
		#pragma warning ( disable : 4820 )
		#pragma warning ( disable : 4514 )
		#pragma warning ( disable : 4987 )
		#pragma warning ( disable : 4710 )
		#pragma warning ( disable : 4826 )
		#pragma warning ( disable : 4061 )
		#pragma warning ( disable : 4191 )
		#pragma warning ( disable : 4711 )
		#pragma warning ( disable : 4701 )
		#pragma warning ( disable : 4244 )
		#pragma warning ( disable : 4996 )

		#pragma warning ( disable : 4224 )
		#pragma warning ( disable : 4244 )
		#pragma warning ( disable : 4305 )
		#pragma warning ( disable : 4251 )
		#pragma warning ( disable : 4786 )
		#pragma warning ( disable : 4788 )

		#pragma warning ( disable : 4006 )
		#pragma warning ( disable : 4217 )
		#pragma warning ( disable : 4049 )
		#pragma warning ( disable : 4088 )

		#define _CRT_NONSTDC_NO_DEPRECATE
		#define _CRT_SECURE_NO_DEPRECATE
	#else
		#pragma warning ( disable: 4505 )
		#pragma warning ( disable: 4514 )
	#endif

	#ifdef _DEBUG
		#pragma warning ( disable: 4127 )
	#endif

	#pragma warning ( push, 3 )
		#include <Windows.h>
		#include <crtdbg.h>
	#pragma warning ( pop )
#endif

#if ( defined ( _MINGW_32_VER ) || defined ( _MINGW_64_VER ) )
	#include <io.h>
	#include <direct.h>
	#include <malloc.h>
	#include <float.h>
	#include <stdarg.h>
	#include <windows.h>
	#include <process.h>
#endif

#ifdef WI_BUILD_WI_CODE
	#if ( defined ( _WIN32 ) || defined ( _WIN64 ) )
		#if ( _MSC_VER >= 1400 )
			#include <intrin.h>
		#else
			#if ( _MSC_VER >= 1300 )
				#include <xmmintrin.h>
			#endif
		#endif
	#endif

	#ifdef __ppc__
		#include <vecLib/veclib.h>
	#endif

	#if ( defined ( __i386__ ) || defined ( __x86_64__ ) )
		#include <xmmintrin.h>
	#endif
#endif

#ifdef _LINUX_VER
	#include <pthread.h>
	#include <semaphore.h>
	#include <unistd.h>
#endif

#ifdef _MAC_VER
	#ifndef _MAC_IPHONE
		#include <pthread.h>
		#include <semaphore.h>
	#endif

	#include <unistd.h>
	#include <libkern/OSAtomic.h>
	#include <sys/sysctl.h>
#endif

/////////////////////////////////////////////////////////
// ------------------------------------------------------
// define expression types

#if ( USE_DOUBLE_PRECISION )

	typedef double				WI_Float;

	#define						WI_EPSILON					DBL_EPSILON
	#define						WI_INFINITY					DBL_MAX
	#define						WI_LARGE_FLOAT				1e30

#else

	typedef float				WI_Float;

	#define						WI_EPSILON						FLT_EPSILON
	#define						WI_INFINITY						FLT_MAX
	#define						WI_LARGE_FLOAT					1e18f

#endif

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Used for standard calling conventions
#define							WI_StdCall			__stdcall
#define							WI_FastCall			__fastcall

#define							WI_Inline			inline
#define							WI_FInline			__forceinline

#define 						WI_SI				signed;
#define 						WI_USI				unsigned;

#define							WI_STATIC			static
#define							WI_STATIC_S			WI_STATIC WI_SI
#define							WI_STATIC_U			WI_STATIC WI_USI
#define							WI_S_LINE			WI_STATIC WI_Inline

typedef	void					WI_Data;
typedef void*					WI_DataPtr;

typedef int						WI_Int;
typedef int*					WI_IntArr;

typedef unsigned int				WI_UInt;
typedef unsigned int*				WI_UIntArr;

typedef char					WI_Char;
typedef char*					WI_CharArr;

typedef unsigned char			WI_UChar;
typedef unsigned char*			WI_UCharArr;

typedef long					WI_Long;
typedef long*					WI_LongArr;

typedef unsigned long			WI_ULong;
typedef unsigned long*			WI_ULongArr;

typedef long long				WI_I64;
typedef unsigned long long		WI_U64;

typedef short					WI_Short;
typedef short*					WI_ShortArr;

typedef unsigned short			WI_UShort;
typedef unsigned short*			WI_UShortArr;

typedef double					WI_Double;
typedef double*					WI_DoubleArr;

typedef __int64					WI_I64;

// define nothing
#ifndef WI_NULL
	#define WI_NULL								0
#endif

// define the boolean operator and expression
#ifndef WI_Bool

	typedef unsigned char		WI_Bool;	// assigning a boolean expression
    #define WI_TRUE				1		    // true
	#define WI_FALSE			0			// false

#endif

//************************************************************
#if !( defined ( _WIN32 ) || defined ( _WIN64 ) )
	#define _ASSERTE( x )
#endif

#define __USE_CPU_FOUND__

#define WI_MAXIMUN_THREADS  8

#ifdef _DEBUG
//#define __ENABLE_SANITY_CHECK
#endif

#if ( defined ( _WIN32 ) || defined ( _WIN64 ) )

	#define WI_TimeGetTime ( DWORD )timeGetTime ( );

	// This is used for external function
	#define WI_API_ENTRY		APIENTRY

	// This is used for external function pointers
	#define WI_API_ENTRY_P		APIENTRY *

#endif

#if ( defined ( _WIN32 ) || defined ( _WIN64 ) )

	#define	WI_MSC_VECTOR_ALIGMENT	__declspec( align( 16 ) )
	#define	WI_GCC_VECTOR_ALIGMENT

#else

	#define	WI_MSC_VECTOR_ALIGMENT
	#define	WI_GCC_VECTOR_ALIGMENT	__attribute__ ( ( aligned ( 16 ) ) )

#endif

// define debug and release
#if defined(DEBUG) || defined (_DEBUG)
#define WI_DEBUG
#elif  defined ( RELEASE ) || defined ( _RELEASE )
#define WI_RELEASE
#endif

#ifdef _XBOX

#define WI_USE_VMX128

#include <ppcintrinsics.h>
#define WI_HAVE_NATIVE_FSEL
#define WI_Fsel(a,b,c) __fsel((a),(b),(c))

#endif

#if defined(__MINGW32__) || defined(__CYGWIN__) || (defined (_MSC_VER) && _MSC_VER < 1300)

			#define WI_FInline inline
			#define ATTRIBUTE_ALIGNED16(a) a
			#define ATTRIBUTE_ALIGNED64(a) a
			#define ATTRIBUTE_ALIGNED128(a) a
		#else
			//#define WI_HAS_ALIGNED_ALLOCATOR
			#pragma warning(disable : 4324) // disable padding warning
//			#pragma warning(disable:4530) // Disable the exception disable but used in MSCV Stl warning.
//			#pragma warning(disable:4996) //Turn off warnings about deprecated C routines
//			#pragma warning(disable:4786) // Disable the "debug name too long" warning

			#define WI_FInline __forceinline
			#define ATTRIBUTE_ALIGNED16(a) __declspec(align(16)) a
			#define ATTRIBUTE_ALIGNED64(a) __declspec(align(64)) a
			#define ATTRIBUTE_ALIGNED128(a) __declspec (align(128)) a

	#if (defined (_WIN32) && (_MSC_VER) && _MSC_VER >= 1400) && (!defined (WI_USE_DOUBLE_PRECISION))

			#define WI_USE_SSE

			#ifdef WI_USE_SSE

				#if (_MSC_FULL_VER >= 170050727)//Visual Studio 2012 can compile SSE4/FMA3 (but SSE4/FMA3 is not enabled by default)
					#define WI_ALLOW_SSE4
				#endif //(_MSC_FULL_VER >= 160040219)

				// WI_USE_SSE_IN_API is disabled under Windows by default, because
				// it makes it harder to integrate Bullet into your application under Windows
				// (structured embedding Bullet structs/classes need to be 16-byte aligned)
				// with relatively little performance gain if you are not embedded
				// Bullet data in your classes, or make sure that you align those
				// classes on 16-byte boundaries you can manually enable this line or
				// set it in the build system for a bit of performance gain
				// (a few percent, dependent on usage)
				#define WI_USE_SSE_IN_API

			#endif //WI_USE_SSE

			#include <emmintrin.h>
	#endif

#endif //__MINGW32__

#ifdef WI_DEBUG
	#ifdef _MSC_VER
		#include <stdio.h>
		#define WI_Assert(x) { if(!(x)){printf("Assert " __FILE__  ":%u ("#x")\n", __LINE__);__debugbreak();	}}
	#else//_MSC_VER
		#include <assert.h>
		#define WI_Assert assert
	#endif//_MSC_VER
	#else
		#define WI_Assert(x)
#endif

	//WI_FullAssert is optional, slows down a lot
	#define WI_FullAssert(x)

	#define WI_Likely(_c)  _c
	#define WI_Unlikely(_c) _c

#if defined	(__CELLOS_LV2__)
		#define WI_FInline WI_Inline __attribute__((always_inline))
		#define ATTRIBUTE_ALIGNED16(a) a __attribute__ ((aligned (16)))
		#define ATTRIBUTE_ALIGNED64(a) a __attribute__ ((aligned (64)))
		#define ATTRIBUTE_ALIGNED128(a) a __attribute__ ((aligned (128)))
		#ifndef assert
		#include <assert.h>
		#endif
#ifdef WI_DEBUG
#ifdef __SPU__
#include <spu_printf.h>
#define printf spu_printf
	#define WI_Assert(x) {if(!(x)){printf("Assert "__FILE__ ":%u ("#x")\n", __LINE__);spu_hcmpeq(0,0);}}
#else
	#define WI_Assert assert
#endif

#else
		#define WI_Assert(x)
#endif
		//WI_FullAssert is optional, slows down a lot
		#define WI_FullAssert(x)

		#define WI_Likely(_c)  _c
		#define WI_Unlikely(_c) _c

#else

#ifdef USE_LIBSPE2

		#define WI_FInline __inline
		#define ATTRIBUTE_ALIGNED16(a) a __attribute__ ((aligned (16)))
		#define ATTRIBUTE_ALIGNED64(a) a __attribute__ ((aligned (64)))
		#define ATTRIBUTE_ALIGNED128(a) a __attribute__ ((aligned (128)))
		#ifndef assert
		#include <assert.h>
		#endif
#ifdef WI_DEBUG
		#define WI_Assert assert
#else
		#define WI_Assert(x)
#endif
		//WI_FullAssert is optional, slows down a lot
		#define WI_FullAssert(x)

		#define WI_Likely(_c)   __builtin_expect((_c), 1)
		#define WI_Unlikely(_c) __builtin_expect((_c), 0)

#else
	//non-windows systems

#if (defined (__APPLE__) && (!defined (WI_USE_DOUBLE_PRECISION)))
	#if defined (__i386__) || defined (__x86_64__)
		#define WI_USE_SSE
		//WI_USE_SSE_IN_API is enabled on Mac OSX by default, because memory is automatically aligned on 16-byte boundaries
		//if apps run into issues, we will disable the next line
		#define WI_USE_SSE_IN_API
		#ifdef WI_USE_SSE
			// include appropriate SSE level
			#if defined (__SSE4_1__)
				#include <smmintrin.h>
			#elif defined (__SSSE3__)
				#include <tmmintrin.h>
			#elif defined (__SSE3__)
				#include <pmmintrin.h>
			#else
				#include <emmintrin.h>
			#endif
		#endif //WI_USE_SSE
	#elif defined( __armv7__ )
		#ifdef __clang__
			#define WI_USE_NEON 1

			#if defined WI_USE_NEON && defined (__clang__)
				#include <arm_neon.h>
			#endif//WI_USE_NEON
	   #endif //__clang__
	#endif//__arm__

	#define WI_FInline WI_Inline __attribute__ ((always_inline))
///@todo: check out alignment methods for other platforms/compilers
	#define ATTRIBUTE_ALIGNED16(a) a __attribute__ ((aligned (16)))
	#define ATTRIBUTE_ALIGNED64(a) a __attribute__ ((aligned (64)))
	#define ATTRIBUTE_ALIGNED128(a) a __attribute__ ((aligned (128)))
	#ifndef assert
	#include <assert.h>
	#endif

	#if defined(DEBUG) || defined (_DEBUG)
	 #if defined (__i386__) || defined (__x86_64__)
	#include <stdio.h>
	 #define WI_Assert(x)\
	{\
	if(!(x))\
	{\
		printf("Assert %s in line %d, file %s\n",#x, __LINE__, __FILE__);\
		asm volatile ("int3");\
	}\
	}
	#else//defined (__i386__) || defined (__x86_64__)
		#define WI_Assert assert
	#end//defined (__i386__) || defined (__x86_64__)
	#endif
	#else//defined(DEBUG) || defined (_DEBUG)
		#define WI_Assert(x)
	#endif//defined(DEBUG) || defined (_DEBUG)

	//WI_FullAssert is optional, slows down a lot
	#define WI_FullAssert(x)
	#define WI_Likely(_c)  _c
	#define WI_Unlikely(_c) _c

#else

		#define WI_FInline inline
		///@todo: check out alignment methods for other platforms/compilers
		///#define ATTRIBUTE_ALIGNED16(a) a __attribute__ ((aligned (16)))
		///#define ATTRIBUTE_ALIGNED64(a) a __attribute__ ((aligned (64)))
		///#define ATTRIBUTE_ALIGNED128(a) a __attribute__ ((aligned (128)))
		#define ATTRIBUTE_ALIGNED16(a) a
		#define ATTRIBUTE_ALIGNED64(a) a
		#define ATTRIBUTE_ALIGNED128(a) a
		#ifndef assert
		#include <assert.h>
		#endif

#if defined(DEBUG) || defined (_DEBUG)
		#define WI_Assert assert
#else
		#define WI_Assert(x)
#endif

		//WI_FullAssert is optional, slows down a lot
		#define WI_FullAssert(x)
		#define WI_Likely(_c)  _c
		#define WI_Unlikely(_c) _c
#endif //__APPLE__

#endif // LIBSPE2

#endif	//__CELLOS_LV2__

#ifdef WI_USE_SSE
	typedef __m128 WI_SimdFloat4;
#endif//WI_USE_SSE

#if defined WI_USE_SSE_IN_API && defined (WI_USE_SSE)

	#ifdef _WIN32

		#ifndef WI_NAN
			static int WI_NanMask = 0x7F800001;
			#define WI_NAN (*(float*)&WI_NanMask)
		#endif

		#ifndef WI_INFINITY
			static  int WI_InfinityMask = 0x7F800000;
			#define WI_INFINITY (*(float*)&WI_InfinityMask)
		#endif

		WI_Inline __m128 operator + (const __m128 A, const __m128 B)
		{
			return _mm_add_ps(A, B);
		}

		WI_Inline __m128 operator - (const __m128 A, const __m128 B)
		{
			return _mm_sub_ps(A, B);
		}

		WI_Inline __m128 operator * (const __m128 A, const __m128 B)
		{
			return _mm_mul_ps(A, B);
		}

		#define WI_CastfTo128i(a) (_mm_castps_si128(a))
		#define WI_CastfTo128d(a) (_mm_castps_pd(a))
		#define WI_CastiTo128f(a) (_mm_castsi128_ps(a))
		#define WI_CastdTo128f(a) (_mm_castpd_ps(a))
		#define WI_CastdTo128i(a) (_mm_castpd_si128(a))
		#define WI_Assign128(r0,r1,r2,r3) _mm_setr_ps(r0,r1,r2,r3)

	#else//_WIN32

		#define WI_CastfTo128i(a) ((__m128i)(a))
		#define WI_CastfTo128d(a) ((__m128d)(a))
		#define WI_CastiTo128f(a)  ((__m128) (a))
		#define WI_CastdTo128f(a) ((__m128) (a))
		#define WI_CastdTo128i(a) ((__m128i)(a))
		#define WI_Assign128(r0,r1,r2,r3) (__m128){r0,r1,r2,r3}
		#define WI_INFINITY INFINITY
		#define WI_NAN NAN

	#endif//_WIN32

#endif //WI_USE_SSE_IN_API

#ifdef WI_USE_NEON
#include <arm_neon.h>

typedef float32x4_t WI_SimdFloat4;
#define WI_INFINITY INFINITY
#define WI_NAN NAN
#define WI_Assign128(r0,r1,r2,r3) (float32x4_t){r0,r1,r2,r3}
#endif

#define							WI_Asm						_asm
#define							WI_Asm_						__asm

#define SWAP_INT16( x ) x
#define SWAP_INT32( x ) x

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Essentially the 'Hint' is that the condition specified is assumed
// to be true at that point in the compilation. If '0' is passed,
// then the compiler assumes that any subsequent code in the same
// 'basic block' is unreachable, and thus usually removed.
#define WI_HINT( THE_HINT )		__assume( ( THE_HINT ) )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Force a function call site -not- to inlined. ( useful for profiling )
#define WI_DONT_INLINE( a ) ( ( ( int ) ( a ) + 1 ) ? ( a ) : ( a ) )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Marks the codepath from here until the next branch entry point as unreachable,
// and asserts if any attempt is made to execute it.
#define WI_UNREACHABLE( ) { Assert( 0 ); WI_HINT( 0 ); }

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// In cases where no default is present or appropriate, this causes MSVC to generate
// as little code as possible, and throw an assertion in debug.
#define NO_DEFAULT default: WI_UNREACHABLE( );

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Alloc defined for this platform
#define  WI_Stackalloc( _size ) _alloca( _size )
#define  WI_Stackfree( _p )   0

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Makes a 4-byte "packed ID" int out of 4 characters
#define WI_MAKEID( d, c, b, a )					( ( ( int )( a ) << 24 ) | ( ( int )( b ) << 16 ) | ( ( int )( c ) << 8 ) | ( ( int )( d ) ) )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// Compares a string with a 4-byte packed ID constant
#define WI_STRING_MATCHES_ID( p, id )		( ( * ( ( int * ) ( p ) ) == ( id ) ) ? true : false )
#define WI_ID_TO_STRING( id, p )			( ( p )[ 3 ] = ( ( ( id ) >> 24 ) & 0xFF ), ( p )[ 2 ] = ( ( ( id ) >>16 ) & 0xFF ), ( p )[ 1 ] = ( ( ( id ) >> 8 ) & 0xFF ), ( p )[ 0 ] = ( ( ( id ) >> 0 ) & 0xFF ) )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// get the size of an array
#define WI_ARRAYSIZE( p )		( sizeof ( p ) / sizeof ( p[ 0 ] ) )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// standard maximum size on array
#define WI_MAX_SIZE			60000

#if ( defined ( _WIN32 ) || defined ( _WIN64 ) )
	#define WI_Api __cdecl

	#ifdef _WIN64
		#define WI_Naked
	#else
		#define WI_Naked  __declspec ( naked )
	#endif
#else
	#define WI_Api
	#define WI_Naked
#endif

//
//#ifdef _WIN32
//
//	WI_Float WIDOWLYTE_API WI_Absf( WI_Float x );
//	WI_Float WIDOWLYTE_API WI_Sqrt( WI_Float x );
//	WI_Float WIDOWLYTE_API WI_Sin( WI_Float x );
//	WI_Float WIDOWLYTE_API WI_Cos( WI_Float x );
//	WI_Float WIDOWLYTE_API WI_Asin( WI_Float x );
//	WI_Float WIDOWLYTE_API WI_Acos( WI_Float x );
//	WI_Float WIDOWLYTE_API WI_Atan2( WI_Float x, WI_Float y );
//	WI_Float WIDOWLYTE_API WI_Floor ( WI_Float x );
//	WI_Int WIDOWLYTE_API WI_FastInt ( WI_Float x );
//	void WIDOWLYTE_API WI_SinCos ( WI_Float ang, WI_Float& sinAng, WI_Float& cosAng );
//
//	#define WI_Rsqrt( x ) ( WI_Float ( 1.0f ) / WI_Sqrt( x ) )
//	#define WI_ControlFP( x,y ) _controlfp( x,y )
//
//	#ifdef __USE_DOUBLE_PRECISION__
//		#define WI_Ceil( x ) ceil( x )
//		#define WI_Log( x ) log( x )
//		#define WI_Pow( x,y ) pow( x,y )
//		#define WI_Fmod( x,y ) fmod( x,y )
//
//	#else
//		#define WI_Ceil( x ) ceilf( x )
//		#define WI_Log( x ) logf( x )
//		#define WI_Pow( x,y ) powf( x,y )
//		#define WI_Fmod( x,y ) fmodf( x,y )
//	#endif
//
//#else
//	#define WI_Absf( x ) WI_Float ( fabs( x ) )
//	#define WI_Sin( x ) WI_Float ( sin( x ) )
//	#define WI_Cos( x ) WI_Float ( cos( x ) )
//	#define WI_Asin( x ) WI_Float ( asin( x ) )
//	#define WI_Acos( x ) WI_Float ( acos( x ) )
//	#define WI_Sqrt( x ) WI_Float ( sqrt( x ) )
//	#define WI_Ceil( x ) WI_Float ( ceil( x ) )
//	#define WI_Floor( x ) WI_Float ( floor( x ) )
//	#define WI_FastInt( x ) ( ( WI_Int ) WI_Floor( x ) )
////	#define WI_Log( x ) WI_Float ( log( x ) )
//	#define WI_Log( x ) WI_Float ( log( x ) )
//	#define WI_Pow( x,y ) WI_Float ( pow( x,y ) )
//	#define WI_Fmod( x,y ) WI_Float ( fmod( x,y ) )
//	#define WI_Atan2( x,y ) WI_Float ( atan2( x,y ) )
//	#define WI_Rsqrt( x ) ( WI_Float ( 1.0f ) / WI_Sqrt( x ) )
//	#define WI_ControlFP( x,y ) x
//	#define stricmp( x,y ) strcasecmp( x,y )
//	WI_Inline void WI_SinCos ( WI_Float ang, WI_Float& sinAng, WI_Float& cosAng )
//	{
//		sinAng = WI_Sin( ang );
//		cosAng = WI_Cos( ang );
//	}
//#endif
//
//WI_Inline WIDOWLYTE_API WI_Int WI_AtomicAdd ( WI_Int* const addend, WI_Int amount )
//{
//	#if ( defined ( _WIN32 ) || defined ( _WIN64 ) || defined ( _MINGW_32_VER ) || defined ( _MINGW_64_VER ) )
//		return InterlockedExchangeAdd( ( long* ) addend, long ( amount ) );
//	#endif
//
//	#if ( defined ( _LINUX ) )
//		return __sync_fetch_and_add ( ( int32_t* )addend, amount );
//	#endif
//
//	#if ( defined ( _MAC ) )
//		WI_Int count = OSAtomicAdd32 ( amount, ( int32_t* )addend );
//		return count - ( *addend );
//	#endif
//}

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// converts a pointer to an int
#define WI_PointerToInt( x ) ( ( size_t )x )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// converts an int to a pointer
#define WI_IntToPointer( x ) ( ( void* )( size_t( x ) ) )

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// A macro to delete and null a pointer
#ifndef WI_DELETE_PTR
	#define WI_DELETE_PTR( ptr )			if ( ptr != NULL ) { delete [  ] ptr; ptr = NULL; }
#endif

#ifndef WI_DELETE_OBJ
	#define WI_DELETE_OBJ( ptr )			if ( ptr != NULL ) { delete ptr; ptr = NULL; }
#endif

#ifndef		WI_FREE
	#define WI_FREE( p )					if( p ){ free( ( LPVOID )p ); p = NULL;	 }
#endif

#pragma message ( "		Paradox Systems:	Widow.Lyte: Core Widow configuration and common definitions made and ready to use..." )
#endif