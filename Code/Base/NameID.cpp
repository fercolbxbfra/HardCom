//----------------------------------------------------------------------------
// an string name (of limited size) used that can be used as identifier because is very efficiently managed
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "NameID.h"

const CNameID cNameID_Null = CNameID( "" );


//////////////////////////////////////////////////////////////////////////

CNameID::CNameID()
{
	Clear();
}


CNameID::CNameID( const char* _pszName )
{
	Set( _pszName );
}


//////////////////////////////////////////////////////////////////////////

void CNameID::Set( const char* _pszName )
{
	const char* psz = _pszName;
	char* pszID     = m_szName;
		
	if (_pszName)
	{
		int i=0;
		for (; i<NAMEID_SIZE && *psz!=0; i++)
		{
			*pszID++ = *psz++;
		}

		//...fill with zeroes
		while (i<NAMEID_SIZE)
		{
			*pszID++ = 0;
			i++;
		}
				
		if (*psz!='\0')
			LOG(("ERR: NameID capped: Original: '%s',  Result: '%s'", _pszName, m_szName ));
		_strupr( m_szName );
	}
	else 
	{
		memset( m_szName, 0, sizeof(m_szName) );
	}
}


//////////////////////////////////////////////////////////////////////////

void CNameID::SetFmt( const char* _pszFmt, ... )
{
	MACRO_PRINTF_FULLSIZE( szBuffer, NAMEID_SIZE );
	Set( szBuffer );
}


//////////////////////////////////////////////////////////////////////////

void CNameID::Clear()
{
	ASSERT( NAMEID_SIZE==32 );
		
	m_i64Part0 = 0;
	m_i64Part1 = 0;
	m_i64Part2 = 0;
	m_i64Part3 = 0;
}



//////////////////////////////////////////////////////////////////////////

bool CNameID::IsEqual ( const char* _pszName ) const
{
	bool bEqual = true;
		
	if (_pszName)
		bEqual = IsEqualStringNoCase( _pszName, m_szName );
	else
		bEqual = IsNull();
				
	return bEqual;
}


//////////////////////////////////////////////////////////////////////////

void CNameID::SetFromRoot( const char* _pszRaiz, int _iNumDigits, int _iNumber, const char* _pszSeparator  )
{
	ASSERT( _iNumDigits>0 && _iNumDigits<10 );
		
	char szNumber[10];
	char szFormat[5];
	CopyString( szFormat, sizeof(szFormat), "%04d" );
	szFormat[2] = '0' + _iNumDigits;
		
	SprintfSafe( szNumber, sizeof(szNumber), szFormat, _iNumber );
		
	char szTotal[NAMEID_SIZE];
	CopyString( szTotal, sizeof(szTotal), _pszRaiz );
	if (_pszSeparator)
		CatString( szTotal, sizeof(szTotal), _pszSeparator );
	CatString( szTotal, sizeof(szTotal), szNumber );
		
	Set( szTotal );
}


//////////////////////////////////////////////////////////////////////////

void CNameID::SetFromRootFmt( int _iNumDigits, int _iNumber, const char* _pszFmt, ... )
{
	MACRO_PRINTF_FULLSIZE( szBuffer, NAMEID_SIZE );
	SetFromRoot( szBuffer, _iNumDigits, _iNumber );
}


//////////////////////////////////////////////////////////////////////////

void CNameID::Set( const char* _pszStr1, const char* _pszStr2 )
{
	if (strlen( _pszStr1 ) + strlen( _pszStr2 ) >= NAMEID_SIZE )
	{
		LOG(("ERR: CNameID::Set-> '%s%s' exceeds maximum name size", _pszStr1, _pszStr2) );
	}
	char szBuf[NAMEID_SIZE];
	CopyString( szBuf, NAMEID_SIZE, _pszStr1 );
	CatString( szBuf, NAMEID_SIZE, _pszStr2 );    
		
	Set( szBuf );
}    



//////////////////////////////////////////////////////////////////////////

bool CNameID::IsRootEqual( const char* _pszRoot ) const
{
	return _strnicmp( _pszRoot, m_szName, strlen( _pszRoot ) )==0;
}



//////////////////////////////////////////////////////////////////////////
// Removes any file extension the name could have. (actually what it does is to remove everything after any '.' found)

void CNameID::RemoveFileExt()
{
	char* psz = m_szName;
		
	while (*psz!=0 && *psz!='.') { psz++; }
				
	while (*psz!=0)
	{
		*psz = 0;
		psz++;
	}
}


//////////////////////////////////////////////////////////////////////////

void CNameID::SetUpperCase()
{
	_strupr( m_szName );
}


//////////////////////////////////////////////////////////////////////////
// appends an string to the end

void CNameID::StrCat( const char* _psz )
{
	int iNChars = min( NAMEID_SIZE - strlen( m_szName ), strlen( _psz ) );
	strncat( m_szName, _psz, iNChars );
}
