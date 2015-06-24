#include "LyteGlobals.h"

WI_Matrix::WI_Matrix ( WI_Float pitch, WI_Float yaw, WI_Float roll, const WI_Vector4& location )
{
	WI_Matrix& me = *this;

	me = WI_PitchMatrix ( pitch ) *
		 WI_YawMatrix ( yaw ) *
		 WI_RollMatrix ( roll );

	me.m_posit = location;
	me.m_posit.w = 1.0f;
}

WI_Vector4 WI_Matrix::GetXYZ_EulerAngles ( ) const
{
	WI_Float yaw;
	WI_Float roll;
	WI_Float pitch;
	const WI_Float minSin = 0.99995f;

	const WI_Matrix& matrix = *this;

	roll = WI_Float ( 0.0f );
	pitch  = WI_Float ( 0.0f );

	yaw = WI_Asin ( - min ( max ( matrix[ 0 ][ 2 ], WI_Float ( -0.999999f ) ), WI_Float ( 0.999999f ) ) );
	if ( matrix[ 0 ][ 2 ] < minSin ) {
		if ( matrix[ 0 ][ 2 ] > ( -minSin ) ) {
			roll = WI_Atan2 ( matrix[ 0 ][ 1 ], matrix[ 0 ][ 0 ] );
			pitch = WI_Atan2 ( matrix[ 1 ][ 2 ], matrix[ 2 ][ 2 ] );
		} else {
			pitch = WI_Atan2 ( matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ] );
		}
	} else {
		pitch = -WI_Atan2 ( matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ] );
	}

	return WI_Vector4 ( pitch, yaw, roll, WI_Float ( 0.0f ) );
}

WI_Matrix WI_Matrix::Inverse ( ) const
{
	return WI_Matrix ( 	WI_Vector4 ( m_front.x, m_up.x, m_right.x, 0.0f ),
						WI_Vector4 ( m_front.y, m_up.y, m_right.y, 0.0f ),
						WI_Vector4 ( m_front.z, m_up.z, m_right.z, 0.0f ),
						WI_Vector4 ( - ( m_posit.Dot ( m_front ) ), - ( m_posit.Dot ( m_up ) ), - ( m_posit.Dot ( m_right ) ), 1.0f ) );
}

WI_Matrix WI_Matrix::Transpose ( ) const
{
	return WI_Matrix ( 	WI_Vector4 ( m_front.x, m_up.x, m_right.x, 0.0f ),
						WI_Vector4 ( m_front.y, m_up.y, m_right.y, 0.0f ),
						WI_Vector4 ( m_front.z, m_up.z, m_right.z, 0.0f ),
						WI_Vector4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

WI_Matrix WI_Matrix::Transpose4X4 ( ) const
{
	return WI_Matrix ( 	WI_Vector4 ( m_front.x, m_up.x, m_right.x, m_posit.x ),
						WI_Vector4 ( m_front.y, m_up.y, m_right.y, m_posit.y ),
						WI_Vector4 ( m_front.z, m_up.z, m_right.z, m_posit.z ),
						WI_Vector4 ( m_front.w, m_up.w, m_right.w, m_posit.w ) );
}

WI_Vector4 WI_Matrix::RotateVector ( const WI_Vector4 &v ) const
{
	return WI_Vector4 ( v.x * m_front.x + v.y * m_up.x + v.z * m_right.x,
					 v.x * m_front.y + v.y * m_up.y + v.z * m_right.y,
					 v.x * m_front.z + v.y * m_up.z + v.z * m_right.z );
}

WI_Vector4 WI_Matrix::UnrotateVector ( const WI_Vector4 &v ) const
{
	return WI_Vector4 ( v.Dot ( m_front ), v.Dot ( m_up ), v.Dot ( m_right ) );
}

WI_Vector4 WI_Matrix::TransformVector ( const WI_Vector4 &v ) const
{
	return m_posit + RotateVector ( v );
}

WI_Vector4 WI_Matrix::UntransformVector ( const WI_Vector4 &v ) const
{
	return UnrotateVector ( v - m_posit );
}

void WI_Matrix::TransformTriplex (
	void* const dstPtr, int dstStrideInBytes, void* const srcPtr, int srcStrideInBytes, int count ) const
{
	int i;
	WI_Float x;
	WI_Float y;
	WI_Float z;
	WI_Float* dst;
	WI_Float* src;

	dst = ( WI_Float* ) dstPtr;
	src = ( WI_Float* ) srcPtr;

	dstStrideInBytes /= sizeof ( WI_Float );
	srcStrideInBytes /= sizeof ( WI_Float );

	for ( i = 0 ; i < count; i ++ ) {
		x = src[ 0 ];
		y = src[ 1 ];
		z = src[ 2 ];
		dst[ 0 ] = x * m_front.x + y * m_up.x + z * m_right.x + m_posit.x;
		dst[ 1 ] = x * m_front.y + y * m_up.y + z * m_right.y + m_posit.y;
		dst[ 2 ] = x * m_front.z + y * m_up.z + z * m_right.z + m_posit.z;
		dst += dstStrideInBytes;
		src += srcStrideInBytes;
	}
}

WI_Matrix WI_Matrix::operator* ( const WI_Matrix &B ) const
{
	const WI_Matrix& A = *this;
	return WI_Matrix ( 	WI_Vector4 ( 	 A[ 0 ][ 0 ] * B[ 0 ][ 0 ] + A[ 0 ][ 1 ] * B[ 1 ][ 0 ] + A[ 0 ][ 2 ] * B[ 2 ][ 0 ] + A[ 0 ][ 3 ] * B[ 3 ][ 0 ],
									 A[ 0 ][ 0 ] * B[ 0 ][ 1 ] + A[ 0 ][ 1 ] * B[ 1 ][ 1 ] + A[ 0 ][ 2 ] * B[ 2 ][ 1 ] + A[ 0 ][ 3 ] * B[ 3 ][ 1 ],
									 A[ 0 ][ 0 ] * B[ 0 ][ 2 ] + A[ 0 ][ 1 ] * B[ 1 ][ 2 ] + A[ 0 ][ 2 ] * B[ 2 ][ 2 ] + A[ 0 ][ 3 ] * B[ 3 ][ 2 ],
									 A[ 0 ][ 0 ] * B[ 0 ][ 3 ] + A[ 0 ][ 1 ] * B[ 1 ][ 3 ] + A[ 0 ][ 2 ] * B[ 2 ][ 3 ] + A[ 0 ][ 3 ] * B[ 3 ][ 3 ] ),
							WI_Vector4 ( A[ 1 ][ 0 ] * B[ 0 ][ 0 ] + A[ 1 ][ 1 ] * B[ 1 ][ 0 ] + A[ 1 ][ 2 ] * B[ 2 ][ 0 ] + A[ 1 ][ 3 ] * B[ 3 ][ 0 ],
									 A[ 1 ][ 0 ] * B[ 0 ][ 1 ] + A[ 1 ][ 1 ] * B[ 1 ][ 1 ] + A[ 1 ][ 2 ] * B[ 2 ][ 1 ] + A[ 1 ][ 3 ] * B[ 3 ][ 1 ],
									 A[ 1 ][ 0 ] * B[ 0 ][ 2 ] + A[ 1 ][ 1 ] * B[ 1 ][ 2 ] + A[ 1 ][ 2 ] * B[ 2 ][ 2 ] + A[ 1 ][ 3 ] * B[ 3 ][ 2 ],
									 A[ 1 ][ 0 ] * B[ 0 ][ 3 ] + A[ 1 ][ 1 ] * B[ 1 ][ 3 ] + A[ 1 ][ 2 ] * B[ 2 ][ 3 ] + A[ 1 ][ 3 ] * B[ 3 ][ 3 ] ),
							WI_Vector4 ( A[ 2 ][ 0 ] * B[ 0 ][ 0 ] + A[ 2 ][ 1 ] * B[ 1 ][ 0 ] + A[ 2 ][ 2 ] * B[ 2 ][ 0 ] + A[ 2 ][ 3 ] * B[ 3 ][ 0 ],
									 A[ 2 ][ 0 ] * B[ 0 ][ 1 ] + A[ 2 ][ 1 ] * B[ 1 ][ 1 ] + A[ 2 ][ 2 ] * B[ 2 ][ 1 ] + A[ 2 ][ 3 ] * B[ 3 ][ 1 ],
									 A[ 2 ][ 0 ] * B[ 0 ][ 2 ] + A[ 2 ][ 1 ] * B[ 1 ][ 2 ] + A[ 2 ][ 2 ] * B[ 2 ][ 2 ] + A[ 2 ][ 3 ] * B[ 3 ][ 2 ],
									 A[ 2 ][ 0 ] * B[ 0 ][ 3 ] + A[ 2 ][ 1 ] * B[ 1 ][ 3 ] + A[ 2 ][ 2 ] * B[ 2 ][ 3 ] + A[ 2 ][ 3 ] * B[ 3 ][ 3 ] ),
							WI_Vector4 ( A[ 3 ][ 0 ] * B[ 0 ][ 0 ] + A[ 3 ][ 1 ] * B[ 1 ][ 0 ] + A[ 3 ][ 2 ] * B[ 2 ][ 0 ] + A[ 3 ][ 3 ] * B[ 3 ][ 0 ],
									 A[ 3 ][ 0 ] * B[ 0 ][ 1 ] + A[ 3 ][ 1 ] * B[ 1 ][ 1 ] + A[ 3 ][ 2 ] * B[ 2 ][ 1 ] + A[ 3 ][ 3 ] * B[ 3 ][ 1 ],
									 A[ 3 ][ 0 ] * B[ 0 ][ 2 ] + A[ 3 ][ 1 ] * B[ 1 ][ 2 ] + A[ 3 ][ 2 ] * B[ 2 ][ 2 ] + A[ 3 ][ 3 ] * B[ 3 ][ 2 ],
									 A[ 3 ][ 0 ] * B[ 0 ][ 3 ] + A[ 3 ][ 1 ] * B[ 1 ][ 3 ] + A[ 3 ][ 2 ] * B[ 2 ][ 3 ] + A[ 3 ][ 3 ] * B[ 3 ][ 3 ] ) );
}

WI_Vector4 WI_Matrix::TransformPlane ( const WI_Vector4 &localPlane ) const
{
	WI_Vector4 tmp ( RotateVector ( localPlane ) );
	tmp.w = localPlane.w - ( localPlane.Dot ( UnrotateVector ( m_posit ) ) );
	return tmp;
}

WI_Vector4 WI_Matrix::UntransformPlane ( const WI_Vector4 &globalPlane ) const
{
	WI_Vector4 tmp ( RotateVector ( globalPlane ) );
	tmp.w = globalPlane.Dot ( m_posit.Scale ( globalPlane.w ) );

	return tmp;
}

bool WI_Matrix::SanityCheck ( ) const
{
	WI_Vector4 right ( m_front.Cross ( m_up ) );

	if ( WI_Abs ( right.Dot ( m_right ) ) < 0.9999f )
		{return false;}

	if ( WI_Abs ( m_right.w ) > 0.0f )
		{ return false; }

	if ( WI_Abs ( m_up.w ) > 0.0f )
		{ return false; }

	if ( WI_Abs ( m_right.w ) > 0.0f )
		{ return false; }

	if ( WI_Abs ( m_posit.w ) != 1.0f )
		{ return false; }

	return true;
}

void WI_Matrix::Set ( WI_Vector4 vFront, WI_Vector4 vUp, WI_Vector4 vRight, WI_Vector4 vPos )
{
	m_front = vFront;
	m_up = vUp;
	m_right = vRight;
	m_posit = vPos;
}

WI_Inline WI_Matrix WI_SetIdentityMatrix ( )
{
	return WI_Matrix ( 	WI_Vector4 ( 1.0f, 0.0f, 0.0f, 0.0f ),
						WI_Vector4 ( 0.0f, 1.0f, 0.0f, 0.0f ),
						WI_Vector4 ( 0.0f, 0.0f, 1.0f, 0.0f ),
						WI_Vector4 ( 0.0f, 0.0f, 0.0f, 1.0f ) );
}

WI_Inline WI_Matrix WI_SetZeroMatrix ( )
{
	return WI_Matrix ( 	WI_Vector4 ( 0.0f, 0.0f, 0.0f, 0.0f ),
						WI_Vector4 ( 0.0f, 0.0f, 0.0f, 0.0f ),
						WI_Vector4 ( 0.0f, 0.0f, 0.0f, 0.0f ),
						WI_Vector4 ( 0.0f, 0.0f, 0.0f, 0.0f ) );
}