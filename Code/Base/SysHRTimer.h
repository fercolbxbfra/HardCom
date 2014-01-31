//----------------------------------------------------------------------------
// hardware High Resolution timer
//----------------------------------------------------------------------------

#pragma once

#include "BaseMath.h"

class CSysHRTimer
{
	public:
			
																	CSysHRTimer             ();
			ERetVal                     Init                    ();
				
			float                       TimerToSecond           ( __int64 _duTimer );
			float                       TimerToMiliSecond       ( __int64 _duTimer ) { return TimerToSecond( _duTimer ) * 1000; }
			uint                        TimerToMiliSecondAccurate ( __int64 _duTimer );
			__int64                     GetTimer                () { return ReadInternalCounter(); }
			__int64                     GetTimerSinceStart      () { return ReadInternalCounter() - m_duTimerStart; }
			float                       GetSecondsSinceStart    () { return TimerToSecond( GetTimerSinceStart() ); }
			uint                        GetMiliSecondSinceStart () { return TimerToMiliSecondAccurate( GetTimerSinceStart()  ); }

	private:
			__int64                     ReadInternalCounter     ();
		

	private:
		
			__int64                     m_uFreq;
			__int64                     m_duTimerStart;
			float                       m_fFreq;
};



//////////////////////////////////////////////////////////////////////////
// raw timer value into seconds
		
inline float CSysHRTimer::TimerToSecond( __int64 _duTimer )
{
	return i64ToFloat(_duTimer) / m_fFreq;
}



//////////////////////////////////////////////////////////////////////////

inline uint CSysHRTimer::TimerToMiliSecondAccurate ( __int64 _duTimer )
{
	__int64 duMs = (_duTimer * 1000 ) / m_uFreq;
		
	return int(duMs);
}
