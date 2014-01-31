//----------------------------------------------------------------------------
// Vector
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Vector.h"
#include "Angle.h"
#include "Matrix.h"
//#include "Ent.h"
#include "BaseMath.h"
#include "Plane.h"

#include <float.h>

//...constants...
const V3        cV3_Zero        = V3(0, 0, 0);
const V2        cV2_Zero        = V2(0, 0);
const V2I       cV2I_Zero       = V2I(0, 0);

const V3        cV3_Unit        = V3(1, 1, 1);
const V2        cV2_Unit        = V2(1, 1);
const V2I       cV2I_Unit       = V2I(1, 1);

const V3        cV3_Max         = V3(FLOAT_MAX, FLOAT_MAX, FLOAT_MAX);
const V2        cV2_Max         = V2(FLOAT_MAX, FLOAT_MAX);
const V2I       cV2I_Max        = V2I(INT_MAX, INT_MAX);

const V3        cV3_Min         = V3(FLOAT_MAX_NEG, FLOAT_MAX_NEG, FLOAT_MAX_NEG);
const V2        cV2_Min         = V2(FLOAT_MAX_NEG, FLOAT_MAX_NEG);
const V2I       cV2I_Min        = V2I(INT_MIN, INT_MIN);


//############################################################################3
// V2I
//############################################################################3


//////////////////////////////////////////////////////////////////////////
// calcs distance from a point to a line segment. -1 if the point is not inside the segment
//----------------------------------------------------------------------

float V2I::GetDistToSegment( const V2I& _vS0, const V2I& _vS1 )
{
  V2 vP = *this;
    
  return vP.GetDistToSegment( _vS0, _vS1 );
}

//////////////////////////////////////////////////////////////////////////
// returns a pointer to an string with the vector formated value
// WARNING, the buffer used for this is static so it will be rewritten in subsequent calls

const char* V2I::GetStr() const
{
  static char szBuf[SIZE_FOR_VECTOR_GETSTRCOPY];
  SprintfSafe( szBuf, sizeof(szBuf), "( %d, %d )", x, y );
  return szBuf;
}



//////////////////////////////////////////////////////////////////////////
// fills an string with the vector formated value

void V2I::GetStrCopy( char* _pszBuf, int _iBufSize ) const
{
  SprintfSafe( _pszBuf, _iBufSize, "( %d, %d )", x, y );
}


//############################################################################3
// V3
//############################################################################3

//////////////////////////////////////////////////////////////////////////
// returns a pointer to an string with the vector formated value
// WARNING, the buffer used for this is static so it will be rewritten in subsequent calls

const char* V3::GetStr() const
{
  static char szBuf[SIZE_FOR_VECTOR_GETSTRCOPY];
  SprintfSafe( szBuf, sizeof(szBuf), "( %5.2f, %5.2f, %5.2f )", x, y, z );
  return szBuf;
}

//////////////////////////////////////////////////////////////////////////
// fills an string with the vector formated value

void V3::GetStrCopy( char* _pszBuf, int _iBufSize ) const
{
  SprintfSafe( _pszBuf, _iBufSize, "( %5.2f, %5.2f, %5.2f )", x, y, z );
}


//////////////////////////////////////////////////////////////////////////
// Rotates vector the specified angle around a given axis

void V3::RotateAroundAxis( const V3& _vPivot, const TAngle& _tAngle )
{
  TMatrix3 RotMat;
  RotMat.SetRotationAxis( _vPivot, _tAngle.GetRad() );
  RotMat.Multiply( this, *this );
}


//############################################################################3
// V2
//############################################################################3

//////////////////////////////////////////////////////////////////////////
// calcs distance from a point to a line segment. -1 if the point is not inside the segment

float V2::GetDistToSegment( const V2& _vS0, const V2& _vS1 ) const
{
  V2 vIntersec;
  bool bValid = vIntersec.SetNearestPointInSegment( *this, _vS0, _vS1 );
  if (bValid)
  {
    vIntersec -= *this;
    return vIntersec.GetModule();
  }
  else return -1;
}

//////////////////////////////////////////////////////////////////////////
// calcs squared distance from a point to a line segment. -1 if the point is not inside the segment

float V2::GetDist2ToSegment( const V2& _vS0, const V2& _vS1 ) const
{
  V2 vIntersec;
  bool bValid = vIntersec.SetNearestPointInSegment( *this, _vS0, _vS1 );
  if (bValid)
  {
    vIntersec -= *this;
    return vIntersec.GetModule2();
  }
  else return -1;
}


//////////////////////////////////////////////////////////////////////////
// calcs the point inside a segment that is nearest to an external point.
// returns false if the resulting point is outside the segment

bool V2::SetNearestPointInSegment(  const V2& _vP, const V2& _vS0, const V2& _vS1 )
{
  V2 vSDelta = _vS1 - _vS0;
    
  V2 vControl = _vS0 - _vP;

  float t = - Dot(vSDelta, vControl) / Dot( vSDelta, vSDelta );
    
  bool bValid = false;
    
  //...if t is between 0 and 1, means that the point is inside the segment
  if (t>=0 && t<=1)
  {
    bValid = true;
    *this = ( vSDelta * t ) + _vS0;
  }
    
  return bValid;
}


//////////////////////////////////////////////////////////////////////////
// calcs intersection point between 2 segments
// returns false if they are paralel of the intersection point is outside the segments

bool V2::SetIntersection ( const V2& _vA0, const V2& _vA1, const V2& _vB0, const V2& _vB1 )
{
  V2 vADelta = _vA1 - _vA0; 
  V2 vBDelta = _vB1 - _vB0;
    
  //....vector that defines the line normal to the segment A
  V2 vN = vADelta;
  vN.Rotate90Clock();
    
  V2 vControl = _vB0 - _vA0;

  float Den = Dot( vN, vBDelta );
  bool bValid = false;
    
  if (fabs(Den)>VAL_DELTA) // if false, the lines are parallel
  {
    float t = -Dot( vN, vControl ) / Den;

    //...if t is between 0 and 1, the point was inside the segment
    if (t>=0 && t<=1)
    {
      //..test if the point is inside the other segment
      vN = vBDelta;
      vN.Rotate90Clock();
      vControl = _vA0 - _vB0;

      Den = Dot( vN, vADelta );
      if ( fabs(Den) > VAL_DELTA )
      {
        t = -Dot( vN, vControl ) / Den;
        if ( t >= 0 && t <= 1 )
        {
          bValid = true;
          *this = ( vADelta * t ) + _vA0;
        }
      }
    }
  }
    
  return bValid; 
}

/*
float V2::ProjectPointToSegment(V2 _vPos, V2 _vSegment0, V2 _vSegment1)
{
  float fLambda = 0.0f; 
  
  double dx = _vSegment1.x-_vSegment0.x;
  double dy = _vSegment1.y-_vSegment0.y;  
  
  double ddx    = double(dx*(_vPos.x-_vSegment0.x));
  double ddy    = double(dy*(_vPos.y-_vSegment0.y));
  double du     = ddx + ddy;
  double duAux  = du;
  double u2     = dx*dx + dy*dy;

  fLambda = 0.f;
  if (du!=0.f)
  {
    if (abs(duAux)<FLOAT_MAX*u2)
      fLambda = float(du/u2);
  }

  return fLambda;
}
*/


//////////////////////////////////////////////////////////////////////////
// returns a pointer to an string with the formated value
// WARNING, the buffer used for this is static so it will be rewritten in subsequent calls

const char* V2::GetStr( char* _pszFormat ) const
{
  static char szBuf[SIZE_FOR_VECTOR_GETSTRCOPY];
  if ( _pszFormat )
    SprintfSafe( szBuf, sizeof(szBuf), _pszFormat, x, y );
  else
    SprintfSafe( szBuf, sizeof(szBuf), "( %5.2f, %5.2f )", x, y );
  return szBuf;
}


//////////////////////////////////////////////////////////////////////////
// fills an string with the vector formated value

void V2::GetStrCopy( char* _pszBuf, int _iBufSize ) const
{
  SprintfSafe( _pszBuf, _iBufSize, "( %5.2f, %5.2f )", x, y );
}



//############################################################################3
// generic
//############################################################################3


//----------------------------------------------------------------------
// Name:    Distance2
// Desc:    Returns the square distance between two ents
//----------------------------------------------------------------------
/*
float Distance2( CEnt* _pEnt1, CEnt* _pEnt2 )
{
    return ( _pEnt1->GetPos() - _pEnt2->GetPos() ).GetModulo2();
}


//----------------------------------------------------------------------
// Name:    Distance
// Desc:    Returns the distance between two ents
//----------------------------------------------------------------------

float Distance( CEnt* _pEnt1, CEnt* _pEnt2 )
{ 
    return sqrt( Distance2( _pEnt1, _pEnt2 ) );
}
*/


//////////////////////////////////////////////////////////////////////////
// giving an axis, this calculate 2 vectors that are perpendicular to that axis and perpendicular between them
// they are normalized

void CalcCoorSysFromAxis( const V3& _vAxis, V3* _pvB0, V3* _pvB1 )
{
  V3 vPlaneP0 = _vAxis;
  TPlane Plane( _vAxis, vPlaneP0 ); 
  V3 vB0;
  vB0.x = vPlaneP0.x + 1;
  vB0.y = vPlaneP0.y + 1;
    
  vB0.z = (-Plane.d -(Plane.a*vB0.x) - (Plane.b*vB0.y)) / Plane.c;  // this calcs the z for apoint in the plane
    
  if ( (vB0-vPlaneP0).GetModule()<VAL_DELTA || fabsf(Plane.c)<VAL_DELTA)
  {
    vB0.y = vPlaneP0.y + 1;
    vB0.z = vPlaneP0.z + 1;
    vB0.x = (-Plane.d -(Plane.b*vB0.y) - (Plane.c*vB0.z)) / Plane.a;
    if ( (vB0-vPlaneP0).GetModule()<VAL_DELTA || fabsf(Plane.a)<VAL_DELTA)
    {
      vB0.x = vPlaneP0.x + 1;
      vB0.z = vPlaneP0.z + 1;
      vB0.y = (-Plane.d -(Plane.a*vB0.x) - (Plane.c*vB0.z)) / Plane.b;
    }
  }

  vB0 = vB0 - vPlaneP0;
    
  vB0.Normalize();
    
  V3 vB1 = vB0;
  TAngle Angle;
  Angle.SetDeg( 90 );
  vB1.RotateAroundAxis( _vAxis, Angle ); 
    
  *_pvB0 = vB0;
  *_pvB1 = vB1;
}
