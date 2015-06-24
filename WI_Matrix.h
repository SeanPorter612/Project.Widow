#pragma once

#ifndef __WI_Matrix__
#define __WI_Matrix__

//class WI_Quaternion;

///////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// small but fully operational 4x4 matrix class

///////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// -------------------------------------------------------------------
// Theory 4x4 matrix class
class WI_Matrix
{
public:
	///////////////////////////////////////////////////////////////////////
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------
	// constructors
	WI_Matrix ( const WI_Vector4 &front	= WI_Vector4 ( 1.0f, 0.0f, 0.0f, 0.0f ),
			    const WI_Vector4 &up		= WI_Vector4 ( 0.0f, 1.0f, 0.0f, 0.0f ),
			    const WI_Vector4 &right	= WI_Vector4 ( 0.0f, 0.0f, 1.0f, 0.0f ),
			    const WI_Vector4 &posit	= WI_Vector4 ( 0.0f, 0.0f, 1.0f, 0.0f ) );

	//WI_Matrix ( WI_Quaternion rotation, const WI_Vector4 &position );

	WI_Matrix ( WI_Float pitch, WI_Float yaw, WI_Float roll, const WI_Vector4& location );

public:
	///////////////////////////////////////////////////////////////////////
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------
	// public methods

	WI_Matrix Inverse ( ) const;
	WI_Matrix Transpose ( ) const;
	WI_Matrix Transpose4X4 ( ) const;
	WI_Vector4 GetXYZ_EulerAngles ( ) const;
	WI_Vector4 RotateVector ( const WI_Vector4 &v ) const;
	WI_Vector4 UnrotateVector ( const WI_Vector4 &v ) const;
	WI_Vector4 TransformVector ( const WI_Vector4 &v ) const;
	WI_Vector4 UntransformVector ( const WI_Vector4 &v ) const;
	WI_Vector4 TransformPlane ( const WI_Vector4 &localPlane ) const;
	WI_Vector4 UntransformPlane ( const WI_Vector4 &globalPlane ) const;

	void TransformTriplex ( void* const dst, int dstStrideInBytes,
						    void* const src, int srcStrideInBytes, int count ) const;

	bool SanityCheck ( ) const;

	void Set ( WI_Vector4 vFront, WI_Vector4 vUp, WI_Vector4 vRight, WI_Vector4 vPos );
public:
	///////////////////////////////////////////////////////////////////////
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------
	// public operators

	WI_Vector4& operator[ ] ( int i );
	const WI_Vector4& operator[ ] ( int i ) const;

	WI_Matrix operator* ( const WI_Matrix &B ) const;

public:
	///////////////////////////////////////////////////////////////////////
	// -------------------------------------------------------------------
	// -------------------------------------------------------------------
	// member vars
	WI_Vector4 m_front;
	WI_Vector4 m_up;
	WI_Vector4 m_right;
	WI_Vector4 m_posit;
};

WI_Inline WI_Matrix WI_SetIdentityMatrix ( );

WI_Inline WI_Matrix WI_SetZeroMatrix ( );

WI_Inline WI_Matrix::WI_Matrix ( const WI_Vector4 &front,
								 const WI_Vector4 &up,
								 const WI_Vector4 &right,
								 const WI_Vector4 &posit )
:m_front ( front ),
m_up ( up ),
m_right ( right ),
m_posit ( posit )
{
}

WI_Inline WI_Vector4& WI_Matrix::operator[ ] ( int  i )
{
	return ( &m_front )[ i ];
}

WI_Inline const WI_Vector4& WI_Matrix::operator[ ] ( int  i ) const
{
	return ( &m_front )[ i ];
}

#pragma message ( "		Widow 4x4 matrix class..." )
#endif
