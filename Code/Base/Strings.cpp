//----------------------------------------------------------------------------
// support functions and macros for C style strings use
//----------------------------------------------------------------------------

#include "stdafx.h"
#include <stdarg.h>
#include <time.h>

#define VAL_CHECK_END_BUFFER 0x474AC725   //...just a randon value

//////////////////////////////////////////////////////////////////////////
// SprintfSafe
//
// Not very efficient. it uses double memory amount, and then does an strcpy of everything on top of the sprintf
// to be used where performance is not a problem

void SprintfSafe( char* _pszBuf, int _iBufTam, const char* _pszFmt, ... )
{
	ASSERT( _pszBuf );
		
	char* pszBuf = NEW char[ _iBufTam*2+4 ];  //..oversized for more secutiry...but it is not 100% safe
	va_list ap;
	va_start(ap, _pszFmt);
	*( (uint*)(pszBuf + _iBufTam ) ) = VAL_CHECK_END_BUFFER;
		
	vsprintf(pszBuf,_pszFmt, ap);
	va_end(ap);
		
	if ( *((uint*)(pszBuf+_iBufTam) ) != VAL_CHECK_END_BUFFER )
	{
		ASSERTLOG( false, ("SprintfSafe overflow\n") );
		pszBuf[_iBufTam-1] = 0;
	}
	else
		CopyString( _pszBuf, _iBufTam, pszBuf );
		
	SAFE_DELETE_ARRAY( pszBuf );
}


//////////////////////////////////////////////////////////////////////////
// this function returns the numeric value in an string of the style "nx", where n is a number. ie: "3x", "100x"
// returns INVALID_INT when the string is not of the right style

int GetMultiplicatorValue( const char* _psz )
{
	const int MAX_STR_SIZE = 50;
	char szBufTmp[ MAX_STR_SIZE ];
	int iVal = INVALID_INT;
	int iLen = strlen( _psz );
	if (iLen>0 && iLen<=MAX_STR_SIZE)
	{
		if (_psz[iLen-1]=='x' || _psz[iLen-1]=='X')
		{
			memcpy( szBufTmp, _psz, iLen-1 );
			szBufTmp[iLen-1] = 0;
			iVal = atoi( szBufTmp );
		}
	}
						
	return iVal;       
}


//////////////////////////////////////////////////////////////////////////
// builds a file name with adding date and time to a given filename

void AddTimeDateToFileName( char* _pszNewFileName, int _iSize, const char* _pszOldFileName )
{
	CopyString( _pszNewFileName, _iSize, _pszOldFileName );
	char* pszCut = strchr( _pszNewFileName, '.' );
	if (pszCut)
		*pszCut = 0;
	const char* pszExt = strchr( _pszOldFileName, '.' );

	// Insert date and time in backup file name
	char szDate[20];
	szDate[0] = 0;
	char szTime[20];
	szTime[0] = 0;
	_strdate( szDate );
	_strtime( szTime );

	szDate[2] = '-';
	szDate[5] = '-';
	szTime[2] = ';';
	szTime[5] = ';';

	CatString( _pszNewFileName, _iSize, "_");
	CatString( _pszNewFileName, _iSize, szDate );
	CatString( _pszNewFileName, _iSize, "_");
	CatString( _pszNewFileName, _iSize, szTime );
	if (pszExt)
		CatString( _pszNewFileName, _iSize, pszExt );
}
