#include "LyteGlobals.h"

////////////////////////////// OPERATOR * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This multiplies a quaternion by a WI_Vector4
/////
////////////////////////////// OPERATOR * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

WI_Vector4 WI_Quaternion::operator*( WI_Vector4 v )
{
	// This function is a complex function that calculates the
	// result of multiplying a quaternion by a vector.  We perform
	// three calculations for different parts of the whole equation
	// and then add them all up to return the result:
	//
	// ResultVector =
	// ( vec * ( 2w^2 - 1) ) + (2 * (q_xyz dot vec) * q_xyz) + (2w * (q_xyz cross vec))

	// First we store the x,y,z of the quaternion in a WI_Vector4
	WI_Vector4 q ( x, y, z );

	// The is the first part of the equation: ( vec * ( 2w^2 - 1) )
	WI_Vector4 t1 = v * ( 2.0f * w * w - 1.0f );

	// This is the second part of the equation: (2 * (q_xyz dot vec) * q_xyz)
	WI_Vector4 t2 = 2.0f * q.Dot ( v ) * q;

	// This is the third and final part of the equation: (2 * w * (q_xyz cross vec))
	WI_Vector4 t3 = 2.0f * w * q.Cross( v );

	// Now add up all the vectors and return the final resultant vector
	return t1 + t2 + t3;
}

////////////////////////////// OPERATOR * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This multiplies 2 quaternions and returns the resultant quaternion
/////
////////////////////////////// OPERATOR * \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

WI_Quaternion WI_Quaternion::operator*( const WI_Quaternion& q )
{
	// This is how to multiply a quaternion by a quaternion
	return WI_Quaternion( w * q.x + x * q.w + y * q.z - z * q.y,
					      w * q.y + y * q.w + z * q.x - x * q.z,
					      w * q.z + z * q.w + x * q.y - y * q.x,
					      w * q.w - x * q.x - y * q.y - z * q.z );
}

////////////////////////////// OPERATOR + \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This adds 2 quaternions and returns the resultant quaternion
/////
////////////////////////////// OPERATOR + \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

WI_Quaternion WI_Quaternion::operator+( const WI_Quaternion& q )
{
	// Add the quaternion to the current quaternion and return the result
	return WI_Quaternion ( x + q.x, y + q.y, z + q.z, w + q.w );
}

////////////////////////////// CREATE MATRIX \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function converts a quaternion to a rotation matrix
/////
////////////////////////////// CREATE MATRIX \\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void WI_Quaternion::CreateMatrix ( WI_Float *pMatrix)
{
	// Make sure the matrix has allocated memory to store the rotation data
	if( !pMatrix )
		return;

	// Fill in the rows of the 4x4 matrix, according to the quaternion to matrix equations

	// First row
	pMatrix[ 0 ] = 1.0f - 2.0f * ( y * y + z * z );
	pMatrix[ 1 ] = 2.0f * ( x * y - w * z );
	pMatrix[ 2 ] = 2.0f * ( x * z + w * y );
	pMatrix[ 3 ] = 0.0f;

	// Second row
	pMatrix[ 4 ] = 2.0f * ( x * y + w * z );
	pMatrix[ 5 ] = 1.0f - 2.0f * ( x * x + z * z );
	pMatrix[ 6 ] = 2.0f * ( y * z - w * x );
	pMatrix[ 7 ] = 0.0f;

	// Third row
	pMatrix[ 8 ] = 2.0f * ( x * z - w * y );
	pMatrix[ 9 ] = 2.0f * ( y * z + w * x );
	pMatrix[10 ] = 1.0f - 2.0f * ( x * x + y * y );
	pMatrix[11 ] = 0.0f;

	// Fourth row
	pMatrix[12 ] = 0;
	pMatrix[13 ] = 0;
	pMatrix[14 ] = 0;
	pMatrix[15 ] = 1.0f;

	// Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
}

///////////////////////////////// CREATE FROM MATRIX \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This creates a quaternion from a 3x3 or a 4x4 matrix, depending on rowColumnCount
/////
///////////////////////////////// CREATE FROM MATRIX \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void WI_Quaternion::CreateFromMatrix(WI_Float *pTheMatrix, WI_Int rowColumnCount)
{
	// Make sure the matrix has valid memory and it's not expected that we allocate it.
	// Also, we do a check to make sure the matrix is a 3x3 or a 4x4 (must be 3 or 4).
	if( !pTheMatrix || ( ( rowColumnCount != 3 ) && ( rowColumnCount != 4 ) ) )
		return;

	// This function is used to take in a 3x3 or 4x4 matrix and convert the matrix
	// to a quaternion.  If rowColumnCount is a 3, then we need to convert the 3x3
	// matrix passed in to a 4x4 matrix, otherwise we just leave the matrix how it is.
	// Since we want to apply a matrix to an OpenGL matrix, we need it to be 4x4.

	// Point the matrix pointer to the matrix passed in, assuming it's a 4x4 matrix
	WI_Float *pMatrix = pTheMatrix;

	// Create a 4x4 matrix to convert a 3x3 matrix to a 4x4 matrix (If rowColumnCount == 3)
	WI_Float m4x4[16] = { 0 };

	// If the matrix is a 3x3 matrix (which it is for Quake3), then convert it to a 4x4
	if( rowColumnCount == 3 )
	{
		// Set the 9 top left indices of the 4x4 matrix to the 9 indices in the 3x3 matrix.
		// It would be a good idea to actually draw this out so you can visualize it.
		m4x4[ 0 ] = pTheMatrix[ 0 ];
		m4x4[ 1 ] = pTheMatrix[ 1 ];
		m4x4[ 2 ] = pTheMatrix[ 2 ];

		m4x4[ 4 ] = pTheMatrix[ 3 ];
		m4x4[ 5 ] = pTheMatrix[ 4 ];
		m4x4[ 6 ] = pTheMatrix[ 5 ];

		m4x4[ 8 ] = pTheMatrix[ 6 ];
		m4x4[ 9 ] = pTheMatrix[ 7 ];
		m4x4[ 10] = pTheMatrix[ 8 ];

		// Since the bottom and far right indices are zero, set the bottom right corner to 1.
		// This is so that it follows the standard diagonal line of 1's in the identity matrix.
		m4x4[ 15 ] = 1;

		// Set the matrix pointer to the first index in the newly converted matrix
		pMatrix = &m4x4[ 0 ];
	}

	// The next step, once we made sure we are dealing with a 4x4 matrix, is to check the
	// diagonal of the matrix.  This means that we add up all of the indices that comprise
	// the standard 1's in the identity matrix.  If you draw out the identity matrix of a
	// 4x4 matrix, you will see that the 1's form a diagonal line.  Notice we just assume
	// that the last index (15) is 1 because it is not effected in the 3x3 rotation matrix.

	// Find the diagonal of the matrix by adding up it's diagonal indices.
	// This is also known as the "trace", but I will call the variable diagonal.
	WI_Float diagonal = pMatrix[ 0 ] + pMatrix[ 5 ] + pMatrix[ 10 ] + 1;
	WI_Float scale = 0.0f;

	// Below we check if the diagonal is greater than zero.  To avoid accidents with
	// floating point numbers, we substitute 0 with 0.00000001.  If the diagonal is
	// great than zero, we can perform an "instant" calculation, otherwise we will need
	// to identify which diagonal element has the greatest value.  Note, that it appears
	// that %99 of the time, the diagonal IS greater than 0 so the rest is rarely used.

	// If the diagonal is greater than zero
	if( diagonal > 0.00000001 )
	{
		// Calculate the scale of the diagonal
		scale = ( WI_Sqrt( diagonal ) ) * 2;

		// Calculate the x, y, x and w of the quaternion through the respective equation
		x = ( pMatrix[9] - pMatrix[6] ) / scale;
		y = ( pMatrix[2] - pMatrix[8] ) / scale;
		z = ( pMatrix[4] - pMatrix[1] ) / scale;
		w = 0.25f * scale;
	}
	else
	{
		// If the first element of the diagonal is the greatest value
		if ( pMatrix[0] > pMatrix[5] && pMatrix[0] > pMatrix[10] )
		{
			// Find the scale according to the first element, and double that value
			scale  = WI_Sqrt ( 1.0f + pMatrix[0] - pMatrix[5] - pMatrix[10] ) * 2.0f;

			// Calculate the x, y, x and w of the quaternion through the respective equation
			x = 0.25f * scale;
			y = ( pMatrix[4] + pMatrix[1] ) / scale;
			z = ( pMatrix[2] + pMatrix[8] ) / scale;
			w = ( pMatrix[9] - pMatrix[6] ) / scale;
		}
		// Else if the second element of the diagonal is the greatest value
		else if ( pMatrix[5] > pMatrix[10] )
		{
			// Find the scale according to the second element, and double that value
			scale  = ( WI_Sqrt ( 1.0f + pMatrix[5] - pMatrix[0] - pMatrix[10] ) ) * 2.0f;

			// Calculate the x, y, x and w of the quaternion through the respective equation
			x = ( pMatrix[4] + pMatrix[1] ) / scale;
			y = 0.25f * scale;
			z = ( pMatrix[9] + pMatrix[6] ) / scale;
			w = ( pMatrix[2] - pMatrix[8] ) / scale;
		}
		// Else the third element of the diagonal is the greatest value
		else
		{
			// Find the scale according to the third element, and double that value
			scale  = ( WI_Sqrt ( 1.0f + pMatrix[10] - pMatrix[0] - pMatrix[5] ) ) * 2.0f;

			// Calculate the x, y, x and w of the quaternion through the respective equation
			x = ( pMatrix[2] + pMatrix[8] ) / scale;
			y = ( pMatrix[9] + pMatrix[6] ) / scale;
			z = 0.25f * scale;
			w = ( pMatrix[4] - pMatrix[1] ) / scale;
		}
	}
}

/////////////////////////////////////// SLERP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	Returns a spherical linear interpolated quaternion between q1 and q2, with respect to t
/////
/////////////////////////////////////// SLERP \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

WI_Quaternion WI_Quaternion::Slerp(WI_Quaternion &q1, WI_Quaternion &q2, WI_Float t)
{
	// Create a local quaternion to store the interpolated quaternion
	WI_Quaternion qInterpolated;

	// Here we do a check to make sure the 2 quaternions aren't the same, return q1 if they are
	if( q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w )
		return q1;

	// Following the (b.a) part of the equation, we do a dot product between q1 and q2.
	// We can do a dot product because the same math applied for a 3D vector as a 4D vector.
	WI_Float result = ( q1.x * q2.x ) +
					  ( q1.y * q2.y ) +
					  ( q1.z * q2.z ) +
					  ( q1.w * q2.w );

	// If the dot product is less than 0, the angle is greater than 90 degrees
	if ( result < 0.0f )
	{
		// Negate the second quaternion and the result of the dot product
		q2 = WI_Quaternion ( -q2.x, -q2.y, -q2.z, -q2.w );
		result = -result;
	}

	// Set the first and second scale for the interpolation
	WI_Float scale0 = 1 - t, scale1 = t;

	// Next, we want to actually calculate the spherical interpolation.  Since this
	// calculation is quite computationally expensive, we want to only perform it
	// if the angle between the 2 quaternions is large enough to warrant it.  If the
	// angle is fairly small, we can actually just do a simpler linear interpolation
	// of the 2 quaternions, and skip all the complex math.  We create a "delta" value
	// of 0.1 to say that if the cosine of the angle (result of the dot product) between
	// the 2 quaternions is smaller than 0.1, then we do NOT want to perform the full on
	// interpolation using.  This is because you won't really notice the difference.

	// Check if the angle between the 2 quaternions was big enough to warrant such calculations
	if ( 1 - result > 0.1f )
	{
		// Get the angle between the 2 quaternions, and then store the sin() of that angle
		WI_Float theta = WI_Acos( result );
		WI_Float sinTheta = WI_Sin( theta );

		// Calculate the scale for q1 and q2, according to the angle and it's sine value
		scale0 = ( WI_Sin ( ( 1 - t ) * theta ) ) / sinTheta;
		scale1 = ( WI_Sin ( t * theta ) ) / sinTheta;
	}

	// Calculate the x, y, z and w values for the quaternion by using a special
	// form of linear interpolation for quaternions.
	qInterpolated.x = ( scale0 * q1.x ) + ( scale1 * q2.x );
	qInterpolated.y = ( scale0 * q1.y ) + ( scale1 * q2.y );
	qInterpolated.z = ( scale0 * q1.z ) + ( scale1 * q2.z );
	qInterpolated.w = ( scale0 * q1.w ) + ( scale1 * q2.w );

	// Return the interpolated quaternion
	return qInterpolated;
}