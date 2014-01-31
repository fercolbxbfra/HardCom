//----------------------------------------------------------------------------
// Plane
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Plane.h"
#include "Ray.h"


//////////////////////////////////////////////////////////////////////////
// calcs intersection point between a plane and a ray. returns fale when there is no intersection

bool TPlane::InterSectRay( V3* _vInter, const TRay& _Ray )
{
	bool bHayInterseccion = false;
	V3 vTemp;
		
	float fTNum = (-d) - Dot(V3(a, b, c), _Ray.m_v3Orig );
	float fTDen = Dot( V3(a, b, c), _Ray.m_v3Dir );
		
	if (fabsf(fTDen)>VAL_DELTA)
	{
		bHayInterseccion = true;
		float fT = fTNum / fTDen;
				
		*_vInter = _Ray.m_v3Dir * fT + _Ray.m_v3Orig;
	}
		
	return bHayInterseccion; 
}



//////////////////////////////////////////////////////////////////////////
// returns a pointer to an string with the plavector formated value
// WARNING, the buffer used for this is static so it will be rewritten in subsequent calls

const char* TPlane::GetStr()
{
	static char szBuf[40];
	SprintfSafe( szBuf, sizeof(szBuf), "( %5.2f, %5.2f, %5.2f, %5.2f )", a, b, c, d );
	return szBuf;
}


//////////////////////////////////////////////////////////////////////////
// calculs intersection point between the plane and a line in parametrics form, defined in TRay.
// assumes that the plane is paralel to xy

bool InterSectRayParalel( V3* _vInter, const TRay& _Ray, float _fAltura )
{
	if (fabsf(_Ray.m_v3Dir.z)>VAL_DELTA)
	{
		float t = ( _fAltura - _Ray.m_v3Orig.z ) / _Ray.m_v3Dir.z;
		*_vInter = _Ray.m_v3Orig + ( _Ray.m_v3Dir * t );
		return true;
	}
	else
		return false;
}


