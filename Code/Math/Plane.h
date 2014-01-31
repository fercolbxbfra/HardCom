//----------------------------------------------------------------------------
// Planes
//----------------------------------------------------------------------------


#pragma once

#include "Vector.h"

struct TRay;

//...TODO: enum that defines intersection results. should be in a more generic place
enum EIntersect
{
	ITS_INTERSECT,
	ITS_IN,
	ITS_OUT,
		
	ITS_FRONT = ITS_IN,
	ITS_BACK = ITS_OUT
};

struct TPlane
{
	float a;
	float b;
	float c;
	float d;
		
	TPlane( const V3& _v1, const V3& _v2, const V3& _v3 );
	TPlane( const V3& _v1, const V3& _v2, float _d );
	TPlane( const V3& _vNorm, const V3& _vPoint );
	TPlane( float _a, float _b, float _c, float _d )
	{
			a = _a;
			b = _b;
			c = _c;
			d = _d;
	}

	TPlane(){}
		
	bool        InterSectRay        ( V3* _vInter, const TRay& _Ray );
	float       GetZ                ( float _x, float _y );
	void        Normalize           ();
	const char* GetStr              ();
	EIntersect  CalcIntersectSphere ( const V3& _vCenter, float _fRadius2 );
	bool        IsPointInFront      ( const V3& _vPos );
	bool        IsPointInPlane      ( const V3& _vPos );
	V3&         GetNorm             () { return *((V3*)this); } // sucio truco que solo funciona si se respeta el orden de a,b,c en el TPlane
};


//////////////////////////////////////////////////////////////////////////
// builds the plane from 2 vectors and D

inline TPlane::TPlane( const V3& _v1, const V3& _v2, float _d )
{
	V3 v = Cross(_v1,_v2);
	a = v.x;
	b = v.y;
	c = v.z;
	d = _d;
}


//////////////////////////////////////////////////////////////////////////
// builds the plane from its normal and a point 

inline TPlane::TPlane( const V3& _vNorm, const V3& _vPoint )
{
	a = _vNorm.x;
	b = _vNorm.y;
	c = _vNorm.z;
	d = -Dot( _vNorm, _vPoint );
}


//////////////////////////////////////////////////////////////////////////
// builds from 3 points

inline TPlane::TPlane( const V3& _v0, const V3& _v1, const V3& _v2 )
{
	V3 v1 = _v1 - _v0;
	V3 v2 = _v2 - _v1;
		
	V3 vN = Cross(v1, v2);
	vN.Normalize();
	a = vN.x;
	b = vN.y;
	c = vN.z;
		
	d = - Dot(vN, _v0);
}


//////////////////////////////////////////////////////////////////////////
// returns the Z of the plane at x,y

inline float TPlane::GetZ( float _x, float _y )
{
	if (fabs(c)>VAL_DELTA)
		return ( -d - a*_x - b*_y ) / c;
	else
		return 0;
}


//////////////////////////////////////////////////////////////////////////
// makes abc an unit vector

inline void TPlane::Normalize()
{
	float fMod = V3( a, b, c ).GetModule();
		
	a /= fMod;
	b /= fMod;
	c /= fMod;
	d /= fMod;   // needed so that the plane equation is still valid
}


//////////////////////////////////////////////////////////////////////////

inline EIntersect TPlane::CalcIntersectSphere ( const V3& _vCenter, float _fRadius2 )
{
	EIntersect eState = ITS_INTERSECT;

	float fDist     = Dot( GetNorm(), _vCenter ) + d;
	float fDist2    = fDist * fDist;
		
	if (fDist2>_fRadius2)
	{
		if (fDist>0)
			eState = ITS_FRONT;
		else
			eState = ITS_BACK;
	}
		
	return eState;
}



//////////////////////////////////////////////////////////////////////////
// para saber si un punto esta enel front del plano (hacia donde apunta la normal) o detras
//----------------------------------------------------------------------

inline bool TPlane::IsPointInFront( const V3& _vPos )
{
		return (Dot( GetNorm(), _vPos ) + d) > 0 ;
}



//----------------------------------------------------------------------
// IsPointInPlane
//
// para saber si un punto esta en un plano
//----------------------------------------------------------------------

inline bool TPlane::IsPointInPlane( const V3& _vPos )
{
		return (Dot( GetNorm(), _vPos ) + d) == 0 ;
}


//...
bool InterSectRayParalel( V3* _vInter, const TRay& _Ray, float _fAltura );

