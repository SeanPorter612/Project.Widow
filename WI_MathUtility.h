#pragma once

#ifndef __WI_MathCore__
#define __WI_MathCore__

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// Widow math lib includes
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

#define BEHIND		0
#define INTERSECTS	1
#define FRNT		2

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// simple min and max
#ifndef WI_MIN_VAL
	#define WI_MIN_VAL( x,y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )
#endif
#ifndef WI_MAX_VAL
	#define WI_MAX_VAL( x,y ) ( ( x ) > ( y ) ? ( x ) : ( y ) )
#endif

#define WI_PI				( 3.141592653589793238462643383279 )
#define WI_2_PI				( WI_Float		( WI_PI * WI_PI ) )
#define WI_HALF_PI			( WI_2_PI	*	WI_Float ( 0.25 ) )

#define WI_RADS_PER_DEG		( WI_2_PI	/	WI_Float ( 360.0 ) )
#define WI_DEGS_PER_RAD		( WI_Float		( 360.0 )	/	WI_2_PI )

#define WI_SIMDSQRT12		( WI_Float		( 0.7071067811865475244008443621048490 ) )

#define WI_EXP			 	WI_Float ( 2.71828f )
#define WI_KMH2MPSEC		WI_Float ( 0.278f )

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// ----------------------------------------------------------------------------------------------
	// ----------------------------------------------------------------------------------------------
	// begin of common math functions all global calls : )

	#define WI_ROUND_MASK			0x0fffff3ff
	#define WI_ROUND_DOWN			0x000000400

	//////////////////////////////////////////////////////////////////////
	// -------------------------------------------------------------------
	// simple min and max
	#define WI_MIN(		x,	y	) ( ( x ) < ( y ) ? ( x ) : ( y ) )
	#define WI_MAX(		x,	y	) ( ( x ) > ( y ) ? ( x ) : ( y ) )

//#if ( WINVER )

//#define	WI_Sqrt( x )		WI_Float ( sqrtf ( WI_Float ( x ) ) )
//#define	WI_Mod( x, y )		WI_Float ( fmod	 ( WI_Float ( x ), WI_Float ( y ) ) )
//
//#define WI_Sin( x )		WI_Float ( sinf	 ( WI_Float ( x ) ) )
//#define WI_Cos( x )		WI_Float ( cosf	 ( WI_Float ( x ) ) )

WI_Float WI_Sqrt 	( WI_Float x );
WI_Float WI_Abs 	( WI_Float x );
WI_Float WI_Sin		( WI_Float x );
WI_Float WI_Cos		( WI_Float x );
WI_Float WI_Asin	( WI_Float x );
WI_Float WI_Acos	( WI_Float x );
WI_Float WI_Atan2	( WI_Float x,	WI_Float y );
WI_Float WI_Floor	( WI_Float x );
WI_Int WI_FastInt	( WI_Float x );

WI_Inline void WI_SinCos ( WI_Float ang, WI_Float& sinAng, WI_Float& cosAng );

#define WI_fAbs( x )			(	WI_Abs  ( x )		)
#define WI_fSqrt( x )			(	WI_Sqrt  ( x )		)
#define WI_fSin( x )			(	WI_Sin   ( x )		)
#define WI_fCos( x )			(	WI_Cos   ( x )		)
#define WI_fAsin( x )			(	WI_Asin  ( x )		)
#define WI_fAcos( x )			(	WI_Acos  ( x )		)
#define WI_fAtan2( x, y )		(	WI_Atan2 ( x, y )	)
#define WI_fFloor( x )			(	WI_Floor ( x )		)
#define WI_Rsqrt( x )			(	WI_Float ( 1.0f ) / WI_fSqrt( x ) )
#define WI_ControlFP( x, y )	( _controlfp( x,	y )	)

#ifdef __USE_DOUBLE_PRECISION__

	#define WI_Ceil( x )		ceil ( x	)
	#define WI_Log(	x )			log ( x )
	#define WI_Pow(	x,	y )		pow ( x, y )
	#define WI_Fmod( x,	y )		fmod (	x,	y)

#else

	#define WI_Ceil( x )		ceilf( x )
	#define WI_Log( x )			logf( x )
	#define WI_Pow( x, y )		powf( x,y )
	#define WI_Fmod( x, y )		fmodf( x,y )

#endif

#if defined(WI_USE_DOUBLE_PRECISION) || defined(WI_FORCE_DOUBLE_FUNCTIONS)

WI_FInline WI_Float WI_Fabs(WI_Float x) { return fabs(x); }

#else

WI_FInline WI_Float WI_Fabs(WI_Float x) { return fabsf(x); }

#endif

WI_Inline WI_Int WI_AtomicAdd ( WI_Int* addend, WI_Int amount );

/* reciprocal square root */
#define WI_RecipSqrt( x ) ( ( WI_Float )( WI_Float ( 1.0 )	/	WI_Sqrt ( WI_Float ( x ) ) ) )

#ifndef _MSC_VER
#define _ASSERTE ( x )
#ifndef min
#define min ( a,b ) ( ( a < b ) ? ( a ) : ( b ) )
#define max ( a,b ) ( ( a > b ) ? ( a ) : ( b ) )
#endif
#endif

#ifdef _MSC_VER
#ifdef _DEBUG
void WI_ExpandTraceMessage ( const char *fmt, ... );
#define WI_Trace ( x )										\
{														\
	WI_ExpandTraceMessage x;								\
}
#else
#define WI_Trace ( x )
#endif
#endif

WI_FInline WI_Float WI_Atan2Fast ( WI_Float y, WI_Float x )
{
	WI_Float coeff_1 = WI_PI / 4.0f;
	WI_Float coeff_2 = 3.0f * coeff_1;
	WI_Float abs_y = WI_Fabs(y);
	WI_Float angle;
	if (x >= 0.0f) {
		WI_Float r = (x - abs_y) / (x + abs_y);
		angle = coeff_1 - coeff_1 * r;
	} else {
		WI_Float r = (x + abs_y) / (abs_y - x);
		angle = coeff_2 - coeff_1 * r;
	}
	return (y < 0.0f) ? -angle : angle;
}

WI_FInline bool      WI_FuzzyZero(WI_Float x) { return WI_Abs(x) < WI_EPSILON; }

WI_FInline bool	WI_Equal(WI_Float a, WI_Float eps)
{
	return (((a) <= eps) && !((a) < -eps));
}
WI_FInline bool	WI_GreaterEqual (WI_Float a, WI_Float eps)
{
	return (!((a) <= eps));
}

WI_FInline int       WI_IsNegative(WI_Float x)
{
	return x < WI_Float(0.0) ? 1 : 0;
}

WI_FInline WI_Float WI_Radians(WI_Float x) { return x * WI_RADS_PER_DEG; }
WI_FInline WI_Float WI_Degrees(WI_Float x) { return x * WI_DEGS_PER_RAD; }

#define WI_DECLARE_HANDLE(name) typedef struct name##__ { int unused; } *name

#ifndef WI_Fsel
WI_FInline WI_Float WI_Fsel(WI_Float a, WI_Float b, WI_Float c)
{
	return a >= 0 ? b : c;
}
#endif

#define WI_Fsels(a,b,c) (WI_Float)WI_Fsel(a,b,c)

WI_FInline bool WI_MachineIsLittleEndian()
{
   long int i = 1;
   const char *p = (const char *) &i;
   if (p[0] == 1)  // Lowest address contains the least significant byte
	   return true;
   else
	   return false;
}

///WI_Select avoids branches, which makes performance much better for consoles like Playstation 3 and XBox 360
///Thanks Phil Knight. See also http://www.cellperformance.com/articles/2006/04/more_techniques_for_eliminatin_1.html
WI_FInline unsigned WI_Select(unsigned condition, unsigned valueIfConditionNonZero, unsigned valueIfConditionZero)
{
	// Set testNz to 0xFFFFFFFF if condition is nonzero, 0x00000000 if condition is zero
	// Rely on positive value or'ed with its negative having sign bit on
	// and zero value or'ed with its negative (which is still zero) having sign bit off
	// Use arithmetic shift right, shifting the sign bit through all 32 bits
	unsigned testNz = (unsigned)(((int)condition | -(int)condition) >> 31);
	unsigned testEqz = ~testNz;
	return ((valueIfConditionNonZero & testNz) | (valueIfConditionZero & testEqz));
}

WI_FInline int WI_Select(unsigned condition, int valueIfConditionNonZero, int valueIfConditionZero)
{
	unsigned testNz = (unsigned)(((int)condition | -(int)condition) >> 31);
	unsigned testEqz = ~testNz;
	return static_cast<int>((valueIfConditionNonZero & testNz) | (valueIfConditionZero & testEqz));
}

WI_FInline float WI_Select(unsigned condition, float valueIfConditionNonZero, float valueIfConditionZero)
{
#ifdef WI_HAVE_NATIVE_FSEL
	return (float)WI_Fsel((WI_Float)condition - WI_Float(1.0f), valueIfConditionNonZero, valueIfConditionZero);
#else
	return (condition != 0) ? valueIfConditionNonZero : valueIfConditionZero;
#endif
}

template<typename T> WI_FInline void WI_Swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

//PCK: endian swapping functions
WI_FInline unsigned WI_SwapEndian(unsigned val)
{
	return (((val & 0xff000000) >> 24) | ((val & 0x00ff0000) >> 8) | ((val & 0x0000ff00) << 8)  | ((val & 0x000000ff) << 24));
}

WI_FInline unsigned short WI_SwapEndian(unsigned short val)
{
	return static_cast<unsigned short>(((val & 0xff00) >> 8) | ((val & 0x00ff) << 8));
}

WI_FInline unsigned WI_SwapEndian(int val)
{
	return WI_SwapEndian((unsigned)val);
}

WI_FInline unsigned short WI_SwapEndian(short val)
{
	return WI_SwapEndian((unsigned short) val);
}

///WI_SwapFloat uses using char pointers to swap the endianness
////WI_SwapFloat/WI_SwapDouble will NOT return a float, because the machine might 'correct' invalid floating point values
///Not all values of sign/exponent/mantissa are valid floating point numbers according to IEEE 754.
///When a floating point unit is faced with an invalid value, it may actually change the value, or worse, throw an exception.
///In most systems, running user mode code, you wouldn't get an exception, but instead the hardware/os/runtime will 'fix' the number for you.
///so instead of returning a float/double, we return integer/long long integer
WI_FInline unsigned int  WI_SwapEndianFloat(float d)
{
	unsigned int a = 0;
	unsigned char *dst = (unsigned char *)&a;
	unsigned char *src = (unsigned char *)&d;

	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];
	return a;
}

// unswap using char pointers
WI_FInline float WI_UnswapEndianFloat(unsigned int a)
{
	float d = 0.0f;
	unsigned char *src = (unsigned char *)&a;
	unsigned char *dst = (unsigned char *)&d;

	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];

	return d;
}

// swap using char pointers
WI_FInline void  WI_SwapEndianDouble(double d, unsigned char* dst)
{
	unsigned char *src = (unsigned char *)&d;

	dst[0] = src[7];
	dst[1] = src[6];
	dst[2] = src[5];
	dst[3] = src[4];
	dst[4] = src[3];
	dst[5] = src[2];
	dst[6] = src[1];
	dst[7] = src[0];
}

// unswap using char pointers
WI_FInline double WI_UnswapEndianDouble(const unsigned char *src)
{
	double d = 0.0;
	unsigned char *dst = (unsigned char *)&d;

	dst[0] = src[7];
	dst[1] = src[6];
	dst[2] = src[5];
	dst[3] = src[4];
	dst[4] = src[3];
	dst[5] = src[2];
	dst[6] = src[1];
	dst[7] = src[0];

	return d;
}

// returns normalized value in range [-WI_PI, WI_PI]
WI_FInline WI_Float WI_NormalizeAngle(WI_Float angleInRadians)
{
	angleInRadians = WI_Fmod(angleInRadians, WI_2_PI);
	if(angleInRadians < -WI_PI)
	{
		return angleInRadians + WI_2_PI;
	}
	else if(angleInRadians > WI_PI)
	{
		return angleInRadians - WI_2_PI;
	}
	else
	{
		return angleInRadians;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input float to int
WI_Int		WI_FloatToInt ( WI_Float val );

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input int to float
WI_Float	WI_IntToFloat ( WI_Int val );

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input float to Double
WI_Double	WI_FloatToDouble ( WI_Float val );

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input Double to float
WI_Float	WI_DoubleToFloat ( WI_Double val );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// This multiplies a scalar by a WI_Vector4 and returns a WI_Vector4
WI_Vector4	operator* ( WI_Float scalar, const WI_Vector4& v );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// This checks to see if a point is inside the ranges of a polygon
bool		WI_InsidePolygon (
	WI_Vector4 vIntersection,
	WI_Vector4 Poly[ ],
	WI_Long verticeCount );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This checks to see if a line intersects a plane
bool		WI_IntersectedPlane (
	WI_Vector4 vPoly[ ],
	WI_Vector4 vLine[ ],
	WI_Vector4 &vNormal,
	WI_Float &originDistance );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This checks if a line is intersecting a polygon
bool		WI_IntersectedPolygon (
	WI_Vector4 vPoly[ ],
	WI_Vector4 vLine[ ],
	WI_Int verticeCount );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns true if the sphere is intersecting any of the edges of the polygon
bool		WI_EdgeSphereCollision (
	WI_Vector4 &vCenter,
	WI_Vector4 vPolygon[ ],
	WI_Int vertexCount,
	WI_Float radius );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	Returns true if collided
bool		WI_SpherePolygonCollision (
	WI_Vector4 vPolygon[ ],
	WI_Vector4 &vCenter,
	WI_Int vertexCount,
	WI_Float radius );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This checks to see if a point is inside the ranges of a polygon
double		WI_AngleBetweenVectors (
	WI_Vector4 Vector1,
	WI_Vector4 Vector2 );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// This adds 2 vectors together and returns the result
WI_Vector4	WI_AddVector (
	WI_Vector4 vVector1,
	WI_Vector4 vVector2 );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// This divides a vector by a single number ( scalar ) and returns the result
WI_Vector4	WI_DivideVectorByScaler (
	WI_Vector4 vVector1,
	WI_Float Scaler );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns a perpendicular vector from 2 given vectors by taking the cross product.
WI_Vector4	WI_Cross (
	WI_Vector4 vVector1,
	WI_Vector4 vVector2 );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// This returns the normal of a vector
WI_Vector4	WI_Normalize ( WI_Vector4 vNormal );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the normal of a polygon ( The direction the polygon is facing )
WI_Vector4	WI_Normal ( WI_Vector4 vPolygon[ ] );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// This calculates a vector between 2 points and returns the result
WI_Vector4	WI_VectorBetween2Points (
	WI_Vector4 vPoint1,
	WI_Vector4 vPoint2 );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// Returns the position to off set by a collision
WI_Vector4	WI_GetCollisionOffset (
	WI_Vector4 &vNormal,
	WI_Float radius,
	WI_Float distance );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the intersection point of the line that intersects the plane
WI_Vector4	WI_IntersectionPoint (
	WI_Vector4 vNormal,
	WI_Vector4 vLine[ ],
	double distance );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the point on the line vA_vB that is closest to the point vPoint
WI_Vector4	WI_ClosestPointOnLine (
	WI_Vector4 vA,
	WI_Vector4 vB,
	WI_Vector4 vPoint );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the absolute value of the number passed in
WI_Float	WI_Absolute ( WI_Float num );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the magnitude of a normal ( or any other vector )
WI_Float	WI_Magnitude ( WI_Vector4 vNormal );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the distance between a plane and the origin
WI_Float	WI_PlaneDistance ( WI_Vector4 Normal, WI_Vector4 Point );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This returns the distance between two 3D points
WI_Float	WI_Distance ( WI_Vector4 vPoint1, WI_Vector4 vPoint2 );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This computes the dot product of 2 vectors
WI_Float	WI_DotProduct ( WI_Vector4 vVector1, WI_Vector4 vVector2 );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This tells if a sphere is BEHIND, in FRONT, or INTERSECTS a plane, also its distance
int			WI_ClassifySphere (
	WI_Vector4 &vCenter,
	WI_Vector4 &vNormal,
	WI_Vector4 &vPoint,
	WI_Float radius,
	WI_Float &distance );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
//	This function computes the normals and vertex normals of the objects
//void		WI_ComputeNormals ( tWI3DModel *pModel );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// returns a the next point around a point
WI_Vector4	WI_RotateAroundPoint (
	WI_Vector4 vPosition,
	WI_Vector4 vCenter,
	WI_Float angle,
	WI_Float x,
	WI_Float y,
	WI_Float z );

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// rotates vector x, using u as an axis, by angle 'ang'.
void		WI_RotateWithVector (
	const WI_Vector4 &x,
	WI_Vector4 u,
	WI_Float ang,
	WI_Vector4 &Res );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// calculate an orthonormal matrix with the front vector pointing in the
// dir direction, and the up and right are determined by using the GramSchidth procedure
WI_Matrix	WI_gGrammSchmidt ( const WI_Vector4& dir );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// recalculates the vUp and vRight of a matrix by an angle
// returns the new matrix
WI_Matrix	WI_PitchMatrix ( WI_Float ang );

/////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// recalculates the vFront and vRight of a matrix by an angle
// returns the new matrix
WI_Matrix	WI_YawMatrix ( WI_Float ang );

//////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------------
// recalculates the vFront and vUp of a matrix by an angle
// returns the new matrix
WI_Matrix	WI_RollMatrix ( WI_Float ang );

// end of common math functions
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma message ( "		Widow math core functions..." )
#endif