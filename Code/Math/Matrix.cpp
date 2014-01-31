//----------------------------------------------------------------------------
// Matrix
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Matrix.h"
#include <d3dx9math.h>


//...constants...
const TMatrix4      cMatrix4_Unit       = TMatrix4( 1, 0, 0, 0,   0, 1, 0, 0,   0, 0, 1, 0,   0, 0, 0, 1 );
const TMatrix3      cMatrix3_Unit       = TMatrix3( 1, 0, 0,     0, 1, 0,    0, 0, 1 );


//////////////////////////////////////////////////////////////////////////
// sets the matrix with a transformtion that includes a given position and rotation

void TMatrix4::CalcPosAndAngles( const V3& _vPos, const V3& _vAngles )
{
	TMatrix4 matT, matX, matY, matZ, matTemp;
	V3 YAxis;
		
	// x-y-z order is intended so that the angles have a predecible effect
		
	matX.SetRotationX( _vAngles.x );
	matY.SetRotationY( -_vAngles.y );
	matZ.SetRotationZ( _vAngles.z );
		
	//...combine al matrixs...
	matTemp.Multiply( matX, matY );
	Multiply( matTemp, matZ);
	ModTranslation( _vPos );
}


//////////////////////////////////////////////////////////////////////////
// Calcs quaternion dof the matrix

void TMatrix4::CalcQuat( TQuat* _pQ ) const
{
/*    float fFourWSquaredMinus1    = v11 + v22 + v33;
		float fFourXSquaredMinus1    = v11 - v22 - v33;
		float fFourYSquaredMinus1    = v22 - v11 - v33;
		float fFourZSquaredMinus1    = v33 - v11 - v22;
		
		int iBiggestIndex = 0;
		
		float fFourBiggestSquaredMinus1 = fFourWSquaredMinus1;
		if (fFourXSquaredMinus1 > fFourBiggestSquaredMinus1 )
		{
				fFourBiggestSquaredMinus1 = fFourXSquaredMinus1;
				iBiggestIndex = 1;
		}

		if (fFourYSquaredMinus1 > fFourBiggestSquaredMinus1 )
		{
				fFourBiggestSquaredMinus1 = fFourYSquaredMinus1;
				iBiggestIndex = 2;
		}

		if (fFourZSquaredMinus1 > fFourBiggestSquaredMinus1 )
		{
				fFourBiggestSquaredMinus1 = fFourZSquaredMinus1;
				iBiggestIndex = 3;
		}


		float fBiggestVal = sqrtf( fFourBiggestSquaredMinus1 + 1) * 0.5f;
		float fMult = 0.25f / fBiggestVal;
		
		switch (iBiggestIndex)
		{
				case 0:
				{
						_pQ->w = fBiggestVal;
						_pQ->x = (v23-v32) * fMult;
						_pQ->y = (v31-v13) * fMult;
						_pQ->z = (v12-v21) * fMult;
						break;
				}

				case 1:
				{
						_pQ->x = fBiggestVal;
						_pQ->w = (v23-v32) * fMult;
						_pQ->y = (v12-v21) * fMult;
						_pQ->z = (v31-v13) * fMult;
						break;
				}

				case 2:
				{
						_pQ->y = fBiggestVal;
						_pQ->w = (v31-v13) * fMult;
						_pQ->y = (v12-v21) * fMult;
						_pQ->z = (v23-v32) * fMult;
						break;
				}

				case 3:
				{
						_pQ->z = fBiggestVal;
						_pQ->w = (v12-v21) * fMult;
						_pQ->x = (v31-v13) * fMult;
						_pQ->y = (v23-v32) * fMult;
						break;
				}
		}*/
		D3DXQUATERNION Quat;
		D3DXQuaternionRotationMatrix( &Quat, (const D3DXMATRIX*)(this) );
		
/*    float rv41 = v41;
		float rv42 = v42;
		float rv43 = v43;
		float rv44 = v44;
		v41=0;
		v42=0;
		v43=0;
		D3DXQuaternionRotationMatrix( &Quat, (const D3DXMATRIX*)(this) );
*/    
		
		
		_pQ->x = Quat.x;
		_pQ->y = Quat.y;
		_pQ->z = Quat.z;
		_pQ->w = Quat.w;
		
}


//////////////////////////////////////////////////////////////////////////
// Calcs the matrix from a quaternion

void TMatrix4::CalcFromQuat( const TQuat& _Quat )
{
/*    float _2x2 = 2 * _Quat.x * _Quat.x;
		float _2y2 = 2 * _Quat.y * _Quat.y;
		float _2z2 = 2 * _Quat.z * _Quat.z;
		
		float _2xy = 2 * _Quat.x * _Quat.y;
		float _2xz = 2 * _Quat.x * _Quat.z;
		float _2xw = 2 * _Quat.x * _Quat.w;
		float _2yz = 2 * _Quat.y * _Quat.z;
		float _2yw = 2 * _Quat.y * _Quat.w;
		float _2zw = 2 * _Quat.z * _Quat.w;
		
		v11 = 1 - _2y2 - _2z2;
		v21 = _2xy - _2zw;
		v31 = _2xz + _2yw;
		
		v12 = _2xy + _2zw;
		v22 = 1 - _2x2 - _2z2;
		v32 = _2yz - _2xw;
		
		v13 = _2xz - _2yw;
		v23 = _2yz + _2xw;
		v33 = 1 - _2x2 - _2y2;*/
		
//    D3DXMATRIX dxmat;
		float rv41 = v41;
		float rv42 = v42;
		float rv43 = v43;
		float rv44 = v44;
		
		D3DXQUATERNION Quat;
		Quat.x = _Quat.x;
		Quat.y = _Quat.y;
		Quat.z = _Quat.z;
		Quat.w = _Quat.w;
		
		D3DXMatrixRotationQuaternion( (D3DXMATRIX*)this, &Quat );
//    static int a = 0;
//    a++;
		v41 = rv41;
		v42 = rv42;
		v43 = rv43;
		v44 = rv44;
}


//////////////////////////////////////////////////////////////////////////
/// does a blend between 2 matrixs

void TMatrix4::CalcBlend( const TMatrix4& _Mat0, const TMatrix4& _Mat1, float _fFactor )
{
	float fInvFactor = 1 - _fFactor;
		
	TQuat Quat0, Quat1, QuatInterp;
	_Mat0.CalcQuat( &Quat0 );
	_Mat1.CalcQuat( &Quat1 );

	D3DXQUATERNION DXQuat0, DXQuat1, DXQuatInterp;
		
	DXQuat0.x = Quat0.x;
	DXQuat0.y = Quat0.y;
	DXQuat0.z = Quat0.z;
	DXQuat0.w = Quat0.w;

	DXQuat1.x = Quat1.x;
	DXQuat1.y = Quat1.y;
	DXQuat1.z = Quat1.z;
	DXQuat1.w = Quat1.w;
		
	D3DXQuaternionSlerp( &DXQuatInterp, &DXQuat0, &DXQuat1, _fFactor );
		
	QuatInterp.x = DXQuatInterp.x;
	QuatInterp.y = DXQuatInterp.y;
	QuatInterp.z = DXQuatInterp.z;
	QuatInterp.w = DXQuatInterp.w;
		
	CalcFromQuat( QuatInterp );
		
	v41 = _Mat1.v41 * _fFactor + _Mat0.v41 * fInvFactor;
	v42 = _Mat1.v42 * _fFactor + _Mat0.v42 * fInvFactor;
	v43 = _Mat1.v43 * _fFactor + _Mat0.v43 * fInvFactor;
	v44 = _Mat1.v44 * _fFactor + _Mat0.v44 * fInvFactor; 
}


//////////////////////////////////////////////////////////////////////////
/// does a blend between 4 matrixs. first blend mats A0-A1, then B0-B1, then the resul of the 2 blendings

void TMatrix4::CalcBlend( const TMatrix4& _MatA0, const TMatrix4& _MatA1, float _fFactorA, 
													const TMatrix4& _MatB0, const TMatrix4& _MatB1, float _fFactorB, 
													float _fFactor )
{
	float fInvFactorA   = 1 - _fFactorA;
	float fInvFactorB   = 1 - _fFactorB;
	float fInvFactor    = 1 - _fFactor;
		
	TQuat QuatA0, QuatA1, QuatB0, QuatB1, QuatA, QuatB, QuatFinal;
	_MatA0.CalcQuat( &QuatA0 );
	_MatA1.CalcQuat( &QuatA1 );
	_MatB0.CalcQuat( &QuatB0 );
	_MatB1.CalcQuat( &QuatB1 );

	//...A0-A1
	D3DXQUATERNION DXQuat0, DXQuat1, DXQuatInterp;
		
	DXQuat0.x = QuatA0.x;
	DXQuat0.y = QuatA0.y;
	DXQuat0.z = QuatA0.z;
	DXQuat0.w = QuatA0.w;

	DXQuat1.x = QuatA1.x;
	DXQuat1.y = QuatA1.y;
	DXQuat1.z = QuatA1.z;
	DXQuat1.w = QuatA1.w;
		
	D3DXQuaternionSlerp( &DXQuatInterp, &DXQuat0, &DXQuat1, _fFactorA );
		
	QuatA.x = DXQuatInterp.x;
	QuatA.y = DXQuatInterp.y;
	QuatA.z = DXQuatInterp.z;
	QuatA.w = DXQuatInterp.w;
		

	//...B0-B1
	DXQuat0.x = QuatB0.x;
	DXQuat0.y = QuatB0.y;
	DXQuat0.z = QuatB0.z;
	DXQuat0.w = QuatB0.w;

	DXQuat1.x = QuatB1.x;
	DXQuat1.y = QuatB1.y;
	DXQuat1.z = QuatB1.z;
	DXQuat1.w = QuatB1.w;
		
	D3DXQuaternionSlerp( &DXQuatInterp, &DXQuat0, &DXQuat1, _fFactorB );
		
	QuatB.x = DXQuatInterp.x;
	QuatB.y = DXQuatInterp.y;
	QuatB.z = DXQuatInterp.z;
	QuatB.w = DXQuatInterp.w;
		
		
		
	//....A-B
	DXQuat0.x = QuatA.x;
	DXQuat0.y = QuatA.y;
	DXQuat0.z = QuatA.z;
	DXQuat0.w = QuatA.w;

	DXQuat1.x = QuatB.x;
	DXQuat1.y = QuatB.y;
	DXQuat1.z = QuatB.z;
	DXQuat1.w = QuatB.w;
		
	D3DXQuaternionSlerp( &DXQuatInterp, &DXQuat0, &DXQuat1, _fFactor );
		
	QuatFinal.x = DXQuatInterp.x;
	QuatFinal.y = DXQuatInterp.y;
	QuatFinal.z = DXQuatInterp.z;
	QuatFinal.w = DXQuatInterp.w;
		
	//...final interpolated quaternion
	CalcFromQuat( QuatFinal );
		
	//..now interpolates the translations
	float v41A = _MatA1.v41 * _fFactorA + _MatA0.v41 * fInvFactorA;
	float v42A = _MatA1.v42 * _fFactorA + _MatA0.v42 * fInvFactorA;
	float v43A = _MatA1.v43 * _fFactorA + _MatA0.v43 * fInvFactorA;
	float v44A = _MatA1.v44 * _fFactorA + _MatA0.v44 * fInvFactorA; 

	float v41B = _MatB1.v41 * _fFactorB + _MatB0.v41 * fInvFactorB;
	float v42B = _MatB1.v42 * _fFactorB + _MatB0.v42 * fInvFactorB;
	float v43B = _MatB1.v43 * _fFactorB + _MatB0.v43 * fInvFactorB;
	float v44B = _MatB1.v44 * _fFactorB + _MatB0.v44 * fInvFactorB; 

	v41 = v41B * _fFactor + v41A * fInvFactor;
	v42 = v42B * _fFactor + v42A * fInvFactor;
	v43 = v43B * _fFactor + v43A * fInvFactor;
	v44 = v44B * _fFactor + v44A * fInvFactor; 
}                          



//////////////////////////////////////////////////////////////////////////
/// does a blend between 3 matrixs. first blend mats A0-A1, then blends the result of that with matrix B

void TMatrix4::CalcBlend( const TMatrix4& _MatA0, const TMatrix4& _MatA1, float _fFactorA, 
													const TMatrix4& _MatB, float _fFactor )
{
	float fInvFactorA   = 1 - _fFactorA;
	float fInvFactor    = 1 - _fFactor;
		
	TQuat QuatA0, QuatA1, QuatB, QuatA, QuatFinal;
	_MatA0.CalcQuat( &QuatA0 );
	_MatA1.CalcQuat( &QuatA1 );
	_MatB.CalcQuat( &QuatB );

	//...A0-A1
	D3DXQUATERNION DXQuat0, DXQuat1, DXQuatInterp;
		
	DXQuat0.x = QuatA0.x;
	DXQuat0.y = QuatA0.y;
	DXQuat0.z = QuatA0.z;
	DXQuat0.w = QuatA0.w;

	DXQuat1.x = QuatA1.x;
	DXQuat1.y = QuatA1.y;
	DXQuat1.z = QuatA1.z;
	DXQuat1.w = QuatA1.w;
		
	D3DXQuaternionSlerp( &DXQuatInterp, &DXQuat0, &DXQuat1, _fFactorA );
		
	QuatA.x = DXQuatInterp.x;
	QuatA.y = DXQuatInterp.y;
	QuatA.z = DXQuatInterp.z;
	QuatA.w = DXQuatInterp.w;
		
	//....A-B
	DXQuat0.x = QuatA.x;
	DXQuat0.y = QuatA.y;
	DXQuat0.z = QuatA.z;
	DXQuat0.w = QuatA.w;

	DXQuat1.x = QuatB.x;
	DXQuat1.y = QuatB.y;
	DXQuat1.z = QuatB.z;
	DXQuat1.w = QuatB.w;
		
	D3DXQuaternionSlerp( &DXQuatInterp, &DXQuat0, &DXQuat1, _fFactor );
		
	QuatFinal.x = DXQuatInterp.x;
	QuatFinal.y = DXQuatInterp.y;
	QuatFinal.z = DXQuatInterp.z;
	QuatFinal.w = DXQuatInterp.w;
		
	//...final interpolated quaternion
	CalcFromQuat( QuatFinal );
		
	//..now interpolates the translations
	float v41A = _MatA1.v41 * _fFactorA + _MatA0.v41 * fInvFactorA;
	float v42A = _MatA1.v42 * _fFactorA + _MatA0.v42 * fInvFactorA;
	float v43A = _MatA1.v43 * _fFactorA + _MatA0.v43 * fInvFactorA;
	float v44A = _MatA1.v44 * _fFactorA + _MatA0.v44 * fInvFactorA; 

	float v41B = _MatB.v41;
	float v42B = _MatB.v42;
	float v43B = _MatB.v43;
	float v44B = _MatB.v44;

	v41 = v41B * _fFactor + v41A * fInvFactor;
	v42 = v42B * _fFactor + v42A * fInvFactor;
	v43 = v43B * _fFactor + v43A * fInvFactor;
	v44 = v44B * _fFactor + v44A * fInvFactor; 
}                          

