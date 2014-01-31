//----------------------------------------------------------------------------
// Rays
//----------------------------------------------------------------------------


#pragma once

#include <math.h>

#include "Vector.h"

struct TRay
{
	V3 m_v3Orig;
	V3 m_v3Dir;
		

	TRay( V3 _v3Orig, V3 _v3Dir )
	{
		m_v3Orig = _v3Orig;
		m_v3Dir  = _v3Dir;
	}

	TRay(){}

	// builds the ray from origin + destination
	void Set( const V3& _vOrig, const V3& _vDest )
	{
		m_v3Orig    = _vOrig;
		V3 vDir     = _vDest - _vOrig;
		vDir.Normalize();
		m_v3Dir     = vDir;
	}
};
