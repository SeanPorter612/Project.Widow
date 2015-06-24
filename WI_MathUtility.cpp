#include "LyteGlobals.h"

WI_Float WI_Abs ( WI_Float x )
{
	WI_Asm fld	x;
	WI_Asm fabs	;
	WI_Asm fstp	x;
	return x;
}

WI_Float WI_Sqrt ( WI_Float x )
{
	WI_Asm		fld		x;
	WI_Asm		fsqrt;
	WI_Asm		fstp	x;

	return x;
}

WI_Float WI_Sin ( WI_Float x )
{
	WI_Asm		fld		x;
	WI_Asm		fsin;
	WI_Asm		fstp	x;

	return x;
}

WI_Float WI_Cos ( WI_Float x )
{
	WI_Asm		fld		x;
	WI_Asm		fcos;
	WI_Asm		fstp	x;

	return x;
}

WI_Float WI_Asin ( WI_Float x )
{
	WI_Asm	fld	x;
	WI_Asm	fld1;
	WI_Asm	fadd   st,			st ( 1 );
	WI_Asm	fld1;
	WI_Asm	fsub   st,			st ( 2 );
	WI_Asm	fmulp  st ( 1 ),	st;

	WI_Asm	fsqrt;
	WI_Asm	fpatan;
	WI_Asm	fstp	x;

	return x;
}

WI_Float WI_Acos ( WI_Float x )
{
	WI_Asm	fld		x;
	WI_Asm	fld1;

	WI_Asm	fadd   st,	st ( 1 );
	WI_Asm	fld1;
	WI_Asm	fsub   st,	st ( 2 );
	WI_Asm	fmulp  st ( 1 ),		st;

	WI_Asm	fsqrt;

	WI_Asm	fxch   st ( 1 );

	WI_Asm	fpatan;

	WI_Asm	fstp	x;

	return x;
}

WI_Float WI_Atan2 ( WI_Float x, WI_Float y )
{
	WI_Asm	fld		x;
	WI_Asm	fld		y;
	WI_Asm	fpatan;
	WI_Asm	fstp	x;

	return x;
}

WI_Float WI_Floor ( WI_Float x )
{
	WI_Int		tmp;
	WI_Int		controlworld;

	WI_Asm_		fld				x;
	WI_Asm_		fnstcw			controlworld;

	WI_Asm_		mov				eax,			controlworld;
	WI_Asm_		and				eax,			WI_ROUND_MASK;
	WI_Asm_		or				eax,			WI_ROUND_DOWN;
	WI_Asm_		mov				tmp,			eax;
	WI_Asm_		fldcw			tmp;

	WI_Asm_		frndint;

	WI_Asm_		fldcw			controlworld;
	WI_Asm_		fstp			x;

	return x;
}

WI_Int WI_FastInt ( WI_Float x )
{
	WI_Int		tmp;
	WI_Int		integer;
	WI_Int		controlworld;

	WI_Asm_		fld			x;
	WI_Asm_		fnstcw		controlworld;

	WI_Asm_		mov			eax,			controlworld;
	WI_Asm_		and			eax,			WI_ROUND_MASK;
	WI_Asm_		or			eax,			WI_ROUND_DOWN;
	WI_Asm_		mov			tmp,			eax;

	WI_Asm_		fldcw		tmp;
	WI_Asm_		fistp		integer;
	WI_Asm_		fldcw		controlworld;

	return integer;
}

WI_Inline void WI_SinCos ( WI_Float ang, WI_Float& sinAng, WI_Float& cosAng )
{
	sinAng = WI_Sin( ang );
	cosAng = WI_Cos( ang );
}

WI_Inline WI_Int WI_AtomicAdd ( WI_Int* addend, WI_Int amount )
{
	#if ( defined ( WINVER  ) || defined ( _MINGW_32_VER ) || defined ( _MINGW_64_VER ) )

		return InterlockedExchangeAdd( (WI_Long* ) addend, WI_Long ( amount ) );

	#endif

	#if ( defined ( _LINUX ) )

		return __sync_fetch_and_add ( ( int32_t* )addend, amount );

	#endif

	#if ( defined ( _MAC ) )

		WI_Int count = OSAtomicAdd32 ( amount, ( int32_t* )addend );
		return count - ( *addend );

	#endif
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input float to int
WI_Int WI_FloatToInt ( WI_Float val )
{
	WI_Int whole_part = ( WI_Int )val;

	WI_Float exp_part = whole_part + 0.5f;

	if ( val >= exp_part && val < whole_part + 1 )
		return whole_part + 1;

	return whole_part;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input int to float
WI_Float WI_IntToFloat ( WI_Int val )
{
	WI_Int whole_part = ( WI_Int )val;

	WI_Double exp_part = whole_part + 0.5;

	if ( val >= exp_part && val < whole_part + 1 )
		return whole_part * 1.0f;

	return whole_part * 1.0f;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input float to Double
WI_Double WI_FloatToDouble ( WI_Float val )
{
	WI_Double whole_part = ( WI_Int )val;

	WI_Double exp_part = whole_part + 0.5;

	if ( val >= exp_part && val < whole_part + 1 )
		return whole_part + 1;

	return whole_part;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// rounds input Double to float
WI_Float WI_DoubleToFloat ( WI_Double val )
{
	WI_Float whole_part = ( WI_Float )val;

	WI_Float exp_part = ( WI_Float )whole_part + 0.5f;

	if ( val >= exp_part && val < whole_part + 1 )
		return whole_part + 1;

	return whole_part;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
//	This multiplies a scalar by a WI_Vector4 and returns a WI_Vector4
WI_Vector4 operator* ( WI_Float scalar, const WI_Vector4& v )
{
	// Return the multiplied scalar by the vector
	return WI_Vector4 ( v.x * scalar, v.y * scalar, v.z * scalar );
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This adds 2 vectors together and returns the result
WI_Vector4 WI_AddVector ( WI_Vector4 vVector1, WI_Vector4 vVector2 )
{
	WI_Vector4 vResult;							// The variable to hold the resultant vector

	vResult.x = vVector2.x + vVector1.x;		// Add Vector1 and Vector2 x's
	vResult.y = vVector2.y + vVector1.y;		// Add Vector1 and Vector2 y's
	vResult.z = vVector2.z + vVector1.z;		// Add Vector1 and Vector2 z's
	vResult.w = vVector1.w;

	return vResult;								// Return the resultant vector
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This divides a vector by a single number ( scalar ) and returns the result
WI_Vector4 WI_DivideVectorByScaler ( WI_Vector4 vVector1, WI_Float Scaler )
{
	WI_Vector4 vResult;							// The variable to hold the resultant vector

	vResult.x = vVector1.x / Scaler;			// Divide Vector1's x value by the scaler
	vResult.y = vVector1.y / Scaler;			// Divide Vector1's y value by the scaler
	vResult.z = vVector1.z / Scaler;			// Divide Vector1's z value by the scaler
	vResult.w = vVector1.w;

	return vResult;								// Return the resultant vector
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the normal of a vector
WI_Vector4 WI_Normalize ( WI_Vector4 vNormal )
{
	double Magnitude;							// This holds the magnitude

	Magnitude = WI_Magnitude ( vNormal );		// Get the magnitude

	vNormal.x /= ( WI_Float )Magnitude;				// Divide the vector's X by the magnitude
	vNormal.y /= ( WI_Float )Magnitude;				// Divide the vector's Y by the magnitude
	vNormal.z /= ( WI_Float )Magnitude;				// Divide the vector's Z by the magnitude

	return vNormal;								// Return the normal
}
///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the absolute value of the number passed in
WI_Float WI_Absolute ( WI_Float num )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// If num is less than zero, we want to return the absolute value of num.
	// This is simple, either we times num by -1 or subtract it from 0.
	if ( num < 0 )
	{
		return ( 0 - num );
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the original number because it was already positive
	return num;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns a perpendicular vector from 2 given vectors by taking the cross product.
WI_Vector4 WI_Cross ( WI_Vector4 vVector1, WI_Vector4 vVector2 )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// The vector to hold the cross product
	WI_Vector4 vNormal;

	///////////////////////////////////////////////////////////////////////////////////////
	// The X value for the vector is:  ( V1.y * V2.z ) - ( V1.z * V2.y )													// Get the X value
	vNormal.x = ( ( vVector1.y * vVector2.z ) - ( vVector1.z * vVector2.y ) );

	///////////////////////////////////////////////////////////////////////////////////////
	// The Y value for the vector is:  ( V1.z * V2.x ) - ( V1.x * V2.z )
	vNormal.y = ( ( vVector1.z * vVector2.x ) - ( vVector1.x * vVector2.z ) );

	///////////////////////////////////////////////////////////////////////////////////////
	// The Z value for the vector is:  ( V1.x * V2.y ) - ( V1.y * V2.x )
	vNormal.z = ( ( vVector1.x * vVector2.y ) - ( vVector1.y * vVector2.x ) );

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the cross product ( Direction the polygon is facing - Normal )
	return vNormal;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the magnitude of a normal ( or any other vector )
WI_Float WI_Magnitude ( WI_Vector4 vNormal )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// magnitude = sqrt ( V.x ^ 2 + V.y ^ 2 + V.z ^ 2 )
	// Where V is the vector
	WI_Float x = vNormal.x * vNormal.x;
	WI_Float y = vNormal.y * vNormal.y;
	WI_Float z = vNormal.z * vNormal.z;

	WI_Float w = x + y + z;

	return WI_Sqrt ( w );
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
//	Returns true if collided
bool WI_SpherePolygonCollision ( WI_Vector4 vPolygon[ ], WI_Vector4 &vCenter, WI_Int vertexCount, WI_Float radius )
{
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// 1 ) STEP ONE - Finding the sphere's classification
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Let's use our Normal ( ) function to return us the normal to this polygon
	WI_Vector4 vNormal = WI_Normal ( vPolygon );

	///////////////////////////////////////////////////////////////////////////////////////
	// This will store the distance our sphere is from the plane
	WI_Float distance = 0.0f;

	///////////////////////////////////////////////////////////////////////////////////////
	// This is where we determine if the sphere is in FRONT, BEHIND, or INTERSECTS the plane
	// of the polygon.  We pass is our sphere center, the polygon's normal, a point on
	// the plane ( vertex ), the sphere's radius and an empty WI_Float to fill the distance with.
	WI_Int classification = WI_ClassifySphere ( vCenter, vNormal, vPolygon[ 0 ], radius, distance );

	///////////////////////////////////////////////////////////////////////////////////////
	// If the sphere intersects the polygon's plane, then we need to check further,
	// otherwise the sphere did NOT intersect the polygon.  Pretty fast so far huh?
	if ( classification == INTERSECTS )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////
		// 2 ) STEP TWO - Finding the pseudo intersection point on the plane
		///////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////

		WI_Vector4 vOffset;
		vOffset.x = vNormal.x * distance;
		vOffset.y = vNormal.y * distance;
		vOffset.z = vNormal.z * distance;

		///////////////////////////////////////////////////////////////////////////////////////
		// Once we have the offset to the plane, we just subtract it from the center
		// of the sphere.  "vPosition" now a point that lies on the plane of the polygon.
		// Whether it is inside the polygon's perimeter is another story.  Usually it
		// is though, unless we get near the edges of the polygon.
		WI_Vector4 vPosition = vCenter - vOffset;

		///////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////
		// 3 ) STEP THREE - Check if the intersection point is inside the polygons perimeter
		///////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////
		// This is the same function used in our previous tutorial on Ray to Polygon Collision.
		// If the intersection point is inside the perimeter of the polygon, it returns true.
		// We pass in the intersection point, the list of vertices and vertex count of the poly.
		if ( WI_InsidePolygon ( vPosition, vPolygon, vertexCount ) )
		{
			///////////////////////////////////////////////////////////////////////////////////////
			// We collided!
			return true;
		}
		else
		{
			if ( WI_EdgeSphereCollision ( vCenter, vPolygon, vertexCount, radius ) )
			{
				///////////////////////////////////////////////////////////////////////////////////////
				// We collided! "And you doubted me..." - Sphere
				return true;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If we get here, there is obviously no collision happening up in this crib
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This calculates a vector between 2 points and returns the result
WI_Vector4 WI_VectorBetween2Points ( WI_Vector4 vPoint1, WI_Vector4 vPoint2 )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// The variable to hold the resultant vector
	WI_Vector4 vVector = WI_Vector4 ( );

	///////////////////////////////////////////////////////////////////////////////////////
	// Subtract point1 and point2 x's
	vVector.x = vPoint1.x - vPoint2.x;

	///////////////////////////////////////////////////////////////////////////////////////
	// Subtract point1 and point2 y's
	vVector.y = vPoint1.y - vPoint2.y;

	///////////////////////////////////////////////////////////////////////////////////////
	// Subtract point1 and point2 z's
	vVector.z = vPoint1.z - vPoint2.z;

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the resultant vector
	return vVector;
}

/////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------
//// This function computes the normals and vertex normals of the objects
//void WI_ComputeNormals ( tWI3DModel *pModel )
//{
//	WI_Vector4 vVector1;
//	WI_Vector4 vVector2;
//	WI_Vector4 vNormal;
//	WI_Vector4 vPoly[ 3 ];
//
//	///////////////////////////////////////////////////////////////////////////////////////
//	// If there are no objects, we can skip this part
//	if ( pModel->m_iObjectCount <= 0 || pModel->m_ObjectArr.size ( ) == 0 )
//	{
//		return;
//	}
//
//	///////////////////////////////////////////////////////////////////////////////////////
//	// Go through each of the objects to calculate their normals
//	for ( WI_Int index = 0; index < pModel->m_iObjectCount; index++ )
//	{
//		///////////////////////////////////////////////////////////////////////////////////////
//		// Get the current object
//		tWI3DObject *pObject = & ( pModel->m_ObjectArr[ index ] );
//
//		///////////////////////////////////////////////////////////////////////////////////////
//		// Here we allocate all the memory we need to calculate the normals
//		WI_Vector4 *pNormals		= new WI_Vector4 [ pObject->m_iNumOfFaces ];
//		WI_Vector4 *pTempNormals	= new WI_Vector4 [ pObject->m_iNumOfFaces ];
//		pObject->m_pNormals		= new WI_Vector4 [ pObject->m_iNumOfVerts ];
//
//		///////////////////////////////////////////////////////////////////////////////////////
//		// Go though all of the faces of this object
//		for ( WI_Int i=0; i < pObject->m_iNumOfFaces; i++ )
//		{
//			///////////////////////////////////////////////////////////////////////////////////////
//			// To cut down LARGE code, we extract the 3 points of this face
//			vPoly[ 0 ] = pObject->m_pVerts[ pObject->m_pFaces[ i ].vertIndex[ 0 ] ];
//			vPoly[ 1 ] = pObject->m_pVerts[ pObject->m_pFaces[ i ].vertIndex[ 1 ] ];
//			vPoly[ 2 ] = pObject->m_pVerts[ pObject->m_pFaces[ i ].vertIndex[ 2 ] ];
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Now let's calculate the face normals ( Get 2 vectors and find the cross product of those 2 )
//			///////////////////////////////////////////////////////////////////////////////////////
//			///////////////////////////////////////////////////////////////////////////////////////
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Get the vector of the polygon ( we just need 2 sides for the normal )
//			vVector1 = WI_VectorBetween2Points ( vPoly[ 0 ], vPoly[ 2 ] );
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Get a second vector of the polygon
//			vVector2 = WI_VectorBetween2Points ( vPoly[ 2 ], vPoly[ 1 ] );
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Return the cross product of the 2 vectors ( normalize vector, but not a unit vector )
//			vNormal  = WI_Cross ( vVector1, vVector2 );
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Save the un-normalized normal for the vertex normals
//			pTempNormals[ i ] = vNormal;
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Normalize the cross product to give us the polygons normal
//			vNormal  = WI_Normalize ( vNormal );
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Assign the normal to the list of normals
//			pNormals[ i ] = vNormal;
//		}
//
//		//////////////// Now Get The Vertex Normals /////////////////
//		WI_Vector4	vSum		=	WI_Vector4 ( );
//		WI_Vector4	vZero		=	vSum;
//		WI_Int		iShared		=	0;
//
//		///////////////////////////////////////////////////////////////////////////////////////
//		// Go through all of the vertices
//		for ( WI_Int i = 0; i < pObject->m_iNumOfVerts; i++ )
//		{
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Go through all of the triangles
//			for ( WI_Int j = 0; j < pObject->m_iNumOfFaces; j++ )
//			{
//				///////////////////////////////////////////////////////////////////////////////////////
//				// Check if the vertex is shared by another face
//				if ( pObject->m_pFaces[ j ].vertIndex[ 0 ] == i || pObject->m_pFaces[ j ].vertIndex[ 1 ] == i || pObject->m_pFaces[ j ].vertIndex [ 2 ] == i )
//				{
//					///////////////////////////////////////////////////////////////////////////////////////
//					// Add the un-normalized normal of the shared face
//					vSum = WI_AddVector ( vSum, pTempNormals[ j ] );
//
//					///////////////////////////////////////////////////////////////////////////////////////
//					// Increase the number of shared triangles
//					iShared++;
//				}
//			}
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Get the normal by dividing the sum by the shared.  We negate the shared so it has the normals pointing out.
//			pObject->m_pNormals[ i ] = WI_DivideVectorByScaler ( vSum, WI_Float ( -iShared ) );
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Normalize the normal for the final vertex normal
//			pObject->m_pNormals[ i ] = WI_Normalize ( pObject->m_pNormals[ i ] );
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Reset the sum
//			vSum = vZero;
//
//			///////////////////////////////////////////////////////////////////////////////////////
//			// Reset the shared
//			iShared = 0;
//		}
//		///////////////////////////////////////////////////////////////////////////////////////
//		// Free our memory and start over on the next object
//		WI_DELETE_PTR ( pTempNormals );
//		WI_DELETE_PTR ( pNormals );
//	}
//}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
//	This returns the normal of a polygon ( The direction the polygon is facing )
WI_Vector4 WI_Normal ( WI_Vector4 vPolygon[ ] )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// Get 2 vectors from the polygon ( 2 sides ), Remember the order!
	WI_Vector4 vVector1 = vPolygon[ 2 ] - vPolygon[ 0 ];
	WI_Vector4 vVector2 = vPolygon[ 1 ] - vPolygon[ 0 ];

	///////////////////////////////////////////////////////////////////////////////////////
	// Take the cross product of our 2 vectors to get a perpendicular vector
	WI_Vector4 vNormal		=		WI_Cross ( vVector1, vVector2 );

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// Now we have a normal, but it's at a strange length, so let's make it length 1.
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Use our function we created to normalize the normal ( Makes it a length of one )
	vNormal = WI_Normalize ( vNormal );

	///////////////////////////////////////////////////////////////////////////////////////
	// Return our normal at our desired length
	return vNormal;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the distance between a plane and the origin
WI_Float WI_PlaneDistance ( WI_Vector4 Normal, WI_Vector4 Point )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// This variable holds the distance from the plane tot he origin
	WI_Float fDistance = 0.0f;

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// Use the plane equation to find the distance ( Ax + By + Cz + D = 0 )  We want to find D.
	// So, we come up with D = - ( Ax + By + Cz )
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Basically, the negated dot product of the normal of the plane and the point. ( More about the dot product in another tutorial )
	fDistance = - ( ( Normal.x * Point.x ) + ( Normal.y * Point.y ) + ( Normal.z * Point.z ) );

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the distance
	return fDistance;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This checks to see if a line intersects a plane
bool WI_IntersectedPlane ( WI_Vector4 vPoly[ ], WI_Vector4 vLine[ ], WI_Vector4 &vNormal, WI_Float &originDistance )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// The distances from the 2 points of the line from the plane
	WI_Float distance1 = 0, distance2 = 0;

	///////////////////////////////////////////////////////////////////////////////////////
	// We need to get the normal of our plane to go any further
	vNormal = WI_Normal ( vPoly );

	///////////////////////////////////////////////////////////////////////////////////////
	// Let's find the distance our plane is from the origin.  We can find this value
	// from the normal to the plane ( polygon ) and any point that lies on that plane ( Any vertex )
	originDistance = WI_PlaneDistance ( vNormal, vPoly[ 0 ] );

	///////////////////////////////////////////////////////////////////////////////////////
	// Get the distance from point1 from the plane using: Ax + By + Cz + D = ( The distance from the plane )
	distance1 = ( ( vNormal.x * vLine[ 0 ].x )   +					// Ax +
				  ( vNormal.y * vLine[ 0 ].y )   +					// Bx +
				  ( vNormal.z * vLine[ 0 ].z ) ) + originDistance;	// Cz + D

	///////////////////////////////////////////////////////////////////////////////////////
	// Get the distance from point2 from the plane using Ax + By + Cz + D = ( The distance from the plane )
	distance2 = ( ( vNormal.x * vLine[ 1 ].x )   +					// Ax +
				  ( vNormal.y * vLine[ 1 ].y )   +					// Bx +
				  ( vNormal.z * vLine[ 1 ].z ) ) + originDistance;	// Cz + D

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// Now that we have 2 distances from the plane, if we times them together we either
	// get a positive or negative number.  If it's a negative number, that means we collided!
	// This is because the 2 points must be on either side of the plane ( IE. -1 * 1 = -1 ).
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Check to see if both point's distances are both negative or both positive
	if ( distance1 * distance2 >= 0 )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the plane.  -1 -2 or 3 4 wouldn't...
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// The line intersected the plane, Return TRUE
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This computers the dot product of 2 vectors
WI_Float WI_DotProduct ( WI_Vector4 vVector1, WI_Vector4 vVector2 )
{
	///////////////////////////////////////////////////////////////////////////////////////
	//   ( V1.x * V2.x        +
	//		V1.y * V2.y        +
	//		V1.z * V2.z )

	WI_Float	Dot =	( vVector1.x * vVector2.x ) +
						( vVector1.y * vVector2.y ) +
						( vVector1.z * vVector2.z );

	return ( Dot );
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This checks to see if a point is inside the ranges of a polygon
double WI_AngleBetweenVectors ( WI_Vector4 Vector1, WI_Vector4 Vector2 )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// Get the dot product of the vectors
	WI_Double dotProduct = WI_DotProduct ( Vector1, Vector2 );

	///////////////////////////////////////////////////////////////////////////////////////
	// Get the product of both of the vectors' magnitudes
	WI_Double vectorsMagnitude = WI_Magnitude ( Vector1 ) * WI_Magnitude ( Vector2 ) ;

	///////////////////////////////////////////////////////////////////////////////////////
	// Get the angle in radians between the 2 vectors
	WI_Double angle = WI_Acos ( dotProduct / vectorsMagnitude );

	///////////////////////////////////////////////////////////////////////////////////////
	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinite
//	if ( _isnan ( angle ) )
//		return 0;

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the angle in radians
	return ( angle );
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the intersection point of the line that intersects the plane
WI_Vector4 WI_IntersectionPoint ( WI_Vector4 vNormal, WI_Vector4 vLine[ ], WI_Double iDistance )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// Variables to hold the point and the line's direction
	WI_Vector4 vPoint = WI_Vector4 ( ), vLineDir = WI_Vector4 ( );

	WI_Double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// 1 )  First we need to get the vector of our line, Then normalize it so it's a length of 1
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Get the Vector of the line
	vLineDir = vLine[ 1 ] - vLine[ 0 ];

	///////////////////////////////////////////////////////////////////////////////////////
	// Normalize the line's vector
	vLineDir = WI_Normalize ( vLineDir );

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// 2 ) Use the plane equation ( distance = Ax + By + Cz + D ) to find the
	// distance from one of our points to the plane.
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Use the plane equation with the normal and the line
	Numerator = - ( vNormal.x * vLine[ 0 ].x +
				    vNormal.y * vLine[ 0 ].y +
				    vNormal.z * vLine[ 0 ].z + iDistance );

	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	// 3 ) If we take the dot product between our line
	// vector and the normal of the polygon,
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////
	// Get the dot product of the line's vector and the normal of the plane
	Denominator = WI_DotProduct ( vNormal, vLineDir );

	///////////////////////////////////////////////////////////////////////////////////////
	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINITE points because the the line is
	// on the plane ( the normal is perpendicular to the line - ( Normal.Vector = 0 ) ).
	// In this case, we should just return any point on the line.

	///////////////////////////////////////////////////////////////////////////////////////
	// Check so we don't divide by zero
	if ( Denominator == 0.0 )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// Return an arbitrary point on the line
		return vLine[ 0 ];
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// Divide to get the multiplying ( percentage ) factor
	dist = Numerator / Denominator;

	///////////////////////////////////////////////////////////////////////////////////////
	// Now, like we said above, we times the dist by the vector,
	// then add our arbitrary point.
	vPoint.x = ( WI_Float ) ( vLine[ 0 ].x + ( vLineDir.x * dist ) );
	vPoint.y = ( WI_Float ) ( vLine[ 0 ].y + ( vLineDir.y * dist ) );
	vPoint.z = ( WI_Float ) ( vLine[ 0 ].z + ( vLineDir.z * dist ) );

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the intersection point
	return vPoint;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This checks to see if a point is inside the ranges of a polygon
bool WI_InsidePolygon ( WI_Vector4 vIntersection, WI_Vector4 Poly[ ], WI_Long verticeCount )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// Used to cover up the error in WI_Floating point
	const WI_Double MATCH_FACTOR = 0.99;

	///////////////////////////////////////////////////////////////////////////////////////
	// Initialize the angle
	WI_Double Angle = 0.0;

	///////////////////////////////////////////////////////////////////////////////////////
	// Create temp vectors
	WI_Vector4 vA, vB;

	///////////////////////////////////////////////////////////////////////////////////////
	// Go in a circle to each vertex and get the angle between
	for ( WI_Int i = 0; i < verticeCount; i++ )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// Subtract the intersection point from the current vertex
		vA = Poly[ i ] - vIntersection;

		///////////////////////////////////////////////////////////////////////////////////////
		// Subtract the point from the next vertex
		vB = Poly[  ( i + 1 ) % verticeCount ] - vIntersection;

		///////////////////////////////////////////////////////////////////////////////////////
		// Find the angle between the 2 vectors and add them all up as we go along
		Angle += WI_AngleBetweenVectors ( vA, vB );
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If the angle is greater than 2 PI, ( 360 degrees )
	if ( Angle >= ( MATCH_FACTOR * ( 2.0 * WI_PI ) ) )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// The point is inside of the polygon
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If you get here, it obviously wasn't inside the polygon, so Return FALSE
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This checks if a line is intersecting a polygon
bool WI_IntersectedPolygon ( WI_Vector4 vPoly[ ], WI_Vector4 vLine[ ], WI_Int verticeCount )
{
	WI_Vector4 vNormal;
	WI_Float originDistance = 0;

	///////////////////////////////////////////////////////////////////////////////////////
	// First, make sure our line intersects the plane
	if ( !WI_IntersectedPlane ( vPoly, vLine,   vNormal,   originDistance ) )
	{
		return false;
	}
	///////////////////////////////////////////////////////////////////////////////////////
	// Now that we have our normal and distance passed back from IntersectedPlane ( ),
	// we can use it to calculate the intersection point.
	WI_Vector4 vIntersection = WI_IntersectionPoint ( vNormal, vLine, originDistance );

	///////////////////////////////////////////////////////////////////////////////////////
	// Now that we have the intersection point, we need to test if it's inside the polygon.
	if ( WI_InsidePolygon ( vIntersection, vPoly, verticeCount ) )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// We collided!	  Return success
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// There was no collision, so return false
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the distance between 2 3D points
WI_Float WI_Distance ( WI_Vector4 vPoint1, WI_Vector4 vPoint2 )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// This is the classic formula used in beginning algebra to return the
	// distance between 2 points.  Since it's 3D, we just add the z dimension:
	//
	// Distance = sqrt (  ( P2.x - P1.x )^2 + ( P2.y - P1.y )^2 + ( P2.z - P1.z )^2 )
	WI_Float x = ( vPoint2.x - vPoint1.x ) * ( vPoint2.x - vPoint1.x );
	WI_Float y = ( vPoint2.y - vPoint1.y ) * ( vPoint2.y - vPoint1.y );
	WI_Float z = ( vPoint2.z - vPoint1.z ) * ( vPoint2.z - vPoint1.z );

	WI_Float distance = sqrt ( x + y + z );

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the distance between the 2 points
	return ( WI_Float )distance;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This returns the point on the line vA_vB that is closest to the point vPoint
WI_Vector4 WI_ClosestPointOnLine ( WI_Vector4 vA, WI_Vector4 vB, WI_Vector4 vPoint )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// Create the vector from end point vA to our point vPoint.
	WI_Vector4 vVector1 = vPoint - vA;

	///////////////////////////////////////////////////////////////////////////////////////
	// Create a normalized direction vector from end point vA to end point vB
	WI_Vector4 vVector2 = WI_Normalize ( vB - vA );

	///////////////////////////////////////////////////////////////////////////////////////
	// Use the distance formula to find the distance of the line segment ( or magnitude )
	WI_Float d = WI_Distance ( vA, vB );

	///////////////////////////////////////////////////////////////////////////////////////
	// Using the dot product, we project the vVector1 onto the vector vVector2.
	// This essentially gives us the distance from our projected vector from vA.
	WI_Float t = WI_DotProduct ( vVector2, vVector1 );

	///////////////////////////////////////////////////////////////////////////////////////
	// If our projected distance from vA, "t", is less than or equal to 0, it must
	// be closest to the end point vA.  We want to return this end point.
	if ( t <= 0 )
	{
		return vA;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If our projected distance from vA, "t", is greater than or equal to the magnitude
	// or distance of the line segment, it must be closest to the end point vB.  So, return vB.
	if ( t >= d )
	{
		return vB;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// Here we create a vector that is of length t and in the direction of vVector2
	WI_Vector4 vVector3;

	vVector3.x = vVector2.x * t;
	vVector3.y = vVector2.y * t;
	vVector3.z = vVector2.z * t;

	///////////////////////////////////////////////////////////////////////////////////////
	// To find the closest point on the line segment, we just add vVector3 to the original
	// end point vA.
	WI_Vector4 vClosestPoint = vA + vVector3;

	///////////////////////////////////////////////////////////////////////////////////////
	// Return the closest point on the line segment
	return vClosestPoint;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// This tells if a sphere is BEHIND, in FRONT, or INTERSECTS a plane, also it's distance
WI_Int WI_ClassifySphere ( WI_Vector4 &vCenter, WI_Vector4 &vNormal, WI_Vector4 &vPoint, WI_Float radius, WI_Float &distance )
{
	///////////////////////////////////////////////////////////////////////////////////////
	// First we need to find the distance our polygon plane is from the origin.
	// We need this for the distance formula below.
	WI_Float d = ( WI_Float )WI_PlaneDistance ( vNormal, vPoint );

	///////////////////////////////////////////////////////////////////////////////////////
	// Here we use the famous distance formula to find the distance the center point
	// of the sphere is from the polygon's plane.
	// Remember that the formula is Ax + By + Cz + d = 0 with ABC = Normal, XYZ = Point
	distance = ( vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d );

	///////////////////////////////////////////////////////////////////////////////////////
	// If the absolute value of the distance we just found is less than the radius,
	// the sphere intersected the plane.
	if ( WI_Absolute ( distance ) < radius )
	{
		return INTERSECTS;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// Else, if the distance is greater than or equal to the radius, the sphere is
	// completely in FRONT of the plane.
	else if ( distance >= radius )
	{
		return FRNT;
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If the sphere isn't intersecting or in FRONT of the plane, it must be BEHIND
	return BEHIND;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
//	This returns true if the sphere is intersecting any of the edges of the polygon
bool WI_EdgeSphereCollision ( WI_Vector4 &vCenter, WI_Vector4 vPolygon[ ], WI_Int vertexCount, WI_Float radius )
{
	WI_Vector4 vPoint;

	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	// This function takes in the sphere's center, the polygon's vertices, the vertex count
	// and the radius of the sphere.  We will return true from this function if the sphere
	// is intersecting any of the edges of the polygon.  How it works is, every edge line
	// segment finds the closest point on that line to the center of the sphere.  If the
	// distance from that closest point is less than the radius of the sphere, there was
	// a collision.  Otherwise, we are definately out of reach of the polygon.  This works
	// for triangles, quads, and any other convex polygons.
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////
	// Go through all of the vertices in the polygon
	for ( WI_Int i = 0; i < vertexCount; i++ )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// This returns the closest point on the current edge to the center of the sphere.
		// Notice that we mod the second point of the edge by our vertex count.  This is
		// so that when we get to the last edge of the polygon, the second vertex of the
		// edge is the first vertex that we starting with.
		vPoint = WI_ClosestPointOnLine ( vPolygon[ i ], vPolygon[  ( i + 1 ) % vertexCount ], vCenter );

		///////////////////////////////////////////////////////////////////////////////////////
		// Now, we want to calculate the distance between the closest point and the center
		WI_Float distance = WI_Distance ( vPoint, vCenter );

		///////////////////////////////////////////////////////////////////////////////////////
		// If the distance is less than the radius, there must be a collision so return true
		if ( distance < radius )
		{
			return true;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////
	// The was no intersection of the sphere and the edges of the polygon
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------------------
// Set the collision offset by a vector
WI_Vector4 WI_GetCollisionOffset ( WI_Vector4 &vNormal, WI_Float radius, WI_Float distance )
{
	WI_Vector4 vOffset = WI_Vector4 ( 0, 0, 0 );

	////////////////////////////////////////////////////////////////////////////////////////////
	// If our distance is greater than zero, we are in front of the polygon
	if ( distance > 0 )
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		// Find the distance that our sphere is overlapping the plane, then
		// find the direction vector to move our sphere.
		WI_Float distanceOver = radius - distance;

		vOffset.x = vNormal.x * distanceOver;
		vOffset.y = vNormal.y * distanceOver;
		vOffset.z = vNormal.z * distanceOver;
	}
	else
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////
		// Else colliding from behind the polygon
		////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////
		// Find the distance that our sphere is overlapping the plane, then
		// find the direction vector to move our sphere.
		WI_Float distanceOver = radius + distance;
		vOffset.x = vNormal.x * -distanceOver;
		vOffset.y = vNormal.y * -distanceOver;
		vOffset.z = vNormal.z * -distanceOver;
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	// Return the offset we need to move back to not be intersecting the polygon.
	return vOffset;
}

////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------
// rotate a vector around a point
WI_Vector4 WI_RotateAroundPoint ( WI_Vector4 vPosition, WI_Vector4 vCenter, WI_Float angle, WI_Float x, WI_Float y, WI_Float z )
{
	///////////////////////////////////////////////////
	// return position vector
	WI_Vector4 vNewPosition = WI_Vector4 ( );

	///////////////////////////////////////////////////
	// Get the vVector from our position to the
	// center we are rotating around
	WI_Vector4 vPos = vPosition - vCenter;

	///////////////////////////////////////////////////
	// Calculate the sine and cosine of the angle once
	WI_Float cosTheta = WI_Cos ( angle );
	WI_Float sinTheta = WI_Sin ( angle );

	///////////////////////////////////////////////////
	// Find the new x position for the new rotated point
	vNewPosition.x  = ( cosTheta + ( 1 - cosTheta ) * x * x )		* vPos.x;
	vNewPosition.x += ( ( 1 - cosTheta ) * x * y - z * sinTheta )	* vPos.y;
	vNewPosition.x += ( ( 1 - cosTheta ) * x * z + y * sinTheta )	* vPos.z;

	///////////////////////////////////////////////////
	// Find the new y position for the new rotated point
	vNewPosition.y  = ( ( 1 - cosTheta ) * x * y + z * sinTheta )	* vPos.x;
	vNewPosition.y += ( cosTheta + ( 1 - cosTheta ) * y * y )		* vPos.y;
	vNewPosition.y += ( ( 1 - cosTheta ) * y * z - x * sinTheta )	* vPos.z;

	///////////////////////////////////////////////////
	// Find the new z position for the new rotated point
	vNewPosition.z  = ( ( 1 - cosTheta ) * x * z - y * sinTheta )	* vPos.x;
	vNewPosition.z += ( ( 1 - cosTheta ) * y * z + x * sinTheta )	* vPos.y;
	vNewPosition.z += ( cosTheta + ( 1 - cosTheta ) * z * z )		* vPos.z;

	///////////////////////////////////////////////////
	// Now we just add the newly rotated vector
	// to our position to set our new rotated
	// position of our camera.
	vPosition = vCenter + vNewPosition;

	///////////////////////////////////////////////////
	// return the position
	return vPosition;
}

//////////////////////////////////////////////////////////////////////
// rotates vector x, using u as an axis, by angle 'ang'.
void WI_RotateWithVector ( const WI_Vector4 &x, WI_Vector4 u, WI_Float ang, WI_Vector4 &Res )
{
	WI_Vector4 U, h, v, uxx;

	U = WI_Normalize ( u );

	uxx		= U.Cross ( x ).CompProduct ( ( WI_Sin ( ang ) ) );
	h		= U.Dot ( ( x.CompProduct ( U ) ) );
	v		= ( x - h ).Scale ( WI_Cos ( ang ) );

	Res = ( h + v ) + uxx;
}

////////////////////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------------------
// calculate an orthonormal matrix with the front vector pointing on the
// dir direction, and the up and right are determined by using the Gram-Schmidt process
WI_Matrix WI_gGrammSchmidt ( const WI_Vector4& dir )
{
	WI_Vector4 up;
	WI_Vector4 right;
	WI_Vector4 front ( dir );

	front = front.Scale ( 1.0f / WI_Sqrt ( front.Dot ( front ) ) );

	if ( WI_Abs ( front.z ) > 0.577f )
	{
		right = front.Cross ( WI_Vector4 ( -front.y, front.z, 0.0f ) );
	}
	else
	{
		right = front.Cross ( WI_Vector4 ( -front.y, front.x, 0.0f ) );
	}

	right = right.Scale ( 1.0f / WI_Sqrt ( right.Dot ( right ) ) );
	up = right.Cross ( front );

	front.w = 0.0f;
	up.w = 0.0f;
	right.w = 0.0f;

	return WI_Matrix ( front, up, right, WI_Vector4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

WI_Matrix WI_PitchMatrix ( WI_Float ang )
{
	WI_Float cosAng;
	WI_Float sinAng;

	sinAng = WI_Sin ( ang );
	cosAng = WI_Cos ( ang );

	return WI_Matrix ( 	WI_Vector4 ( 1.0f,    0.0f,    0.0f, 0.0f ),
						WI_Vector4 ( 0.0f,  cosAng,  sinAng, 0.0f ),
						WI_Vector4 ( 0.0f, -sinAng,  cosAng, 0.0f ),
						WI_Vector4 ( 0.0f,    0.0f,    0.0f, 1.0f ) );
}

WI_Matrix WI_YawMatrix ( WI_Float ang )
{
	WI_Float cosAng;
	WI_Float sinAng;

	sinAng = WI_Sin ( ang );
	cosAng = WI_Cos ( ang );

	return WI_Matrix ( 	WI_Vector4 ( cosAng, 0.0f, -sinAng, 0.0f ),
						WI_Vector4 ( 0.0f,   1.0f,    0.0f, 0.0f ),
						WI_Vector4 ( sinAng, 0.0f,  cosAng, 0.0f ),
						WI_Vector4 ( 0.0f,   0.0f,    0.0f, 1.0f ) );
}

WI_Matrix WI_RollMatrix ( WI_Float ang )
{
	WI_Float cosAng;
	WI_Float sinAng;

	sinAng = WI_Sin ( ang );
	cosAng = WI_Cos ( ang );

	return WI_Matrix ( 	WI_Vector4 ( cosAng, sinAng, 0.0f, 0.0f ),
						WI_Vector4 ( -sinAng, cosAng, 0.0f, 0.0f ),
						WI_Vector4 (  0.0f,   0.0f, 1.0f, 0.0f ),
						WI_Vector4 (  0.0f,   0.0f, 0.0f, 1.0f ) );
}