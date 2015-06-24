#include "LyteGlobals.h"

// ------------------------------------------------------
// ------------------------------------------------------
// constructor
WI_Vector4::WI_Vector4 ( const WI_Float x, const WI_Float y, const WI_Float z, const WI_Float w )
:x ( x ), y ( y ), z ( z ), w ( w ) { }

//////////////////////////////////////////////////////////
// init by float pointer
WI_Vector4::WI_Vector4 ( const WI_Float *ptr )
:x ( ptr[ 0 ] ),	y ( ptr[ 1 ] ), z ( ptr[ 2 ] ),	w ( 1.0 ) { }

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// methods

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// sets this vector
void WI_Vector4::Set ( WI_Float X, WI_Float Y, WI_Float Z, WI_Float W )
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

//////////////////////////////////////////////////////////////////////
// scales a vector by scalar S
WI_Vector4 WI_Vector4::Scale ( WI_Float S ) const
{
	return WI_Vector4 ( x * S, y * S, z * S, w );
}

//////////////////////////////////////////////////////////////////////
// returns a vector's dot product
WI_Float WI_Vector4::Dot ( const WI_Vector4 &A ) const
{
	return x * A.x + y * A.y + z * A.z;
}

//////////////////////////////////////////////////////////////////////
// returns this vector's cross product of vV
WI_Vector4 WI_Vector4::Cross ( const WI_Vector4 &B ) const
{
	return WI_Vector4 ( 	y * B.z - z * B.y,
						z * B.x - x * B.z,
						x * B.y - y * B.x, w );
}

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// computes the normal of a vector by a vector
WI_Vector4 WI_Vector4::Normalize ( )
{
	///////////////////////////////////////////////////////////////
	// convert current vals to a vector
	WI_Vector4 vVec		= WI_Vector4 ( x, y, z, w );

	///////////////////////////////////////////////////////////////
	// get the magnitude of the vector
	WI_Float Magnitude = WI_Magnitude ( vVec );

	///////////////////////////////////////////////////////////////
	// Divide the vector's X by the magnitude
	vVec.x /= Magnitude;

	///////////////////////////////////////////////////////////////
	// Divide the vector's Y by the magnitude
	vVec.y /= Magnitude;

	///////////////////////////////////////////////////////////////
	// Divide the vector's Z by the magnitude
	vVec.z /= Magnitude;

	x = vVec.x;
	y = vVec.y;
	z = vVec.z;

	///////////////////////////////////////////////////////////////
	// Return this as the normal
	return *this;
//	return vVec;
}

//////////////////////////////////////////////////////////////////////
// component-wise multiplication
WI_Vector4 WI_Vector4::CompProduct ( const WI_Vector4 &A ) const
{
	return WI_Vector4 ( x * A.x, y * A.y, z * A.z, A.w );
}

//////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// operators

WI_Float& WI_Vector4::operator [ ] ( int i )
{
	return ( &x )[ i ];
}

const WI_Float& WI_Vector4::operator [ ] ( int i ) const
{
	return ( &x )[ i ];
}

WI_Vector4 WI_Vector4::operator + ( const WI_Vector4 &B ) const
{
	return WI_Vector4 ( x + B.x, y + B.y, z + B.z, w );
}

WI_Vector4& WI_Vector4::operator += ( const WI_Vector4 &A )
{
	x += A.x;	y += A.y;	z += A.z;
	return *this;
}

WI_Vector4& WI_Vector4::operator += ( const WI_Float &F )
{
	x += F;	y += F;	z += F;
	return *this;
}

WI_Vector4& WI_Vector4::operator ++ ( )
{
	x ++;	y ++;	z ++;
	return *this;
}

WI_Vector4 WI_Vector4::operator - ( const WI_Vector4 &A ) const
{
	return WI_Vector4 ( x - A.x, y - A.y, z - A.z, w );
}

WI_Vector4& WI_Vector4::operator -= ( const WI_Vector4 &A )
{
	x -= A.x;	y -= A.y;	z -= A.z;
	return *this;
}

WI_Vector4& WI_Vector4::operator -= ( const WI_Float &F )
{
	x -= F;	y -= F;	z -= F;
	return *this;
}

WI_Vector4& WI_Vector4::operator -- ( )
{
	x --;	y --;	z --;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// This is our operator overloaded multiplication of a scalar
WI_Vector4  WI_Vector4::operator * ( const WI_Float scalar ) const
{
	return WI_Vector4 ( x * scalar, y * scalar, z * scalar );
}

//////////////////////////////////////////////////////////////////////
// This is our operator overloaded multiplication agenst a scalar
WI_Vector4&  WI_Vector4::operator *= ( const WI_Float scalar )
{
	x *= scalar;	y *= scalar;	z *= scalar;
	return *this;
}