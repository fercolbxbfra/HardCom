//----------------------------------------------------------------------------
// basic file management. It uses transparently (or sort of) files inside a  PACK or normal files
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "File.h"
#include "MemFile.h"
#include "Languages.h"
#include "Setup.h"
#include "Globals.h"

#include <stdlib.h>
#include <direct.h>


//////////////////////////////////////////////////////////////////////////

CFile::CFile()
{
	m_pszFileName       = NULL;
	m_bHadError         = false;
	m_bLog              = true;
	m_pFile             = NULL;
	m_pPackFile         = NULL;
	m_bPackFile         = true;   // by default all are. but then the hard truth arrives
	m_bLanguageVersions = false;
	m_bLookInAndOutPack = false;
}


//////////////////////////////////////////////////////////////////////////

CFile::~CFile()
{
	End();
	if (m_pPackFile)
		g_pFilePack->CloseFile( m_pPackFile );
}


//////////////////////////////////////////////////////////////////////////
/// this only need to be used for objects that cant be destroyed, like global ones

void CFile::End()
{
	if (m_pszFileName)
		SAFE_DELETE_ARRAY( m_pszFileName );
	if (m_pFile)
		fclose( (FILE*)m_pFile );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Open( const char* _pszFileName )
{
	ERetVal eRetVal = RET_OK;
		
	ASSERT( _pszFileName );

	if (_pszFileName==NULL )
	{
		eRetVal = RET_ERR;
		LOG(("ERR: NULL filename\n"));
	}
		
		
	if (eRetVal==RET_OK)
	{
		SAFE_DELETE_ARRAY( m_pszFileName );
						
		if (m_bLanguageVersions)
			m_pszFileName = BuildLanguageFileName( _pszFileName );
		else
			m_pszFileName = ALLOC_COPY_STRING( _pszFileName );
				 
		eRetVal = Open_LowLvl( m_pszFileName );
		if (eRetVal!=RET_OK)
		{
			if (m_bLog)
				LOG(("ERR: cant open the file. Maybe it does not exist.: '%s'", m_pszFileName));
		}
	}
		
	UpdateError( eRetVal );
		
	return eRetVal;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Open( const char* _pszDir, const char* _pszFileName )
{
	MAKE_FILENAME( _pszDir, _pszFileName );
	return Open( szFullFileName );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Open( const char* _pszDir, const char* _pszFileName, const char* _pszExt )
{
	MAKE_FILENAME_EXT( _pszDir, _pszFileName, _pszExt );
	return Open( szFullFileName );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Open_LowLvl( const char* _pszFile )
{
	ERetVal eRetVal = RET_OK;
	bool bReadFromPack = (g_pFilePack && g_pFilePack->IsUsingPack() && m_bPackFile);
		
	if (bReadFromPack)
	{
		bool bShowError = !m_bLookInAndOutPack;
		m_pPackFile = g_pFilePack->OpenFile( _pszFile, bShowError );
		if (!m_pPackFile && !m_bLookInAndOutPack)
			eRetVal = RET_ERR;
	}
		
	if (!bReadFromPack || (m_pPackFile==NULL && m_bLookInAndOutPack))
	{
		m_pFile = fopen( _pszFile, "rb" );
		m_bPackFile = false;
		if (!m_pFile)
			eRetVal = RET_ERR;
	}
		
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////
// if the file already exists, it is cleared

ERetVal CFile::OpenWrite( const char* _pszFileName )
{
	ERetVal eRetVal = RET_OK;
		
	ASSERT( _pszFileName );

	if (_pszFileName==NULL )
	{
		eRetVal = RET_ERR;
		LOG(("ERR: Nombre de fichero NULL en OpenWrite"));
	}
		
	if (eRetVal==RET_OK)
	{
		SAFE_DELETE_ARRAY( m_pszFileName );
		m_pszFileName     = ALLOC_COPY_STRING( _pszFileName );
				 
		FILE* fp = fopen( m_pszFileName, "wb" );
				
		if (!fp)  // if there is an error, assumes it is because the directory is not created, and so it tries to create all the directory chain
		{
			char szDir[ MAX_FILENAME_SIZE ];
			COPY_STRING( szDir, m_pszFileName );        
			char* psz = szDir;
			char* pszSlash = NULL;
			do
			{
				char* pszSlash = strchr( psz, '/' );
				if (pszSlash)
				{
					*pszSlash = 0;
					_mkdir( szDir );
					*pszSlash = '/';
					psz = pszSlash + 1;
				}
			} while (pszSlash!=0);
						
			fp = fopen( m_pszFileName, "wb" );  // then tries to create the file again
		}
				
		if (!fp)  // if still cant, then error
		{
			eRetVal = RET_ERR;
			if (m_bLog)
				LOG(("ERR: when trying to open the file (does not exist or cant be read): '%s'", m_pszFileName));
		}
						
		m_pFile = fp;
	}
		
	UpdateError( eRetVal );
	return eRetVal;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::OpenWrite( const char* _pszDir, const char* _pszFileName )
{
	MAKE_FILENAME( _pszDir, _pszFileName );
	return OpenWrite( szFullFileName );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::OpenWrite( const char* _pszDir, const char* _pszFileName, const char* _pszExt )
{
	MAKE_FILENAME_EXT( _pszDir, _pszFileName, _pszExt );
	return OpenWrite( szFullFileName );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read ( void* _pBuffer, int _iBytes )
{
	ERetVal eRetVal = RET_OK;
		
	if (!m_pFile && !m_pPackFile)
	{
		LOG(("ERR: tried to read a file that is not open. File: '%s'", m_pszFileName));
		eRetVal = RET_ERR;
	}
		
	//....not in FILEPACK
	if (m_pFile)
	{
		int bytesRead = fread( _pBuffer, 1, _iBytes, (FILE*)m_pFile );
		if (bytesRead<_iBytes)
		{
			if (m_bLog)
				LOG(("ERR: read less bytes(%d) than expected(%d). File: '%s'", bytesRead, _iBytes, m_pszFileName));
			eRetVal = RET_ERR;
		}
	}
		
	//...in FILEPACK...
	if (m_pPackFile)
	{
		eRetVal = g_pFilePack->ReadFile( _pBuffer, _iBytes, m_pPackFile );
	}
		
	UpdateError( eRetVal );
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Write ( void* _pBuffer, int _iBytes )
{
	ERetVal eRetVal = RET_OK;
		
	if (!m_pFile)
	{
		LOG(("ERR: tried to write into a file that is not open. File: '%s'", m_pszFileName));
		eRetVal = RET_ERR;
	}
		
	if (m_pFile)
	{
		int bytesWriten = fwrite( _pBuffer, 1, _iBytes, (FILE*)m_pFile );
		if (bytesWriten<_iBytes)
		{
			LOG(("ERR: writen less bytes(%d) than expected(%d). File: '%s'", bytesWriten, _iBytes, m_pszFileName));
			eRetVal = RET_ERR;
		}
	}
		
	UpdateError( eRetVal );
	return eRetVal;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Write( const char* _pszBuffer )
{
	ERetVal eRetVal = RET_ERR;
		
	if (_pszBuffer)
		eRetVal = Write( (void*)_pszBuffer, strlen(_pszBuffer ));    
		
	UpdateError( eRetVal );
	return eRetVal;    
}    


//////////////////////////////////////////////////////////////////////////
// string + adds a crlf at the end
//----------------------------------------------------------------------

ERetVal CFile::WriteCRLF( const char* _pszBuffer )
{
	ERetVal eRetVal1 = Write( _pszBuffer );
	ERetVal eRetVal2 = WriteCRLF();
		
	ERetVal eRetVal = eRetVal1==RET_OK && eRetVal2==RET_OK ? RET_OK : RET_ERR;
	return eRetVal;    
}    


//////////////////////////////////////////////////////////////////////////
/// write with the typical printf format

ERetVal CFile::Writef(  const char* _pszFmt, ...  )
{
	MACRO_PRINTF( szBuffer, 10000 )

	return Write( szBuffer );    
}



//////////////////////////////////////////////////////////////////////////

void CFile::Close()
{
	if (m_pFile)
	{
		fclose( (FILE*)m_pFile );
		m_pFile = NULL;
	}
		
	if (m_pPackFile)
	{
		g_pFilePack->CloseFile( m_pPackFile );
		m_pPackFile = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
// WARNING, this function leaves the file pointer at the start

int CFile::GetSize()
{
	int iTam = 0;
		
	if (m_pFile)
	{
		fseek( (FILE*)m_pFile, 0, SEEK_END );
		iTam = ftell( (FILE*)m_pFile );
		fseek( (FILE*)m_pFile, 0, SEEK_SET );
	}
		
	if (m_pPackFile)
		iTam = m_pPackFile->m_iSize;
		
	return iTam;
}



//////////////////////////////////////////////////////////////////////////

bool CFile::Exists( const char* _pszFileName, bool _bInPack )
{
	bool bExists = false;
		
	if (g_pFilePack && g_pFilePack->IsUsingPack() && _bInPack )
			bExists = g_pFilePack->ExistsFile( _pszFileName );
	else
	{
		FILE* fp = fopen( _pszFileName, "rb" );
		if (fp)
		{
			bExists = true;
			fclose( fp );
		}
	}
		
	return bExists;
}


//////////////////////////////////////////////////////////////////////////

bool CFile::Exists( const char* _pszDir, const char* _pszFileName, bool _bInPack )
{
	bool bExists = false;
		
	char szFileName[ MAX_FILENAME_SIZE ];
	CopyString( szFileName, sizeof(szFileName), _pszDir );
	CatString( szFileName, sizeof(szFileName), _pszFileName );
		
	return Exists( szFileName, _bInPack );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_Int( int* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(int) );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_Uint( uint* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(uint) );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_Short( short* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(short) );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_UShort( ushort* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(ushort) );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_Float( float* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(float) );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_Bool( bool* _pVal )
{
	ASSERT( _pVal );
		
	return Read( _pVal, sizeof(bool) );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFile::Read_NameID( CNameID* _pName )
{
	ASSERT( _pName );
		
	char szBuf[ CNameID::NAMEID_SIZE ];
		
	ERetVal eRetVal = Read( szBuf, sizeof(szBuf) );
	_pName->Set( szBuf );
		
	return eRetVal;
}


//////////////////////////////////////////////////////////////////////////
// sets file pointer to the start of the file

void CFile::GoStart()
{
	if (m_pFile)
		fseek( (FILE*)m_pFile, 0, SEEK_SET );
				
	if (m_pPackFile)
		g_pFilePack->GoStartFile( m_pPackFile );
}



//////////////////////////////////////////////////////////////////////////

void CFile::AdvanceFilePos( uint _uAdvance )
{
	if (m_pFile)
		fseek( (FILE*)m_pFile, _uAdvance, SEEK_CUR );
				
	if (m_pPackFile)
		g_pFilePack->AdvanceFilePos( m_pPackFile, _uAdvance );     
}



//////////////////////////////////////////////////////////////////////////

void CFile::UpdateError( ERetVal eRetVal )
{
	if (!m_bHadError)
		m_bHadError = ( eRetVal != RET_OK );
}


//////////////////////////////////////////////////////////////////////////
// forces the file to be read from outside the FILEPACK, even if that is enabled
// ONLY can be used before opening the file

void CFile::SetNoPack()
{
	ASSERT( !IsFileOpen() );
	ASSERT( !m_bLookInAndOutPack );
	m_bPackFile = false;
}


//////////////////////////////////////////////////////////////////////////
// this forces the file to be looked for first inside the pack, then, if not found, is looked for outside.
// ONLY can be used before opening the file

void CFile::SetLookInAndOutPack()
{
	ASSERT( !IsFileOpen() );
	ASSERT( m_bPackFile );
	m_bLookInAndOutPack = true;
}



//----------------------------------------------------------------------
// reserves a memory block and reads the whole file into it.
// the pointer returned has to be freed by the user
//----------------------------------------------------------------------

byte* CFile::ReadIntoMem( const char* _pszFileName, int* _piSize )
{
	byte* pBuf = NULL;
		
	ERetVal eRetVal = Open( _pszFileName );
	if (eRetVal==RET_OK)
	{
		int iSize = GetSize();
		if (_piSize)
			*_piSize = iSize;
		pBuf = NEW byte[iSize];
		Read( pBuf, iSize );
		Close();
	}    

	return pBuf;
}


//////////////////////////////////////////////////////////////////////////

void CFile::Seek( uint _uPos )
{
	if (m_pFile)
		fseek( (FILE*)m_pFile, _uPos, SEEK_SET );
				
	if (m_pPackFile)
		g_pFilePack->SeekFile( m_pPackFile, _uPos );
}


//----------------------------------------------------------------------

uint CFile::GetFilePos()
{
	ASSERT( m_pFile );  // only works for no pack files
		
	if (m_pFile)
		return ftell( (FILE*)m_pFile );
	else
		return 0;
}


//////////////////////////////////////////////////////////////////////////
// from a filename, inserts a language suffix. the pointer that returns is allocated, need to be freed by the user

char* CFile::BuildLanguageFileName( const char* _pszFile )
{
	int iNumChars = strlen(_pszFile) + strlen( GetLangFileSuffix()) + 1; // +1 because the 0 at the end
	char* pszFull = NEW char [ iNumChars ];

	int is = 0;
	int id = 0;
	while (_pszFile[is]!=0)
	{
		if (_pszFile[is]=='.')
		{
			pszFull[id] = 0;
			CatString( pszFull, iNumChars, GetLangFileSuffix());
			CatString( pszFull, iNumChars, _pszFile + is );
			break;
		}
		pszFull[id] = _pszFile[is];
		id++;
		is++;
	}

	return pszFull;        
}


//----------------------------------------------------------------------
// looks for all the files that match the wildcar, inside and outside the pack

void FindFilesInAndOutPack( const char* _pszFind, vector<char*>* _paList )
{
	//...first find inside the pack...
	g_pFilePack->FindFiles( _pszFind, _paList );

	if (g_pFilePack->IsUsingPack())
	{
		// then manually finds outside the pack.....
		//...start the search
		WIN32_FIND_DATA FindFileData;
		HANDLE hHandle = FindFirstFile( _pszFind, &FindFileData );
				
		bool bContinue = hHandle!=INVALID_HANDLE_VALUE;
				
		//...look for all the files in the directory and adds them to the vector
		while (bContinue)
		{
			if ((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0)
			{
				char* pszFileName = ALLOC_COPY_STRING( FindFileData.cFileName );
				_paList->push_back( pszFileName );
			}
			BOOL bValid = FindNextFile( hHandle, &FindFileData );
			bContinue = bValid!=0;
		};
				
		if (hHandle!=INVALID_HANDLE_VALUE)  
			FindClose( hHandle ); 
	}
}
