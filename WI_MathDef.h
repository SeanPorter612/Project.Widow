#pragma once

#ifndef __iMathDef__
#define __iMathDef__

#include < math.h >
#include < float.h >
//
//////////////////////////////////////////////////////////////////////////
////---------------------------------------------------------------------
//// common math definitions and macros
//
///////////////////////////////////////////////////////////
//// ------------------------------------------------------
//// The famous PI functions
//#define WI_PI2	WI_Float ( WI_PI * 2.0f )
//
///////////////////////////////////////////////////////////
//// ------------------------------------------------------
//// radians functions
//#define WI_RAD2DEG( x )		( ( WI_Float ) ( x ) * ( WI_Float ) ( 180.0f / PI ) )
//#define WI_RAD2DEG2	  	 	WI_Float ( 180.0f / WI_PI )
//#define WI_DEG2RAD	  	 	WI_Float ( WI_PI / 180.0f )
//
//
///////////////////////////////////////////////////////////
//// ------------------------------------------------------
//// gets the magnitude of the normal of a vector
////#define WI_Magnitude( Normal ) ( WI_Sinf ( Normal.x * Normal.x + Normal.y * Normal.y + Normal.z * Normal.z ) )


#pragma message ( "		Widow math defines and macros done..." )
#endif
