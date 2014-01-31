//----------------------------------------------------------------------------
// Angle
//----------------------------------------------------------------------------

#pragma once

#define DEG2RADCONST (PI*2/360)
#define RAD2GRADCONST (360/(PI*2))

#define DEG2RAD( grad ) ( grad * DEG2RADCONST )
#define RAD2GRAD( rad  ) ( rad  * RAD2GRADCONST )

#include <math.h>

struct V3;
struct V2I;
struct V2;


//////////////////////////////////////////////////////////////////////////
// 0-360 degrees -> rads. normalizes between -pi +pi

float inline Deg2RadNorm( float _fAngDecimal )
{
	while (_fAngDecimal>=180)
		_fAngDecimal-=360;

	while (_fAngDecimal<-180)
		_fAngDecimal+=360;
				
	return ( DEG2RADCONST * _fAngDecimal );
}



//////////////////////////////////////////////////////////////////////////
// 0-360 degrees into rads brute force

float inline Deg2Rad( float _fAngDecimal )
{
	return ( DEG2RADCONST * _fAngDecimal );
}


//////////////////////////////////////////////////////////////////////////
// radians angle into 0-360

float inline Rad2Grad( float _fAngRad )
{
	return ( RAD2GRADCONST * _fAngRad );
}

//################################ TAngle #########################################

struct TAngle
{
	float   m_fRad;           // Angle in radians
		
						TAngle          ( float _v ) { m_fRad = _v; }
						TAngle          ( void ) {}

	//TAngle      operator=       ( float _v ) { m_fRad = _v; return *this; };
	TAngle      operator=       ( TAngle _v ) { m_fRad = _v.m_fRad; return *this; };
	TAngle      operator+       ( TAngle _v ) const;
	TAngle      operator-       ( TAngle _v ) const;
	TAngle      operator+=      ( TAngle _v );
	TAngle      operator-=      ( TAngle _v );
	TAngle      operator*=      ( int _f );
	TAngle      operator*=      ( float _f );
	TAngle      operator/=      ( int _f );
	TAngle      operator/=      ( float _f );
	TAngle      operator/       ( int _f ) const;
	TAngle      operator*       ( int _f ) const;
	TAngle      operator/       ( float _f ) const;
	TAngle      operator*       ( float _f ) const;
	TAngle      operator-       ( void ) const;
	V2          GetDir          ( void ) const;
	void        SetDir          ( V2 _vDir );

	void        SetRad          ( float _fRad ) { m_fRad = _fRad; }
	void        SetDeg          ( float _fDeg ) { m_fRad = DEG2RAD( _fDeg ); }

	float       GetRad          ( void ) const  { return m_fRad; }
	float       GetDeg          ( void ) const  { return Rad2Grad( m_fRad ); }
		
	float       Distance        (TAngle& _Other) const
	{
		float fRet = _Other.m_fRad - m_fRad;
		if (fRet>PI)
			fRet -= 2*PI;
		else
		if (fRet<-PI)
			fRet += 2*PI;
						
		return fRet;
	}
		
	void        NormalizeAng       ( void )
	{
		while ( m_fRad < -PI )
			m_fRad += 2* PI;
		while ( m_fRad >= PI )
			m_fRad -= 2* PI;
	}
};


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator+=( TAngle _v )
{
	m_fRad += _v.m_fRad;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator*=( float _f )
{
	m_fRad *= _f;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator/=( float _f )
{
	m_fRad /= _f;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator-=( TAngle _v )
{
	m_fRad -= _v.m_fRad;
		
	return *this;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator+( TAngle _v ) const
{
	TAngle v = *this;
	v.m_fRad += _v.m_fRad;
		
	return v;
}

//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator-( TAngle _v ) const
{
	TAngle v = *this;
	v.m_fRad -= _v.m_fRad;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator-() const
{
	TAngle v = *this;
	v.m_fRad = -m_fRad;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator*( float _f ) const
{
	TAngle v = *this;
	v.m_fRad *= _f;
		
	return v;
}


//////////////////////////////////////////////////////////////////////////

inline TAngle TAngle::operator/( float _f ) const
{
	TAngle v = *this;
	v.m_fRad /= _f;
		
	return v;
}


//################################ TDirAng3D #########################################

//...direction 3D, defined by 2 angles
struct TDirAng3D
{
	TAngle AngXY;    //...direction in the XY plane
	TAngle AngEle;   //...elevation over that direction
		
	TDirAng3D( TAngle _AngXY, TAngle _AngEle ) { AngXY = _AngXY; AngEle = _AngEle; }
	TDirAng3D() {}
		
	void        Set             ( const V3& _vPos );
	V3          GetAngles       ( void );
	void        NormEle         ();
};

extern const TAngle     cAngle_Zero;
extern const TDirAng3D  cDirAng3D_Zero;



//////////////////////////////////////////////////////////////////////////
// makes sure the elevation ang is between 90 ad -90 degrees

inline void TDirAng3D::NormEle()
{
	if (AngEle.GetRad()>DEG2RAD( 90 ))
		AngEle.SetRad( DEG2RAD( 90 ) );
	if (AngEle.GetRad()<DEG2RAD( -90 ))
		AngEle.SetRad( DEG2RAD( -90 ) );
}



