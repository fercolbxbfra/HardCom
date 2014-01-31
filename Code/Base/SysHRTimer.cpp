//----------------------------------------------------------------------------
// hardware High Resolution timer
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "SysHRTimer.h"


//////////////////////////////////////////////////////////////////////////

CSysHRTimer::CSysHRTimer()
{
	m_uFreq         = 0;
	m_fFreq         = 0;
	m_duTimerStart  = 0;
}



//////////////////////////////////////////////////////////////////////////

ERetVal CSysHRTimer::Init()
{
	LARGE_INTEGER Frecuency;
	ERetVal eRetVal = RET_OK;

	BOOL bThereIsAnHighResolutionTimeCounter = QueryPerformanceFrequency( &Frecuency );

	if (!bThereIsAnHighResolutionTimeCounter)
	{
		ERROR_UBER_CRITICAL(("ERR: Cant find an High Resolution Time Counter\n"));
		eRetVal = RET_ERR;
	}
	
	m_uFreq   = Frecuency.QuadPart;
	m_fFreq   = i64ToFloat( m_uFreq );
	
	m_duTimerStart = GetTimer();
	
	LOG(("Timer at: %f Mhz", m_fFreq / 1000000.f));
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////
// Reads the current value from the hardware timer

__int64 CSysHRTimer::ReadInternalCounter()
{
	LARGE_INTEGER queryValue;
	QueryPerformanceCounter( &queryValue );
	return queryValue.QuadPart;
}
		
		
