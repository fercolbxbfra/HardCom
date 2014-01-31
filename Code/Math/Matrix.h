//----------------------------------------------------------------------------
// Matrix
//----------------------------------------------------------------------------


#pragma once

#include "Vector.h"
#include "Angle.h"


struct TQuat
{
	float x, y, z, w;
};


struct TMatrix4
{
	union
	{
		struct
		{
			float   v11, v12, v13, v14;
			float   v21, v22, v23, v24;
			float   v31, v32, v33, v34;
			float   v41, v42, v43, v44;
		};
		float   m[4][4];
	};


															TMatrix4                    () {}
															TMatrix4                    ( float _11, float _12, float _13, float _14,
																															float _21, float _22, float _23, float _24,
																															float _31, float _32, float _33, float _34,
																															float _41, float _42, float _43, float _44 );

			void                    SetIdentity                 ();
			void                    SetTranslation              ( const V3& _vPos );
			void                    SetRotationX                ( float _fAngle );
			void                    SetRotationY                ( float _fAngle );
			void                    SetRotationZ                ( float _fAngle );
			void                    SetRotationDegX             ( float _fAngle );
			void                    SetRotationDegY             ( float _fAngle );
			void                    SetRotationDegZ             ( float _fAngle );
			void                    SetProjection               ( float _fFovY, float _fAspect, float _zn, float _zf );
			void                    SetScale                    ( float _fScale );
			void                    ApplyScale                  ( float _fScale );
			void                    Multiply_vector             ( V3* _pRes, const V3& _vec ) const;
			void                    Multiply_point              ( V3* _pRes, const V3& _vec ) const;
			void                    Multiply                    ( const TMatrix4& mA, const TMatrix4& mB );
			void                    SetRotationAxis             ( const V3& _vEje, float _fAngle );
			void                    InvertTo                    ( TMatrix4* _pMat ) const;
			void                    InvertTo                    ( TMatrix4* _pMat, float _fScale ) const;
			void                    CalcPosAndAngles            ( const V3& _vPos, const V3& _vAngles );
			void                    CalcQuat                    ( TQuat* _pQuat ) const;
			void                    CalcFromQuat                ( const TQuat& _Quat );
			void                    CalcBlend                   ( const TMatrix4& _Mat0, const TMatrix4& _Mat1, float _fFactor );
			void                    CalcBlend                   ( const TMatrix4& _MatA0, const TMatrix4& _MatA1, float _fFactorA, 
																														const TMatrix4& _MatB0, const TMatrix4& _MatB1, float _fFactorB, 
																														float _fFactor );
			void                    CalcBlend                   ( const TMatrix4& _MatA0, const TMatrix4& _MatA1, float _fFactorA, 
																														const TMatrix4& _MatB, 
																														float _fFactor );
			void                    ModTranslation              ( const V3& _vPos );
			V3                      GetTranslation              () const { return V3( v41, v42, v43 ); }
			void                    CalcView                    ( const V3& _Right, const V3& _Up, const V3& _Look, const V3& _vPosCam );
			void                    CalcView                    ( const V3& _LookAt, const V3& _vPosCam );
			void                    CalcCamVectors              ( V3* _pRight, V3* _pUp, V3* _pLook, V3* _pPos ) const;
				
			void                    SetRow0                     ( const V3& _v ) { v11 = _v.x; v12 = _v.y; v13 = _v.z; }
			void                    SetRow1                     ( const V3& _v ) { v21 = _v.x; v22 = _v.y; v23 = _v.z; }
			void                    SetRow2                     ( const V3& _v ) { v31 = _v.x; v32 = _v.y; v31 = _v.z; }
			void                    SetRow3                     ( const V3& _v ) { v31 = _v.x; v32 = _v.y; v31 = _v.z; }
			void                    SetCol0                     ( const V3& _v ) { v11 = _v.x; v21 = _v.y; v31 = _v.z; }
			void                    SetCol1                     ( const V3& _v ) { v12 = _v.x; v22 = _v.y; v32 = _v.z; }
			void                    SetCol2                     ( const V3& _v ) { v13 = _v.x; v23 = _v.y; v33 = _v.z; }
			void                    SetTypicalCol3              () { v14 = v24 = v34 = 0; v44 = 1; }
};

/*
struct TMatrix44
{
		union
		{
				struct
				{
						float   v11, v12, v13, v14;
						float   v21, v22, v23, v24;
						float   v31, v32, v33, v34;
						float   v41, v42, v43, v44;
				};
				float   m[4][4];
		};


																TMatrix44                   () {}
																TMatrix44                   ( float _11, float _12, float _13, float _14,
																																float _21, float _22, float _23, float _24,
																																float _31, float _32, float _33, float _34,
																																float _41, float _42, float _43, float _44 );

				void                    SetIdentidad                ();
				void                    SetProjection               ( float _fFovY, float _fAspect, float _zn, float _zf );
				void                    Multiply_vector             ( V3* _pRes, const V3& _vec ) const;
				void                    Multiply_point              ( V3* _pRes, const V3& _vec ) const;
				void                    Multiply                    ( const TMatrix4& mA, const TMatrix44& mB );
};

*/

//--------------------------------------------------------------------------------

struct TMatrix3
{
	union
	{
		struct
		{
			float   v11, v12, v13;
			float   v21, v22, v23;
			float   v31, v32, v33;
		};
		float   m[3][3];
	};


															TMatrix3                    () {}
															TMatrix3                    ( float f11, float f12, float f13,
																															float f21, float f22, float f23,
																															float f31, float f32, float f33 );
				
			void                    SetIdentity                 ();
			void                    SetRotationX                ( float fAngle );
			void                    SetRotationY                ( float fAngle );
			void                    SetRotationZ                ( float fAngle );
			void                    SetRotationAxis             ( const V3& _vEje, float fAngle );
			void                    Multiply                    ( V3* pRes, const V3& vec );
				
			void                    SetRow0                     ( const V3& _v ) { v11 = _v.x; v12 = _v.y; v13 = _v.z; }
			void                    SetRow1                     ( const V3& _v ) { v21 = _v.x; v22 = _v.y; v23 = _v.z; }
			void                    SetRow2                     ( const V3& _v ) { v31 = _v.x; v32 = _v.y; v31 = _v.z; }
			void                    SetCol0                     ( const V3& _v ) { v11 = _v.x; v21 = _v.y; v31 = _v.z; }
			void                    SetCol1                     ( const V3& _v ) { v12 = _v.x; v22 = _v.y; v32 = _v.z; }
			void                    SetCol2                     ( const V3& _v ) { v13 = _v.x; v23 = _v.y; v33 = _v.z; }
};

extern const TMatrix4       cMatrix4_Unit;
extern const TMatrix3       cMatrix3_Unit;


//############################################################################3
// TMatrix4
//############################################################################3

//////////////////////////////////////////////////////////////////////////

inline TMatrix4::TMatrix4( float _11, float _12, float _13, float _14,
														float _21, float _22, float _23, float _24,
														float _31, float _32, float _33, float _34,
														float _41, float _42, float _43, float _44 )
{
	v11 = _11; v12 = _12; v13 = _13; v14 = _14;
	v21 = _21; v22 = _22; v23 = _23; v24 = _24;
	v31 = _31; v32 = _32; v33 = _33; v34 = _34;
	v41 = _41; v42 = _42; v43 = _43; v44 = _44;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::SetIdentity()
{
	v11 = v22 = v33 = v44 = 1;
	v12 = v13 = v14 = v21 = v23 = v24 = v31 = v32 = v34 = v41 = v42 = v43 = 0;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::SetTranslation( const V3& _vPos )
{
	SetIdentity();
	v41 = _vPos.x;
	v42 = _vPos.y;
	v43 = _vPos.z;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::ModTranslation( const V3& _vPos )
{
	v41 = _vPos.x;
	v42 = _vPos.y;
	v43 = _vPos.z;
}


//////////////////////////////////////////////////////////////////////////
		
inline void TMatrix4::SetRotationX( float _fAngle )
{
	SetIdentity();
	float fSin = sinf( _fAngle );
	float fCos = cosf( _fAngle );
		
	v22 = fCos;
	v23 = fSin;
	v32 = -fSin;
	v33 = fCos;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::SetRotationY( float _fAngle )
{
	SetIdentity();
	float fSin = sinf( _fAngle );
	float fCos = cosf( _fAngle );
		
	v11 = fCos;
	v13 = -fSin;
	v31 = fSin;
	v33 = fCos;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::SetRotationZ( float _fAngle )
{
	SetIdentity();
	float fSin = sinf( _fAngle );
	float fCos = cosf( _fAngle );
		
	v11 = fCos;
	v12 = fSin;
	v21 = -fSin;
	v22 = fCos;
}


//////////////////////////////////////////////////////////////////////////
		
inline void TMatrix4::SetRotationDegX( float _fAngle )
{
	float fAngle = Deg2Rad( _fAngle );
	SetIdentity();
	float fSin = sinf( fAngle );
	float fCos = cosf( fAngle );
		
	v22 = fCos;
	v23 = fSin;
	v32 = -fSin;
	v33 = fCos;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::SetRotationDegY( float _fAngle )
{
	float fAngle = Deg2Rad( _fAngle );
	SetIdentity();
	float fSin = sinf( fAngle );
	float fCos = cosf( fAngle );
		
	v11 = fCos;
	v13 = -fSin;
	v31 = fSin;
	v33 = fCos;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::SetRotationDegZ( float _fAngle )
{
	float fAngle = Deg2Rad( _fAngle );
	SetIdentity();
	float fSin = sinf( fAngle );
	float fCos = cosf( fAngle );
		
	v11 = fCos;
	v12 = fSin;
	v21 = -fSin;
	v22 = fCos;
}
		
		
//////////////////////////////////////////////////////////////////////////
		
inline void TMatrix4::SetProjection( float _fFovY, float _fAspect, float _zn, float _zf )
{
	float fCot = cosf( _fFovY/2 ) / sinf( _fFovY / 2 );
	float fYScale = fCot;
	float fXScale = _fAspect * fYScale;
		
	v11 = fXScale;
	v22 = fYScale;
	v33 = _zf / ( _zf - _zn );
	v43 = -_zn*_zf / ( _zf-_zn );
	v34 = 1;
	v12 = v13 = v14 = v21 = v23 = v24 = v31 = v32 = v41 = v42 = v44 = 0;
	v44 = 1;
}



//////////////////////////////////////////////////////////////////////////
// builds a matrix that includes an scale transformation
		
inline void TMatrix4::SetScale( float _fScale )
{
	v11 = v22 = v33 = _fScale;
	v12 = v13 = v14 = v21 = v23 = v24 = v31 = v32 = v34 = v41 = v42 = v43 = 0;
	v44 = 1;
}


//////////////////////////////////////////////////////////////////////////
// is like making an scale matrix and multiply it by current one. (first the scale is applied, then current one is applied)
// WARNING, is not the same than appliying it in the other order
		
inline void TMatrix4::ApplyScale( float _fScale )
{
	v11 *= _fScale;
	v12 *= _fScale;
	v13 *= _fScale;
	v14 *= _fScale;
	v21 *= _fScale;
	v22 *= _fScale;
	v23 *= _fScale;
	v24 *= _fScale;
	v31 *= _fScale;
	v32 *= _fScale;
	v33 *= _fScale;
	v34 *= _fScale;
}



//////////////////////////////////////////////////////////////////////////
// assumes that it is a vector, so it only applies rotations
		
inline void TMatrix4::Multiply_vector( V3* _pRes, const V3& _vec ) const
{
	float x = _vec.x*v11 + _vec.y*v21 + _vec.z*v31;
	float y = _vec.x*v12 + _vec.y*v22 + _vec.z*v32;
	float z = _vec.x*v13 + _vec.y*v23 + _vec.z*v33;
		
	_pRes->x = x;
	_pRes->y = y;
	_pRes->z = z;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix4::Multiply_point( V3* _pRes, const V3& _vec ) const
{
	float x = _vec.x*v11 + _vec.y*v21 + _vec.z*v31 + v41;
	float y = _vec.x*v12 + _vec.y*v22 + _vec.z*v32 + v42;
	float z = _vec.x*v13 + _vec.y*v23 + _vec.z*v33 + v43;
		
	_pRes->x = x;
	_pRes->y = y;
	_pRes->z = z;
}


//////////////////////////////////////////////////////////////////////////
// WARNING!! MA and MB, cant NOT be "this"
//----------------------------------------------------------------------

inline void TMatrix4::Multiply( const TMatrix4& mA, const TMatrix4& mB )
{
	v11 = mA.v11*mB.v11 + mA.v12*mB.v21 + mA.v13*mB.v31 + mA.v14*mB.v41;
	v12 = mA.v11*mB.v12 + mA.v12*mB.v22 + mA.v13*mB.v32 + mA.v14*mB.v42;
	v13 = mA.v11*mB.v13 + mA.v12*mB.v23 + mA.v13*mB.v33 + mA.v14*mB.v43;
	v14 = mA.v11*mB.v14 + mA.v12*mB.v24 + mA.v13*mB.v34 + mA.v14*mB.v44;

	v21 = mA.v21*mB.v11 + mA.v22*mB.v21 + mA.v23*mB.v31 + mA.v24*mB.v41;
	v22 = mA.v21*mB.v12 + mA.v22*mB.v22 + mA.v23*mB.v32 + mA.v24*mB.v42;
	v23 = mA.v21*mB.v13 + mA.v22*mB.v23 + mA.v23*mB.v33 + mA.v24*mB.v43;
	v24 = mA.v21*mB.v14 + mA.v22*mB.v24 + mA.v23*mB.v34 + mA.v24*mB.v44;

	v31 = mA.v31*mB.v11 + mA.v32*mB.v21 + mA.v33*mB.v31 + mA.v34*mB.v41;
	v32 = mA.v31*mB.v12 + mA.v32*mB.v22 + mA.v33*mB.v32 + mA.v34*mB.v42;
	v33 = mA.v31*mB.v13 + mA.v32*mB.v23 + mA.v33*mB.v33 + mA.v34*mB.v43;
	v34 = mA.v31*mB.v14 + mA.v32*mB.v24 + mA.v33*mB.v34 + mA.v34*mB.v44;
		
	v41 = mA.v41*mB.v11 + mA.v42*mB.v21 + mA.v43*mB.v31 + mA.v44*mB.v41;
	v42 = mA.v41*mB.v12 + mA.v42*mB.v22 + mA.v43*mB.v32 + mA.v44*mB.v42;
	v43 = mA.v41*mB.v13 + mA.v42*mB.v23 + mA.v43*mB.v33 + mA.v44*mB.v43;
	v44 = mA.v41*mB.v14 + mA.v42*mB.v24 + mA.v43*mB.v34 + mA.v44*mB.v44;
		
//    ASSERT( fabsf(v41)<VAL_DELTA );
//    ASSERT( fabsf(v42)<VAL_DELTA );
//    ASSERT( fabsf(v43)<VAL_DELTA );
//    ASSERT( fabsf(1-v43)<VAL_DELTA );
}

//////////////////////////////////////////////////////////////////////////
		
inline void TMatrix4::SetRotationAxis( const V3& _vAxis, float _fAngle )
{
		V3 vAxis = _vAxis;
		vAxis.Normalize();
		
		float s = sinf( _fAngle );
		float c = cosf( _fAngle );
		float x = vAxis.x;
		float y = vAxis.y;
		float z = vAxis.z;
		
		v11 = x*x*(1-c)+c;
		v21 = x*y*(1-c)-(z*s);
		v31 = x*z*(1-c)+(y*s);
		v12 = y*x*(1-c)+(z*s);
		v22 = y*y*(1-c)+c;
		v32 = y*z*(1-c)-(x*s);
		v13 = z*x*(1-c)-(y*s);
		v23 = z*y*(1-c)+(x*s);
		v33 = z*z*(1-c)+c;
		v14 = v24 = v34 = v41 = v42 = v43 = 0;
		v44 = 1;
}        



	 
//////////////////////////////////////////////////////////////////////////
/// Inverts a matrix that is made of rotation and translations only. does NOT work if is an scale matrix
/// This algorithm comes from "Advanced 3d Game programming" but i have no explanation of it p.

inline void TMatrix4::InvertTo( TMatrix4* _pMat ) const 
{
	ASSERT( _pMat!= this );
	_pMat->v11 = v11;
	_pMat->v12 = v21;
	_pMat->v13 = v31;
	_pMat->v21 = v12;
	_pMat->v22 = v22;
	_pMat->v23 = v32;
	_pMat->v31 = v13;
	_pMat->v32 = v23;
	_pMat->v33 = v33;
		
	_pMat->v14 = 0;
	_pMat->v24 = 0;
	_pMat->v34 = 0;
	_pMat->v44 = 1;
		
	_pMat->v41 = -( v41*v11 + v42*v12 + v43*v13 );
	_pMat->v42 = -( v41*v21 + v42*v22 + v43*v23 );
	_pMat->v43 = -( v41*v31 + v42*v32 + v43*v33 );
}


//////////////////////////////////////////////////////////////////////////
/// Calculate the inverse of a matrix made of scale, rotations and  translations.
/// WARNING, it assumes the scale was made before all other transformations
/// WARNING2, "this" is NOT the real matrix, is the matrix without the scale
/// what this function does basically is just do the inverse of the no-scale matrix, and postmultiply

inline void TMatrix4::InvertTo( TMatrix4* _pMat, float _fScale ) const 
{
	ASSERT( _pMat != this );
		
	float fInvScale = 1 / _fScale;
		
	_pMat->v11 = v11 * fInvScale;
	_pMat->v12 = v21 * fInvScale;
	_pMat->v13 = v31 * fInvScale;
	_pMat->v21 = v12 * fInvScale;
	_pMat->v22 = v22 * fInvScale;
	_pMat->v23 = v32 * fInvScale;
	_pMat->v31 = v13 * fInvScale;
	_pMat->v32 = v23 * fInvScale;
	_pMat->v33 = v33 * fInvScale;
		
	_pMat->v14 = 0;
	_pMat->v24 = 0;
	_pMat->v34 = 0;
	_pMat->v44 = 1;
		
	_pMat->v41 = -( v41*v11 + v42*v12 + v43*v13 ) * fInvScale;
	_pMat->v42 = -( v41*v21 + v42*v22 + v43*v23 ) * fInvScale;
	_pMat->v43 = -( v41*v31 + v42*v32 + v43*v33 ) * fInvScale;
}


//////////////////////////////////////////////////////////////////////////
/// calculates the matrix that could be used as a view matrix for a camara with those parameters
/// the inside calcs are in fact basically just to do the inverse of the straight matrix formed with those vectors

inline void TMatrix4::CalcView( const V3& _vRight, const V3& _vUp, const V3& _vLook, const V3& _vPos )
{
	v11 = _vRight.x;
	v12 = _vUp.x;
	v13 = _vLook.x;
	v14 = 0;
		
	v21 = _vRight.y;
	v22 = _vUp.y;
	v23 = _vLook.y;
	v24 = 0;
		
	v31 = _vRight.z;
	v32 = _vUp.z;
	v33 = _vLook.z;
	v34 = 0;
		
	v41 = - Dot( _vRight, _vPos );
	v42 = - Dot( _vUp, _vPos );
	v43 = - Dot( _vLook, _vPos );
	v44 = 1;
}



//////////////////////////////////////////////////////////////////////////
/// Calculates a camera matrix from lookat point and a camera pos
/// WARNING, the camera will have the right vector parallel to the x-y plane

inline void TMatrix4::CalcView( const V3& _vPosTarget, const V3& _vPosCam )
{
	//..calculate look
	V3 vLook = _vPosTarget - _vPosCam;
	vLook.Normalize();
		
	//...calculate right (rotate 90 degrees clockwise and always paralel to the xy plane)
	V3 vRight = vLook;
	vRight.z = 0;
	vRight.Normalize();
	vRight.Rotate90ClockZAxis();

	//..calculate up
	V3 vUp = Cross(vLook, vRight);
		
	CalcView( vRight, vUp, vLook, _vPosCam );
}


//////////////////////////////////////////////////////////////////////////
/// assuming the mat is a camera view matrix, this calcs the 3 vectors and the position of the camera

inline void TMatrix4::CalcCamVectors( V3* _pRight, V3* _pUp, V3* _pLook, V3* _pPos ) const
{
	_pRight->x  = v11;
	_pUp->x     = v12;
	_pLook->x   = v13;
		
	_pRight->y  = v21;
	_pUp->y     = v22;
	_pLook->y   = v23;
		
	_pRight->z  = v31;
	_pUp->z     = v32;
	_pLook->z   = v33;

	_pPos->x = -( v41*v11 + v42*v12 + v43*v13 );
	_pPos->y = -( v41*v21 + v42*v22 + v43*v23 );
	_pPos->z = -( v41*v31 + v42*v32 + v43*v33 );
}




	 
//############################################################################3
// TMatrix3
//############################################################################3


//////////////////////////////////////////////////////////////////////////

inline TMatrix3::TMatrix3( float f11, float f12, float f13,
						float f21, float f22, float f23,
						float f31, float f32, float f33 )
{
	v11 = f11; v12 = f12; v13 = f13;
	v21 = f21; v22 = f22; v23 = f23;
	v31 = f31; v32 = f32; v33 = f33;
}

//////////////////////////////////////////////////////////////////////////

inline void TMatrix3::SetIdentity()
{
	v11 = v22 = v33 = 1;
	v12 = v13 = v21 = v23 = v31 = v32 = 0;
}

//////////////////////////////////////////////////////////////////////////

inline void TMatrix3::SetRotationX( float fAngle )
{
	SetIdentity();
	float fSin = sinf( fAngle );
	float fCos = cosf( fAngle );
		
	v22 = fCos;
	v23 = fSin;
	v32 = -fSin;
	v33 = fCos;
}

//////////////////////////////////////////////////////////////////////////

inline void TMatrix3::SetRotationY( float fAngle )
{
	SetIdentity();
	float fSin = sinf( fAngle );
	float fCos = cosf( fAngle );
		
	v11 = fCos;
	v13 = -fSin;
	v31 = fSin;
	v33 = fCos;
}


//////////////////////////////////////////////////////////////////////////

inline void TMatrix3::SetRotationZ( float fAngle )
{
	SetIdentity();
	float fSin = sinf( fAngle );
	float fCos = cosf( fAngle );
		
	v11 = fCos;
	v12 = fSin;
	v21 = -fSin;
	v22 = fCos;
}

//////////////////////////////////////////////////////////////////////////

inline void TMatrix3::SetRotationAxis( const V3& _vEje, float fAngle )
{
	V3 vEje = _vEje;
	vEje.Normalize();
		
	float s = sinf( fAngle );
	float c = cosf( fAngle );
	float x = vEje.x;
	float y = vEje.y;
	float z = vEje.z;
		
	v11 = x*x*(1-c)+c;
	v21 = x*y*(1-c)-(z*s);
	v31 = x*z*(1-c)+(y*s);
	v12 = y*x*(1-c)+(z*s);
	v22 = y*y*(1-c)+c;
	v32 = y*z*(1-c)-(x*s);
	v13 = z*x*(1-c)-(y*s);
	v23 = z*y*(1-c)+(x*s);
	v33 = z*z*(1-c)+c;
}        
		
		
//////////////////////////////////////////////////////////////////////////
		
inline void TMatrix3::Multiply( V3* pRes, const V3& vec )
{
	float x = vec.x*v11 + vec.y*v21 + vec.z*v31;
	float y = vec.x*v12 + vec.y*v22 + vec.z*v32;
	float z = vec.x*v13 + vec.y*v23 + vec.z*v33;
		
	pRes->x = x;
	pRes->y = y;
	pRes->z = z;
}






