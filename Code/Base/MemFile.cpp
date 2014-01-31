//----------------------------------------------------------------------------
// manages a memory file, which is a buffer in memory where is possible to read and write sequentially in the same way we do with a normal file
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "MemFile.h"
#include "File.h"

#define DEFAULT_GROWTH (5*1024)

//////////////////////////////////////////////////////////////////////////

CMemFile::~CMemFile()
{
		End();
}


//////////////////////////////////////////////////////////////////////////
// used when we want to reuse it. We call End, then Init again.

void CMemFile::End()
{
	if (m_bOk)
	{
		SAFE_DELETE_ARRAY( m_pData );    
	}
}


//////////////////////////////////////////////////////////////////////////

void CMemFile::InitVars()
{
	m_pData         = NULL;
	m_iCursorPos    = 0;
	m_iBufferSize   = 0;
	m_iGrowth       = DEFAULT_GROWTH;
	m_iDataUsed     = 0;
	m_bHadError     = false;
}



//////////////////////////////////////////////////////////////////////////
// to assign a memfile to another one, without memory leaks
// WARNING: the size of the new memfile buffer is just the size of the USED part of the old one. So it will growth right away if anything is added to it.

void CMemFile::operator=( const CMemFile& _MemFile )
{
	End();
	InitVars();
	m_iCursorPos    = _MemFile.m_iCursorPos;
	m_iBufferSize   = _MemFile.m_iBufferSize;
	m_iGrowth       = _MemFile.m_iGrowth;
	m_iDataUsed     = _MemFile.m_iDataUsed;
	m_pData         = NEW byte[ m_iDataUsed ];
	memcpy( m_pData, _MemFile.m_pData, m_iDataUsed );
	m_bOk           = true;
}


//////////////////////////////////////////////////////////////////////////

void CMemFile::Init( int _iInitSize )
{
	ASSERT( _iInitSize>0 );
	InitVars();
		
	m_pData         = NEW byte[ _iInitSize ];
	m_iBufferSize   = _iInitSize;
	m_bOk           = true;
}



//////////////////////////////////////////////////////////////////////////

void CMemFile::InitRaw( int _iSize, byte* _pData )
{
	InitVars();
	m_pData         = NEW byte[_iSize];
	memcpy( m_pData, _pData, _iSize );
	m_bOk           = true;
	m_iBufferSize   = _iSize;
	m_iDataUsed     = m_iBufferSize;
}


//////////////////////////////////////////////////////////////////////////

void CMemFile::InitFromFile( CFile* _pFile )
{
	InitVars();
	m_iBufferSize   = _pFile->GetSize();
	m_iDataUsed     = m_iBufferSize;
	m_pData         = NEW byte[ m_iBufferSize ];
	_pFile->Read( m_pData, m_iBufferSize );
	m_bOk           = true;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CMemFile::Read ( void* _pBuffer, int _iBytes )
{
	ERetVal eRetVal = RET_OK;
		
	if (m_iCursorPos + _iBytes >m_iDataUsed)
	{
		LOG(("ERR: tried to read past the end of the file" ));
		_iBytes = m_iDataUsed - m_iCursorPos;
		m_bHadError = true;
		eRetVal = RET_ERR;
	}
		
	memcpy( _pBuffer, m_pData + m_iCursorPos, _iBytes );
	m_iCursorPos += _iBytes;
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////

void CMemFile::Write ( void* _pBuffer, int _iBytes )
{
	ERetVal eRetVal = RET_OK;
		
	//...grow if needed
	if (m_iCursorPos + _iBytes > m_iBufferSize )
	{
		int iIncSize = ( m_iCursorPos + _iBytes ) - m_iBufferSize;
		iIncSize = ( ( iIncSize / m_iGrowth ) + 1 ) * m_iGrowth;
		int iNewSize = m_iBufferSize + iIncSize;
		byte* pNewBuffer = NEW byte[ iNewSize ];
		memcpy( pNewBuffer, m_pData, m_iBufferSize );
		SAFE_DELETE_ARRAY( m_pData );
		m_pData = pNewBuffer;
		m_iBufferSize = iNewSize;
	}
		 
	memcpy( m_pData + m_iCursorPos, _pBuffer, _iBytes );
	m_iCursorPos += _iBytes;   
	if (m_iCursorPos>m_iDataUsed)
		m_iDataUsed = m_iCursorPos;
}


//////////////////////////////////////////////////////////////////////////

void CMemFile::Write_Str( const char* _pszBuffer )
{
	if (_pszBuffer)
		Write( (void*)_pszBuffer, strlen(_pszBuffer ));    
}    


//////////////////////////////////////////////////////////////////////////

void CMemFile::Write_Int( int _iVal )
{
	Write( &_iVal, sizeof(int) );
}    

//////////////////////////////////////////////////////////////////////////

ERetVal CMemFile::Read_Int( int* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(int) );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CMemFile::Read_NameID( CNameID* _pName )
{
	ASSERT( _pName );
		
	char szBuf[ CNameID::NAMEID_SIZE ];
		
	ERetVal eRetVal = Read( szBuf, sizeof(szBuf) );
	_pName->Set( szBuf );
		
	return eRetVal;
}


