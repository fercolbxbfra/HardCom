//----------------------------------------------------------------------------
// separates a text in its basic components (tokens). Used as tool from other modules to parse setup files, scripts and stuff
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Tokenizer.h"
#include "File.h"
#include <stdlib.h>

#define ATOMIC_TOKENS   "!&/()=*][{}<>|:"  
#define SEPARATORS      ","  
#define STRING_DELIMITER  '"'


//..comentaries. 
#define REM_LINE                "//"
#define REM_BLOCK_START         "/*"
#define REM_BLOCK_END           "*/"
#define SIZE_REM                2    //..WARNING, changing this value is not enough. the code assumes in some places that the size is 2


//////////////////////////////////////////////////////////////////////////

CTokenizer::~CTokenizer()
{
	if (m_bOk)
	{
		SAFE_DELETE_ARRAY( m_pBuffer );
		SAFE_DELETE_ARRAY( m_paTokens );
		SAFE_DELETE_ARRAY( m_pBufferTokens );
		SAFE_DELETE_ARRAY( m_pszFileName );
		SAFE_DELETE_ARRAY( m_pszAtomicTokens );
		SAFE_DELETE_ARRAY( m_pszSeparators );
	}
}


//////////////////////////////////////////////////////////////////////////
// Initializes tokenizer supplying atomic tokens and separators

ERetVal CTokenizer::Init( const char* _pszAtomicTokens, const char* _pszSeparadores, bool _bSpaceIsSeparator )
{
	ERetVal eRetVal = RET_OK;
		
	// Init pointers
	m_paTokens          = NULL;
	m_pBufferTokens     = NULL;
	m_pBuffer           = NULL;
	m_pszFileName       = NULL;
	m_pszAtomicTokens   = NULL;
	m_pszSeparators    = NULL;
		
	// Init separators and tokens
	if ( _pszAtomicTokens == NULL )
		m_pszAtomicTokens = ALLOC_COPY_STRING( ATOMIC_TOKENS );
	else
		m_pszAtomicTokens = ALLOC_COPY_STRING( _pszAtomicTokens );

	if ( _pszSeparadores == NULL )
		m_pszSeparators = ALLOC_COPY_STRING( SEPARATORS );
	else
		m_pszSeparators = ALLOC_COPY_STRING( _pszSeparadores );
				
	m_iLowAsciiSeparator = 33;  // this meants all chars below this are separators also
	if (!_bSpaceIsSeparator)
		m_iLowAsciiSeparator = 32;
		
	m_bOk           = ( eRetVal == RET_OK );
	m_bDataParsed   = false;
		
	return eRetVal;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CTokenizer::DoParseFile( const char* _pszFileName, bool _bNoPack, bool _bLookInAndOutPack )
{
	ERetVal eRetVal = RET_OK;
		
	eRetVal = ReadFile( _pszFileName, _bNoPack, _bLookInAndOutPack );
		
	if ( eRetVal == RET_OK )
	{
		ProcessBuffer( true );  //..count tokens
		ProcessBuffer( false );   //..store tokens
		SAFE_DELETE_ARRAY( m_pBuffer );
	}
				
	m_bDataParsed = ( eRetVal == RET_OK );
		
	return eRetVal;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CTokenizer::DoParseFile( const char* _pszDir, const char* _pszFileName, bool _bNoPack, bool _bLookInAndOutPack )
{
	char szFullFileName[ MAX_FILENAME_SIZE ];
	CAT_2_STRINGS( szFullFileName, _pszDir, _pszFileName );
	return DoParseFile( szFullFileName, _bNoPack, _bLookInAndOutPack );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CTokenizer::DoParseBuffer( const char* _pBuffer, uint _uTam )
{
	ERetVal eRetVal = RET_OK;
		
	m_pszFileName   = NULL;
	m_uSizeBuffer    = _uTam;
		
	m_pBuffer = NEW char[ _uTam ];
	memcpy( m_pBuffer, _pBuffer, _uTam );
		
	ProcessBuffer( true );  //..count tokens
	ProcessBuffer( false );   //..store the tokens
		
	SAFE_DELETE_ARRAY( m_pBuffer );
		
	m_bDataParsed = ( eRetVal == RET_OK );
		
	return eRetVal;
}

				
//////////////////////////////////////////////////////////////////////////

ERetVal CTokenizer::ReadFile( const char* _pszFileName, bool _bNoPack, bool _bLookInAndOutPack )
{
	ERetVal eRetVal = RET_OK;
		
	//....open it...
	CFile vF;
	if (_bNoPack)
		vF.SetNoPack();
	if (_bLookInAndOutPack)
		vF.SetLookInAndOutPack();
				
	eRetVal = vF.Open( _pszFileName );
		
	//..see file size
	if (eRetVal==RET_OK)
	{
		m_pszFileName = ALLOC_COPY_STRING(_pszFileName);
		m_uSizeBuffer = vF.GetSize();
		if (m_uSizeBuffer<1)
		{
			LOG(("ERR: Tokenizer. File : '%s' is too small.", _pszFileName));
			eRetVal = RET_ERR;
		}
	}    
		
		
	//....read the file........        
	if (eRetVal==RET_OK)
	{
		m_pBuffer = NEW char[m_uSizeBuffer];
		vF.Read( m_pBuffer, m_uSizeBuffer );
		vF.Close();
	}
		
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////
// where the actual text processing and token separation happens

void CTokenizer::ProcessBuffer( bool _bOnlyCount )
{
	uint uPointer  = 0;
	uint uToken = 0;
	uint uPointerBufferTokens = 0;
	int iNumLine = 1;

	SAFE_DELETE_ARRAY( m_paTokens );
	SAFE_DELETE_ARRAY( m_pBufferTokens );
		
	if (_bOnlyCount)
	{
		m_uNumTokens       = 0;
		m_paTokens          = NULL;
	}
	else
	{
		m_paTokens = NEW TToken[ m_uNumTokens ];
		m_pBufferTokens = NEW char[ m_uSizeBufferTokens ]; // reservs memory for all tokens + the 0 ending on each one of them
	}
		
	do
	{
		//...skip separators....
		while (!IsFinal( uPointer) && IsSeparator( uPointer ))
		{
			if (IsEndOfLine(uPointer))
				iNumLine++;
			uPointer++;
		}
						
		if (!IsFinal( uPointer ))
		{                            
			uint uPosIniToken   = uPointer;
			uint uSizeToken      = 0;
			bool bIsToken       = true;
						
			enum { TP_ATOMIC, TP_NORMAL, TP_STRING, TP_REM_LINE, TP_REM_BLOCK, TP_NOTHING } eType = TP_NOTHING;
						
			if (IsRemLine( uPointer ))
				eType = TP_REM_LINE;
			if (eType==TP_NOTHING && IsRemBlockStart( uPointer ))
				eType = TP_REM_BLOCK;
			if (eType==TP_NOTHING && IsCharAtomicToken( uPointer ))  
				eType = TP_ATOMIC;
			if (eType==TP_NOTHING && IsCharNormalToken( uPointer ))
				eType = TP_NORMAL;
			if (eType==TP_NOTHING && IsCharStringDelimiter( uPointer ))
				eType = TP_STRING;
								
			switch (eType)
			{
				// if is a char of an atomic token it skips the search for the end of the token
				case TP_ATOMIC:
				{
					uSizeToken++;
					uPointer++;
					break;
				}
										
				// is a normal token...               
				case TP_NORMAL:
				{
					while ( !IsFinal(uPointer) && IsCharNormalToken( uPointer ))
					{
						uPointer++;
						uSizeToken++;
					}
					break;
				}
								
				//...is an string...
				case TP_STRING:
				{
					uPointer++;        // skips initial '"'
					uPosIniToken++; //
					ASSERTLOG( !IsFinal(uPointer), ("End of string not found. File: '%s'    Line(aprox): %d\n", m_pszFileName, iNumLine ));
					while ( !IsFinal(uPointer) && !IsCharStringDelimiter( uPointer ) )
					{
						if (IsCharCR(uPointer))
								iNumLine++;
						uPointer++;
						uSizeToken++;
						ASSERTLOG( !IsFinal(uPointer), ("End of string not found. File: '%s'    Line(aprox): %d\n", m_pszFileName, iNumLine ));
					}
					if (!IsFinal(uPointer))
						uPointer++; // skips the ending '"'
					break;
				}
								
				//.....line coment
				case TP_REM_LINE:
				{
					bIsToken = false;
					uPointer   += SIZE_REM; //..skips "//"
					while (!IsFinal(uPointer) && !IsEndOfLine( uPointer ) )
					{
						uPointer++;
					}
					break;
				}


				//...block coment
				case TP_REM_BLOCK:
				{
					bIsToken = false;
					uPointer   += SIZE_REM; //..se salta el "/*"
					ASSERTM( !IsFinal(uPointer), ("End of comment not found. File: '%s'    Line(aprox): %d\n", m_pszFileName, iNumLine ));
					int iNumLineStart = iNumLine;
					int iLvl = 1;  //...deep counter for nested comments
					while (!IsFinal(uPointer) && ( !IsRemBlockEnd(uPointer) || iLvl>1) )
					{
						if (IsRemBlockStart(uPointer))
							iLvl++;
						if (IsRemBlockEnd(uPointer))
							iLvl--;
						ASSERT( iLvl>0 );
						if (IsEndOfLine(uPointer))
							iNumLine++;
						uPointer++;
						ASSERTLOG( !IsFinal(uPointer), ("End of comment not found. File: '%s'    Line(aprox): %d\n", m_pszFileName, iNumLineStart ));
					}
					if (!IsFinal(uPointer))
						uPointer += SIZE_REM; //..skips "*/"
					break;
				}
			}
						
			//...puts the token info into the array.
			if (bIsToken)
			{
				if (!_bOnlyCount)
				{
					ASSERT( uToken<m_uNumTokens );
										
					memcpy( m_pBufferTokens + uPointerBufferTokens, m_pBuffer + uPosIniToken, uSizeToken );
					m_pBufferTokens[ uPointerBufferTokens + uSizeToken ] = 0;
					m_paTokens[ uToken ].pszToken   = m_pBufferTokens + uPointerBufferTokens;
					m_paTokens[ uToken ].iLineNum   = iNumLine;
				}
				uToken++;
				uPointerBufferTokens += uSizeToken + 1;;
			}
		}
	} while (!IsFinal(uPointer));
		
	m_uNumTokens       = uToken;
	m_uSizeBufferTokens  = uPointerBufferTokens;
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsSeparator( uint _uPointer )
{
	bool bIsSeparador = false;
		
	if (m_pBuffer[_uPointer]<m_iLowAsciiSeparator)
		bIsSeparador = true;
	else
		bIsSeparador = (strchr( m_pszSeparators, m_pBuffer[_uPointer] )!=NULL);
		
	return bIsSeparador;
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsCharAtomicToken( uint _uPointer )
{
	if (strchr( m_pszAtomicTokens, m_pBuffer[_uPointer] )!=NULL)
		return true;
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsCharNormalToken( uint _uPointer )
{
	return (!IsSeparator(_uPointer) && !IsCharAtomicToken(_uPointer) && !IsCharStringDelimiter(_uPointer)  );
}

//////////////////////////////////////////////////////////////////////////
// true if the character is an string delimiter

bool CTokenizer::IsCharStringDelimiter( uint _uPointer )
{
	return m_pBuffer[_uPointer] == STRING_DELIMITER;
}



//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsCharCR( uint _uPointer )
{
	return m_pBuffer[_uPointer]==CR;
}



//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsDoubleChar( const char* _psz, uint _uPointer )
{
	if (!IsFinal(_uPointer+1))
	{
		return m_pBuffer[_uPointer]==_psz[0] && m_pBuffer[_uPointer+1]==_psz[1];
	}
	else
		return false;
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsRemLine( uint _uPointer )
{
	return IsDoubleChar( REM_LINE, _uPointer );
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsRemBlockStart( uint _uPointer )
{
	return IsDoubleChar( REM_BLOCK_START, _uPointer );
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsRemBlockEnd( uint _uPointer )
{
	return IsDoubleChar( REM_BLOCK_END, _uPointer );
}



//////////////////////////////////////////////////////////////////////////

bool CTokenizer::IsEndOfLine( uint _uPointer )
{
	return (m_pBuffer[_uPointer]==CR);
}


//////////////////////////////////////////////////////////////////////////
// returns pointer to the struct with the info for the specified token

const CTokenizer::TToken* CTokenizer::GetToken( uint _uToken ) const
{
	const TToken* pToken = NULL;
	ASSERT( _uToken<m_uNumTokens );
		
	if (_uToken<m_uNumTokens)
		pToken = m_paTokens + _uToken;
				
	return pToken;
}



//////////////////////////////////////////////////////////////////////////

const char* CTokenizer::GetTokenStr( uint _uToken ) const
{
	ASSERT( _uToken<m_uNumTokens );
		
	if (_uToken<m_uNumTokens)
		return m_paTokens[_uToken].pszToken;
	else
		return NULL;
}


//////////////////////////////////////////////////////////////////////////
// returns first char of the token

char CTokenizer::GetTokenChar( uint _uToken ) const
{
	ASSERTM( _uToken<m_uNumTokens, ("file: %s", m_pszFileName) );
		
	if (_uToken<m_uNumTokens)
		return m_paTokens[_uToken].pszToken[0];
	else
		return NULL;
}



//////////////////////////////////////////////////////////////////////////
// return the line number of the token

int CTokenizer::GetTokenLineNum( uint _uToken ) const
{
	ASSERTM( _uToken<m_uNumTokens, ("file: %s", m_pszFileName)  );
		
	if (_uToken<m_uNumTokens)
		return m_paTokens[_uToken].iLineNum;
	else
		return -1;
}



//////////////////////////////////////////////////////////////////////////
// returns atoi of a token

int CTokenizer::GetTokenValueInt( uint _uToken ) const
{
	const char* psz = GetTokenStr( _uToken );
	int iVal = 0;
		
	if (psz)
		iVal = atoi( psz );
		
	return iVal;
}


//////////////////////////////////////////////////////////////////////////

bool CTokenizer::GetTokenValueBool( uint _uToken ) const
{
	const char* psz = GetTokenStr( _uToken );
	bool bVal = IsEqualStringNoCase(psz, "YES") || IsEqualStringNoCase(psz, "TRUE");
		
	return bVal;
}

	 

//////////////////////////////////////////////////////////////////////////
// returns atof of a token

float CTokenizer::GetTokenValueFloat( uint _uToken ) const
{
	const char* psz = GetTokenStr( _uToken );
	float fVal = 0;
		
	if (psz)
		fVal = float(atof( psz ));
		
	return fVal;
}
