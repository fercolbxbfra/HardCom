//----------------------------------------------------------------------------
// BaseMath
//--------------------------------------------------------------------------

#pragma once

#include <math.h>
#include <float.h>

#define FLOAT_MAX       FLT_MAX
#define FLOAT_MAX_NEG   ( -FLT_MAX )

//////////////////////////////////////////////////////////////////////////
// checks if 2 floats are equal (within a difference of a delta value )

inline bool AreFloatEqual( float _f1, float _f2, float _fDelta = VAL_DELTA )
{
    return ( fabsf( _f1 - _f2 ) < _fDelta );
}

//////////////////////////////////////////////////////////////////////////

inline float SpeedKmToM( float _fKmh )
{
    return _fKmh * ( 1000.f / 3600.f );
}

//..macro version
#define SPEEDKMTOM( Kmh ) ( Kmh * ( 1000.f / 3600.f ) )


//////////////////////////////////////////////////////////////////////////

inline float SpeedMToKm( float _fms )
{
    return _fms * ( 3600.f / 1000.f );
}

//..macro version
#define SPEEDMTOKM( Kmh ) ( Kmh * ( 3600.f / 1000.f ) )


//////////////////////////////////////////////////////////////////////////
// converts a float number to the nearest int (7.6 -> 8, -7.6 -> -8, 7.4->7, -7.4 

inline int RoundNear( float _f )
{
    return int( floor( _f + 0.5f ) );
}


//////////////////////////////////////////////////////////////////////////
// returns the power of 2 value that is nearest and not less than the given value

inline int CalcNextPowerOf2( int _iVal )
{
    int iPowered = 1;
    
    while (iPowered<_iVal)
    {
        iPowered *= 2;
    }
    
    return iPowered;
}


//////////////////////////////////////////////////////////////////////////
// power of 2 value that is nearest and not greater than the given value

inline int CalcPrevPowerOf2( int _iVal )
{
    if (_iVal==0)
        return 0;
        
    int iPowered = 1;
    
    while (iPowered<_iVal)
    {
        iPowered *= 2;
        if (iPowered>_iVal)
        {
            iPowered /= 2;
            break;
        }
    }
    
    return iPowered;
}


//////////////////////////////////////////////////////////////////////////
// converts a normalized float value (-1 to 1), into a byte value, where -127 = -1, 0 = 0, 127 = 1
// used mostly for to pack components of normalized normals vectors

inline byte FloatNormToByte( float _v )
{
    return int ( _v * 127 ) + 127;
}

//////////////////////////////////////////////////////////////////////////
// converts a normalized float value (-1 to 1), into a 3 bit value, that is, a value between 0-6, where 3 = 0   ( 7 is not used )

inline byte FloatNormTo3Bits( float _v )
{
    return int ( _v * 3 ) + 3;
}    


//////////////////////////////////////////////////////////////////////////
// converts a normalized float value (-1 to 1), into a 2 bit value, that is, a value between 0-2, where 1 = 0   ( 3 is not used )

inline byte FloatNormTo2Bits( float _v )
{
    return int ( _v * 1 ) + 1;
}    


//////////////////////////////////////////////////////////////////////////
// converts a normalized float positive value (0 to 1), into a 3 bit value, that is, a value between 0-7

inline byte FloatTo3Bits( float _v )
{
    int iVal = min( int ( _v * 8 ), 7 );
    return iVal;
}    


//////////////////////////////////////////////////////////////////////////
// converts a normalized float positive value (0 to 1), into a 2 bit value, that is, a value between 0-3

inline byte FloatTo2Bits( float _v )
{
    int iVal = min( int ( _v * 4 ), 3 );
    return iVal;
}


//////////////////////////////////////////////////////////////////////////
/// Converts an integer value of bytes into kilobytes

inline float CalcKB( uint _uBytes )
{
    return _uBytes / (1024.f);
}


//////////////////////////////////////////////////////////////////////////
/// Converts an integer value of bytes into megabytes

inline float CalcMB( uint _uBytes )
{
    return _uBytes / (1024.f*1024.f);
}


//////////////////////////////////////////////////////////////////////////

inline float i64ToFloat( __int64 _val )
{
    uint* p = (uint*)&_val;

    float res = p[0] + p[1] * 4294967296.f;
    return res;
}


//////////////////////////////////////////////////////////////////////////

inline double i64ToDouble( __int64 _val )
{
    uint* p = (uint*)&_val;

    double res = p[0] + p[1] * 4294967296.0;
    return res;
}
