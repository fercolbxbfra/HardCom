//----------------------------------------------------------------------------
// support functions and macros for C style strings use
//----------------------------------------------------------------------------

#include <string.h>

inline void CopyString( char *pszDest, int nDestSize, const char *pszOrig)
{
	if (pszOrig)
		strncpy(pszDest, pszOrig, nDestSize);
	pszDest[nDestSize-1] = '\0';
}

inline void CatString( char *pszDest, int nDestSize, const char *pszOrig)
{
	int nLen = strlen(pszDest);
	if (nLen < nDestSize - 1)
	{
		CopyString(pszDest + nLen, nDestSize - nLen, pszOrig);
	}
}

//....to compare strings without the !=0 stupid shit
inline bool IsEqualString( const char* psz1, const char* psz2 )
{
	return (strcmp( psz1, psz2 )==0);
}
inline bool IsEqualStringNoCase( const char* psz1, const char* psz2 )
{
	if (psz1==NULL || psz2==NULL)
		return psz1==psz2;
	else
		return (_stricmp( psz1, psz2 )==0);
}

inline bool IsEqualStringNoCaseNumChars( const char* psz1, const char* psz2, int _iNumChars )
{
	if (psz1==NULL || psz2==NULL)
		return psz1==psz2;
	else
		return (_strnicmp( psz1, psz2, _iNumChars )==0);
}


//...sprintf with buffer size checks
void SprintfSafe( char* _pszBuf, int _iBufTam, const char* _pszFmt, ... );

//...gets memory for an string, and copies it. WARNING, that memory has to be freed by the user
#define ALLOC_COPY_STRING( _pszOrig ) AllocCopyString( _pszOrig, __FILE__, __LINE__ )

inline char* AllocCopyString( const char* _pszOrig, const char* _pszFileNEW, uint _uLineNEW )
{
	char* pszDest = NULL;
	if (_pszOrig)
	{
		pszDest = NEW_MOVED( _pszFileNEW, _uLineNEW ) char[ strlen(_pszOrig)+1];
		strcpy( pszDest, _pszOrig );
	}
	return pszDest;
}

// Macros to manage strings that are not pointers. Because the simple check, strings with a size of 4 cant be used either.
#define CAT_2_STRINGS( buf, str1, str2 )        \
{                                               \
		ASSERT(sizeof(buf)!=4);                     \
		CopyString( buf, sizeof(buf), str1 );       \
		CatString ( buf, sizeof(buf), str2 );       \
}

#define COPY_STRING( dest, ori )                \
{                                               \
		ASSERT(sizeof(dest)!=4);                    \
		CopyString( dest, sizeof(dest), ori );      \
}

//...appends an string into another but dest CANT be a pointer. (it will fail when it is an string of size 4 also...)
#define CAT_STRING( dest, ori )             \
{                                           \
		ASSERT( sizeof(dest)!=4 );              \
		CatString( dest, sizeof(dest), ori );   \
}


//////////////////////////////////////////////////////////////////////////
inline const char* GetLitONOFF( bool _bPar )
{
	if (_bPar)
		return "ON";
	else
		return "OFF";
}


//////////////////////////////////////////////////////////////////////////
inline const char* GetLitBool( bool _bPar )
{
	if (_bPar)
		return "TRUE";
	else
		return "FALSE";
}


//////////////////////////////////////////////////////////////////////////
// retunrs true if the string is with "true"
//----------------------------------------------------------------------

inline bool Str2Bool( const char* _psz )
{
	char szBuf[128];
	const char* psz = _psz;
		
	while (*psz==' ')
	{
		psz++;
	}
		
	int iDest = 0;
	while (*psz!=0 && *psz!=' ' && iDest<sizeof(szBuf)-1)
	{
		szBuf[iDest]=*psz;
		psz++;
		iDest++;
	}
		
	szBuf[iDest] = 0;
				
	return IsEqualStringNoCase( szBuf, "true" );
}


//////////////////////////////////////////////////////////////////////////
// builds a file name with adding date and time to a given root filename

void AddTimeDateToFileName( char* _pszNewFileName, int _iSize, const char* _pszOldFileName );



//////////////////////////////////////////////////////////////////////////
// MACRO_PRINTF
//
// Macro to read printf data style in a function
// the format string has to be _pszFmt

#define MACRO_PRINTF( szBuffer, BufferSize )        \
		const int BUFFER_SIZE = BufferSize;              \
		char szBuffer[BUFFER_SIZE];                      \
		{                                               \
				const int CHECK = 0x0114455AA;              \
				va_list ap;                                 \
				va_start(ap, _pszFmt);                      \
				*((int*)(szBuffer+BUFFER_SIZE-4)) = CHECK;   \
				vsprintf(szBuffer, _pszFmt, ap);            \
				ASSERTM( *((int*)(szBuffer+BUFFER_SIZE-4)) == CHECK, ("Buffer overrun, probably memory leak now\n") );    \
				va_end(ap);                                 \
		}


//----------------------------------------------------------------------
// MACRO_PRINTF_FULLSIZE

#define MACRO_PRINTF_FULLSIZE( szBuffer, BufferSize )        \
		const int BUFFER_SIZE = BufferSize;              \
		char szBuffer[BUFFER_SIZE];                      \
		{                                               \
				char szBufferTemp[BUFFER_SIZE+4];            \
				const int CHECK = 0x0114455AA;              \
				va_list ap;                                 \
				va_start(ap, _pszFmt);                      \
				*((int*)(szBufferTemp+BUFFER_SIZE)) = CHECK; \
				vsprintf(szBufferTemp, _pszFmt, ap);        \
				ASSERTM( *((int*)(szBufferTemp+BUFFER_SIZE)) == CHECK, ("Buffer overrun, probably memory leak now\n") );    \
				va_end(ap);                                 \
				CopyString( szBuffer, sizeof(szBuffer), szBufferTemp ); \
		}                                               \

// this function returns the numeric value in an string of the style "nx", where n is a number. ie: "3x", "100x"
int         GetMultiplicatorValue( const char* _psz );