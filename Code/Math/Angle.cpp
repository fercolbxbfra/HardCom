//----------------------------------------------------------------------------
// Angle
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Vector.h"
#include "Angle.h"

const TAngle    cAngle_Zero     = TAngle(0);
const TDirAng3D cDirAng3D_Zero  = TDirAng3D( 0, 0 );


//////////////////////////////////////////////////////////////////////////

void TDirAng3D::Set( const V3& _vPos )
{
	// Angle around Z-axis
	AngXY = atan2f( _vPos.y, _vPos.x );
		
	// Elevation angle
	V2 vPosProj = _vPos;
	V2 vTmp     = V2( vPosProj.GetModule(), _vPos.z );
	AngEle      = vTmp.GetAngle();
}


//////////////////////////////////////////////////////////////////////////
// Returns a vector containing the angles for X, Y, Z

V3 TDirAng3D::GetAngles( void )
{
	return V3( 0, AngEle.m_fRad, AngXY.m_fRad );
}


//////////////////////////////////////////////////////////////////////////
// returns a normalized vector that represents the same direction than the angle

V2 TAngle::GetDir() const
{
	V2 v;
	v.x = cosf( m_fRad );
	v.y = sinf( m_fRad );
	return v;
}


//////////////////////////////////////////////////////////////////////////

void TAngle::SetDir( V2 _vDir )
{
	m_fRad = atan2f( _vDir.y, _vDir.x );
}