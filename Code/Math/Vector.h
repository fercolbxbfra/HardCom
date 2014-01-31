//----------------------------------------------------------------------------
// Vectors
//----------------------------------------------------------------------------

#pragma once

#include "BaseMath.h"
#include "Angle.h"


class   CEnt;
struct  V2;
struct  V2I;

#define SIZE_FOR_VECTOR_GETSTRCOPY 128   /// size that should be used for the buffers that are going to be used with GetStrCopy functions

struct V3
{
		float x, y, z;

								V3              ( float _x, float _y, float _z ) { x = _x; y = _y; z = _z; }
								V3              (){}
								V3              ( const V2& _v );
								V3              ( const V2I& _v );
								V3              ( const V2& _v, float _z );
								V3              ( const V2I& _v, float _z );
								
		V3          operator=       ( V2 _v );
		V3          operator=       ( V2I _v );
		V3          operator+=      ( V3 _v );
		V3          operator*=      ( float _f );
		V3          operator/=      ( float _f );
		V3          operator-=      ( V3 _v );
		V3          operator+       ( V3 _v ) const;
		V3          operator-       ( V3 _v ) const;
		V3          operator*       ( V3 _v ) const;
		V3          operator/       ( V3 _v ) const;
		V3          operator/       ( float _f ) const;
		V3          operator*       ( float _f ) const;
		V3          operator-       () const;
		bool        operator==      ( V3 _v ) const;
		bool        operator!=      ( V3 _v ) const;
		V2          GetV2           () const;
		void        RotateZ         ( float _fAng ); //..radianes
		void        ElevateY        ( float _fAng ); //..radianes
		void        RotateAroundAxis( const V3& _vPivot, const TAngle& _tAngle );
		
		float       GetModule       () const;
		float       GetModule2      () const;
		V3          Normalize       ();
		void        SetDirAngDeg    ( const TDirAng3D& _Dir );
		void        Rotate90ClockZAxis () { float t = x; x = -y; y = t; }
		
		const char* GetStr          () const;
		void        GetStrCopy      ( char* _pszBuf, int _iBufSize ) const;
};


struct V2
{
	union
	{
			float x;
			float u;
	};
		
	union
	{
			float y;
			float v;
	};

							V2                  ( float _x, float _y ) { x = _x; y = _y; }
							V2                  (){}
							V2                  ( const V3& _v ) { x = _v.x; y = _v.y; }
							V2                  ( const V2I& _v );
								
	V2          operator=           ( V3 _v );
	V2          operator=           ( V2I _v );
	V2          operator+=          ( V2 _v );
	V2          operator*=          ( float _f );
	V2          operator/=          ( float _f );
	V2          operator-=          ( V2 _v );
	V2          operator+           ( V2 _v ) const;
	V2          operator-           ( V2 _v ) const;
	V2          operator*           ( V2 _v ) const;
	V2          operator/           ( V2 _v ) const;
	V2          operator/           ( float _f ) const;
	V2          operator*           ( float _f ) const;
	V2          operator-           () const;
	bool        operator==          ( V2 _v ) const;
	bool        operator!=          ( V2 _v ) const;
								
	void        Rotate90Clock       () { float t = x; x = -y; y = t; }
	void        Rotate90AntiClock   () { float t = x; x = y; y = -t; }
	void        Rotate180             () { x = -x; y = -y; }
	float       GetModule           () const;
	float       GetModule2          () const;
	V2          Normalize           ();
	void        SetZero             () { x = 0.0f; y = 0.0f; };
	float       GetDistToSegment    ( const V2& _vS0, const V2& _vS1 ) const;
	float       GetDist2ToSegment   ( const V2& _vS0, const V2& _vS1 ) const;
	bool        SetNearestPointInSegment(  const V2& _vP, const V2& _vS0, const V2& _vS1 );
	bool        SetIntersection     ( const V2& _vA0, const V2& _vA1, const V2& _vB0, const V2& _vB1 );
	float       GetAngle            () const;
	void        Rotate              ( float _fAng ); //..radianes
	void        RotateAround        ( const V2& _vPivot, const TAngle& _tAngle );
	const char* GetStr              ( char* _pszFormat = NULL ) const;
	void        GetStrCopy          ( char* _pszBuf, int _iBufSize ) const;
	void        Saturate            ();
		
	//static float       ProjectPointToSegment(V2 _vPos, V2 _vSegment0, V2 _vSegment1);
};


struct V2I
{
	int x, y;

							V2I             ( int _x, int _y ) { x = _x; y = _y; }
							V2I             (){}
							V2I             ( const V3& _v ) { x = int(_v.x); y = int(_v.y); }
							V2I             ( const V2& _v ) { x = int(_v.x); y = int(_v.y); }
								
	V2I         operator=       ( V3 _v );
	V2I         operator=       ( V2 _v );
	bool        operator==      ( V2I _v ) const;
	bool        operator!=      ( V2I _v ) const;
	V2I         operator+=      ( V2I _v );
	V2I         operator*=      ( int _f );
	V2I         operator*=      ( float _f );
	V2I         operator/=      ( int _f );
	V2I         operator-=      ( V2I _v );
	V2I         operator+       ( V2I _v ) const;
	V2I         operator-       ( V2I _v ) const;
	V2I         operator/       ( V2I _v ) const;
	V2I         operator*       ( V2I _v ) const;
	V2I         operator/       ( int _f ) const;
	V2I         operator*       ( int _f ) const;
	V2I         operator/       ( float _f ) const;
	V2I         operator*       ( float _f ) const;
	V2I         operator-       () const;
	const char* GetStr          () const;
	void        GetStrCopy      ( char* _pszBuf, int _iBufSize ) const;

	void        Rotate90RClock  () { int it = x; x = -y; y = it; }
	void        Rotate90AntiClock() { int it = x; x = y; y = -it; }
	float       GetDistToSegment( const V2I& _vS0, const V2I& _vS1 );
	float       GetModule       () const;
	float       GetModule2      () const;
};




struct TQuad
{
	V3 v0, v1, v2, v3;
		
							TQuad           ( const V3& _v0, const V3& _v1, const V3& _v2, const V3& _v3 ) { v0 = _v0; v1 = _v1; v2 = _v2; v3 = _v3; }
							TQuad           () {}
};


struct TQuadV2
{
	V2 v0, v1, v2, v3;
		
							TQuadV2         ( const V2& _v0, const V2& _v1, const V2& _v2, const V2& _v3 ) { v0 = _v0; v1 = _v1; v2 = _v2; v3 = _v3; }
							TQuadV2         () {}
};



extern const V3         cV3_Zero;
extern const V2         cV2_Zero;
extern const V2I        cV2I_Zero;

extern const V3         cV3_Unit;
extern const V2         cV2_Unit;
extern const V2I        cV2I_Unit;

extern const V3         cV3_Max;
extern const V2         cV2_Max;
extern const V2I        cV2I_Max;

extern const V3         cV3_Min;
extern const V2         cV2_Min;
extern const V2I        cV2I_Min;



//############################################################################3
// V2I
//############################################################################3


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator=( V3 _v )
{
	x = int(_v.x);
	y = int(_v.y);
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator=( V2 _v )
{
	x = int(_v.x);
	y = int(_v.y);
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline bool V2I::operator==( V2I _v ) const
{
	if ( x != _v.x )
			return false;
	if ( y != _v.y )
			return false;

	return true;
}


//////////////////////////////////////////////////////////////////////////

inline bool V2I::operator!=( V2I _v ) const
{
	if ( x!=_v.x || y!=_v.y)
		return true;
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator+=( V2I _v )
{
	x += _v.x;
	y += _v.y;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator*=( int _f )
{
	x *= _f;
	y *= _f;
		
	return *this;
}

inline V2I V2I::operator*=( float _f )
{
	x = int( x * _f );
	y = int( y * _f );
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator/=( int _f )
{
	x /= _f;
	y /= _f;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator-=( V2I _v )
{
	x -= _v.x;
	y -= _v.y;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator+( V2I _v ) const
{
	V2I v = *this;
	v.x += _v.x;
	v.y += _v.y;
		
	return v;
}

//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator-( V2I _v ) const
{
	V2I v = *this;
	v.x -= _v.x;
	v.y -= _v.y;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator*( V2I _v ) const
{
	V2I v = *this;
	v.x *= _v.x;
	v.y *= _v.y;
		
	return v;
}

//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator/( V2I _v ) const
{
	V2I v = *this;
	v.x /= _v.x;
	v.y /= _v.y;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator-() const
{
	V2I v = *this;
	v.x = -x;
	v.y = -y;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator*( int _f ) const
{
	V2I v = *this;
	v.x *= _f;
	v.y *= _f;
		
	return v;
}

inline V2I V2I::operator*( float _f ) const
{
	V2I v = *this;
	v.x = int( v.x * _f );
	v.y = int( v.y * _f );
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2I V2I::operator/( int _f ) const
{
	V2I v = *this;
	v.x /= _f;
	v.y /= _f;
		
	return v;
}

inline V2I V2I::operator/( float _f ) const
{
	V2I v = *this;
	v.x = int( v.x / _f );
	v.y = int( v.y / _f );
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline float V2I::GetModule() const
{
	float fModulo = sqrtf( (float)x*(float)x + (float)y*(float)y );
	return fModulo;
}


//////////////////////////////////////////////////////////////////////////

inline float V2I::GetModule2() const
{
	float fModulo2 = (float)x*(float)x + (float)y*(float)y;
	return fModulo2;
}



//############################################################################3
// V3
//############################################################################3

//////////////////////////////////////////////////////////////////////////

inline V3::V3( const V2& _v )
{ 
	x = _v.x; 
	y = _v.y; 
	z = 0;
}


//////////////////////////////////////////////////////////////////////////

inline V3::V3( const V2& _v, float _z )
{ 
	x = _v.x; 
	y = _v.y; 
	z = _z;
}



//////////////////////////////////////////////////////////////////////////

inline V3::V3( const V2I& _v )
{ 
	x = float(_v.x);
	y = float(_v.y); 
	z = 0;
}


//////////////////////////////////////////////////////////////////////////

inline V3::V3( const V2I& _v, float _z )
{ 
	x = float(_v.x);
	y = float(_v.y); 
	z = _z;
}



//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator+=( V3 _v )
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator*=( float _f )
{
	x *= _f;
	y *= _f;
	z *= _f;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator/=( float _f )
{
	x /= _f;
	y /= _f;
	z /= _f;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator-=( V3 _v )
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator+( V3 _v ) const
{
	V3 v = *this;
	v.x += _v.x;
	v.y += _v.y;
	v.z += _v.z;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator-( V3 _v ) const
{
	V3 v = *this;
	v.x -= _v.x;
	v.y -= _v.y;
	v.z -= _v.z;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator*( V3 _v ) const
{
	V3 v = *this;
	v.x *= _v.x;
	v.y *= _v.y;
	v.z *= _v.z;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator/( V3 _v ) const
{
	V3 v = *this;
	v.x /= _v.x;
	v.y /= _v.y;
	v.z /= _v.z;
		
	return v;
}



//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator-() const
{
	V3 v = *this;
	v.x = -x;
	v.y = -y;
	v.z = -z;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator*( float _f ) const
{
	V3 v = *this;
	v.x *= _f;
	v.y *= _f;
	v.z *= _f;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator/( float _f ) const
{
	V3 v = *this;
	v.x /= _f;
	v.y /= _f;
	v.z /= _f;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator=( V2 _v ) { x = _v.x; y = _v.y; return *this; }                


//////////////////////////////////////////////////////////////////////////

inline V3 V3::operator=( V2I _v )
{
	x = float(_v.x);
	y = float(_v.y);
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline bool V3::operator==( V3 _v ) const
{
	if ( abs(_v.x - x) > VAL_DELTA )
		return false;
	if ( abs(_v.y - y) > VAL_DELTA )
		return false;
	if ( abs(_v.z - z) > VAL_DELTA )
		return false;

	return true;
}


//////////////////////////////////////////////////////////////////////////

inline bool V3::operator!=( V3 _v ) const
{
	if ( abs(_v.x - x)>VAL_DELTA || abs(_v.y - y)>VAL_DELTA || abs(_v.z - z)>VAL_DELTA )
		return true;
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////

inline V3 V3::Normalize()
{
	float fModule = sqrtf( x*x + y*y + z*z );
//    ASSERT (fModule>VAL_DELTA*VAL_DELTA);
	x = x / fModule;
	y = y / fModule;
	z = z / fModule;
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline float V3::GetModule() const
{
	float fModule = sqrtf( x*x + y*y + z*z );
	return fModule;
}


//////////////////////////////////////////////////////////////////////////

inline float V3::GetModule2() const
{
	float fModule = x*x + y*y + z*z;
	return fModule;
}


//////////////////////////////////////////////////////////////////////////
// converts a direction given in angles into a direction vector

inline void V3::SetDirAngDeg( const TDirAng3D& _Dir )
{
	float fEle = _Dir.AngEle.GetRad();
	float fXY  = _Dir.AngXY.GetRad();
	z = sinf( fEle );
		
	float fHorMod = cosf( fEle );
		
	x = fHorMod * cosf( fXY );
	y = fHorMod * sinf( fXY );
}


//////////////////////////////////////////////////////////////////////////

inline V2 V3::GetV2() const
{
	return V2(x,y);
}


//////////////////////////////////////////////////////////////////////////
// rotate the vector an amount of angle in rads, around Z axis

inline void V3::RotateZ( float _fAngle )
{
	float fSin = sinf( _fAngle );
	float fCos = cosf( _fAngle );

	float xa = x;
	x = x * fCos - y * fSin;
	y = xa * fSin + y * fCos;    
}


//////////////////////////////////////////////////////////////////////////
//
// is called ElevateY and not rotate because in our coordinate system a positive rotation in Y is downwards, while this function uses positive values to go upwards
// mientras que este elevate toma como positivas rotaciones hacia arriba
//----------------------------------------------------------------------

inline void V3::ElevateY( float _fAngle )
{
	TDirAng3D Ang;
	Ang.Set( *this );
	Ang.AngEle.m_fRad += _fAngle;
	SetDirAngDeg( Ang );
}




//############################################################################3
// V2
//############################################################################3

//////////////////////////////////////////////////////////////////////////

inline V2::V2( const V2I& _v )
{ 
	x = float(_v.x);
	y = float(_v.y); 
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator=( V3 _v )
{
	x = _v.x;
	y = _v.y;
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator=( V2I _v )
{
	x = float(_v.x);
	y = float(_v.y);
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline bool V2::operator==( V2 _v ) const
{
	if ( abs(_v.x - x) > VAL_DELTA )
		return false;
	if ( abs(_v.y - y) > VAL_DELTA )
		return false;

	return true;
}


//////////////////////////////////////////////////////////////////////////

inline bool V2::operator!=( V2 _v ) const
{
	if ( abs(_v.x - x)>VAL_DELTA || abs(_v.y - y)>VAL_DELTA )
		return true;
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator+=( V2 _v )
{
	x += _v.x;
	y += _v.y;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator*=( float _f )
{
	x *= _f;
	y *= _f;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator/=( float _f )
{
	x /= _f;
	y /= _f;

	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator-=( V2 _v )
{
	x -= _v.x;
	y -= _v.y;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator+( V2 _v ) const
{
	V2 v = *this;
	v.x += _v.x;
	v.y += _v.y;
		
	return v;
}

//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator-( V2 _v ) const
{
	V2 v = *this;
	v.x -= _v.x;
	v.y -= _v.y;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator*( V2 _v ) const
{
	V2 v = *this;
	v.x *= _v.x;
	v.y *= _v.y;
		
	return v;
}

//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator/( V2 _v ) const
{
	V2 v = *this;
	v.x /= _v.x;
	v.y /= _v.y;
		
	return v;
}

//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator-() const
{
	V2 v = *this;
	v.x = -x;
	v.y = -y;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator*( float _f ) const
{
	V2 v = *this;
	v.x *= _f;
	v.y *= _f;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline V2 V2::operator/( float _f ) const
{
	V2 v = *this;
	v.x /= _f;
	v.y /= _f;
		
	return v;
}



//////////////////////////////////////////////////////////////////////////

inline V2 V2::Normalize()
{
	float fModule = sqrtf( x*x + y*y );
//    ASSERT (fModulo>VAL_DELTA*VAL_DELTA);
	x = x / fModule;
	y = y / fModule;
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline float V2::GetModule() const
{
	float fModule = sqrtf( x*x + y*y );
	return fModule;
}


//////////////////////////////////////////////////////////////////////////

inline float V2::GetModule2() const
{
	float fModule = x*x + y*y;
	return fModule;
}



//////////////////////////////////////////////////////////////////////////

inline float V2::GetAngle() const
{
	return atan2f( y, x );
}


//////////////////////////////////////////////////////////////////////////

inline void V2::Rotate( float _fAngle )
{
	float fSin = sinf( _fAngle );
	float fCos = cosf( _fAngle );

	float xa = x;
	x = x * fCos - y * fSin;
	y = xa * fSin + y * fCos;    
}


//////////////////////////////////////////////////////////////////////////
// Rotates vector around pivot

inline void V2::RotateAround( const V2& _vPivot, const TAngle& _tAngle )
{
	// Translate
	x  -= _vPivot.x;
	y  -= _vPivot.y;

	// Rotate
	float fSin  = sinf( _tAngle.m_fRad );
	float fCos  = cosf( _tAngle.m_fRad );
	float xa    = x;
	x           = x * fCos - y * fSin;
	y           = xa * fSin + y * fCos;

	// Return to previous axis
	x  += _vPivot.x;
	y  += _vPivot.y;
}


//////////////////////////////////////////////////////////////////////////
// clip the values between 0..1

inline void V2::Saturate()
{
	if (u<0)
		u = 0;
	if (v<0)
		v = 0;
	if (u>1)
		u = 1;
	if (v>1)
		v = 1;
}



//############################################################################
// independent functions
//############################################################################

float   Distance2   ( CEnt* _pEnt1, CEnt* _pEnt2 );
float   Distance    ( CEnt* _pEnt1, CEnt* _pEnt2 );


//////////////////////////////////////////////////////////////////////////
// cross product
//----------------------------------------------------------------------

inline V3 Cross ( const V3& _v0, const V3& _v1 )
{
	V3 v;
	v.x = _v0.y*_v1.z - _v0.z*_v1.y;
	v.y = _v0.z*_v1.x - _v0.x*_v1.z;
	v.z = _v0.x*_v1.y - _v0.y*_v1.x;
	return v;
}


//////////////////////////////////////////////////////////////////////////
// dot product

inline float Dot( const V3& _v0, const V3& _v1 )
{
	return _v0.x * _v1.x + _v0.y * _v1.y + _v0.z * _v1.z;
}

inline float Dot( const V2& _v0, const V2& _v1 )
{
	return _v0.x * _v1.x + _v0.y * _v1.y;
}

inline int Dot( const V2I& _v0, const V2I& _v1 )
{
	return _v0.x * _v1.x + _v0.y * _v1.y;
}


//////////////////////////////////////////////////////////////////////////
// perp product

inline float Perp( const V2& _v0, const V2& _v1 )
{
	return( (_v0.x*_v1.y) - (_v0.y*_v1.x) );
}


//////////////////////////////////////////////////////////////////////////
// Projects point to segment and returns delta. If delta's
//  value between 0..1, to projected point lies in the segment

inline float ProjectPointToSegment( const V2& _vPos, const V2& _vS0, const V2& _vS1 )
{
	V2      vV      = _vPos - _vS0;
	V2      vD      = _vS1 - _vS0;
	float   fDelta  = Dot( vD, vV ) / vD.GetModule2();

	return fDelta;
}


//////////////////////////////////////////////////////////////////////////
//     Projects point to segment and returns delta and the projected
//     point. If delta's value between 0..1, to projected point lies
//     in the segment
//----------------------------------------------------------------------

inline float ProjectPointToSegment( const V2& _vPos, const V2& _vS0, const V2& _vS1, V2* _vProj )
{
	V2      vV      = _vPos - _vS0;
	V2      vD      = _vS1 - _vS0;
	float   fDelta  = Dot( vD, vV ) / vD.GetModule2();

	// Return the intersection point
	*_vProj         = vD * fDelta + _vS0;

	// Return delta value
	return fDelta;
}


//////////////////////////////////////////////////////////////////////////

inline float geom2d_signed_dist_point_to_segment(
	float _x, float _y,
	float _x0,float _y0,float _Dx,float _Dy
	)
{
	double dx =  _x - _x0;
	double dy =  _y - _y0;
	double su =  _Dx*dx + _Dy*dy;
	double du = -_Dy*dx + _Dx*dy;
	if ( su<0.0 )
		// before start point, return distance to start point
		return (float)((du<0.f?-1.f:1.f) * sqrt( dx*dx+dy*dy ));
	double u2 =  _Dx*_Dx + _Dy*_Dy;
	if (su>u2)
		// after end point, return distance to end point
		return (float)((du<0.f?-1.f:1.f)* sqrt( u2+dx*(dx-2.0*_Dx)+dy*(dy-2.0*_Dy)));
	else
	{
		// within segment
		double u = sqrt((float)u2);
		if (abs(du)>=FLOAT_MAX*u) // segment is too small for floats, return +distance to start point
			return (float)(sqrt( dx*dx + dy*dy ));
		else // return distance to line
			return float(du/u);
	}
}


void CalcCoorSysFromAxis( const V3& _vAxis, V3* _pvB0, V3* _pvB1 );







