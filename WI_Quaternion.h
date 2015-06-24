#pragma once

#ifndef __WI_Quaternion__
#define __WI_Quaternion__

//////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------------------
// This is our quaternion class
class WI_Quaternion
{
public:

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This is our default constructor, which initializes everything to an
	// identity quaternion. An identity quaternion has
	// x, y, z as 0 and w as 1.
	WI_Quaternion ( )
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// Creates a constructor that will allow us to initialize the quaternion when creating it
	WI_Quaternion ( WI_Float X, WI_Float Y, WI_Float Z, WI_Float W )
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// Creates a quaternion from a WI_Vector4
	WI_Quaternion ( WI_Vector4 &v )
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This is our operator overloaded multiplication against a scalar
	WI_Quaternion operator*( const WI_Float scalar ) const
	{
		return WI_Quaternion ( x * scalar, y * scalar, z * scalar, w * scalar );
	}

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This is our operator overloaded multiplication against a Vector3
	WI_Vector4 operator*( WI_Vector4 v );

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This is our operator overloaded multiplication against a quaternion
	WI_Quaternion operator*( const WI_Quaternion& q );

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This is our operator overloaded addition against another quaternion
	WI_Quaternion operator+( const WI_Quaternion& q );

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This takes in an array of 16 floats to fill in a 4x4
	// homogeneous matrix from a quaternion
	void CreateMatrix ( WI_Float *pMatrix );

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This takes a 3x3 or 4x4 matrix and converts it to a quaternion,
	// depending on rowColumnCount
	void CreateFromMatrix ( WI_Float *pMatrix, WI_Int rowColumnCount);

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This returns a spherical linear interpolated quaternion between
	// q1 and q2, according to t
	WI_Quaternion Slerp ( WI_Quaternion &q1, WI_Quaternion &q2, WI_Float t );

private:

	//////////////////////////////////////////////////////////////////////////////
	// ---------------------------------------------------------------------------
	// This stores the 4D values for the quaternion
	WI_Float x, y, z, w;
};

#pragma message ( "		Widow 4x4 matrix based quaternion..." )
#endif