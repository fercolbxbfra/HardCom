//----------------------------------------------------------------------------
// the huge FILEPACK
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "FilePack.h"

#define SLASH               '/'


bool CFilePack::m_bFilePackForced = false;


//////////////////////////////////////////////////////////////////////////

CFilePack::~CFilePack()
{
	SAFE_DELETE_ARRAY( m_pBuffNames );
	SAFE_DELETE_ARRAY( m_paDirs );
	SAFE_DELETE_ARRAY( m_paFiles );
		
	if (m_pFile)
			fclose( (FILE*)m_pFile );
}


//////////////////////////////////////////////////////////////////////////

CFilePack::CFilePack()
{
	m_pFile                 = NULL;
	m_pBuffNames            = NULL;
	m_bUsingPack            = false;
	m_paDirs                = NULL;
	m_paFiles               = NULL;
	m_uStartFileData        = 0;
	m_pCurrFile             = NULL;
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFilePack::Init( const char* _pszPackFileName )
{
	ERetVal eRetVal = RET_OK;
		
	FILE* pf = fopen( _pszPackFileName, "rb" );
	if (pf)
	{
		m_pFile         = pf;
		m_bUsingPack    = true;
		eRetVal         = ReadPackFileInfo();
	}
		
	if (!m_bUsingPack && m_bFilePackForced)
	{
		ASSERTM( false, ("ERR: Could not open the packfile: '%s'", _pszPackFileName));
		eRetVal = RET_ERR;
	}
		
	COPY_STRING( m_szPackFileName, _pszPackFileName );
		
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFilePack::Init( const char* _pszDir, const char* _pszPackFileName )
{
	char szFullFileName[ MAX_FILENAME_SIZE ];
		
	COPY_STRING( szFullFileName, _pszDir );
	CAT_STRING( szFullFileName, _pszPackFileName );
		
	return Init( szFullFileName );
}



//////////////////////////////////////////////////////////////////////////

ERetVal CFilePack::ReadPackFileInfo()
{
	m_uStartFileData = 0;
		
	//....header...
	ERetVal eRetVal = RET_OK;
	int iBytesRead = fread( &m_Header, 1, sizeof(m_Header), (FILE*)m_pFile );
	m_uStartFileData += iBytesRead;
		
	if (iBytesRead!=sizeof(m_Header))
		eRetVal = RET_ERR;
				
	if (m_Header.m_ID!=ID_PACKFILE)
	{
		ASSERTM(false, ("ERR: Packfile. Wrong ID, probably is not a packfile."));
		eRetVal = RET_ERR;
	}
				
	if (m_Header.m_iVersion!=PACK_VERSION)
	{
		ASSERTM(false, ("ERR: Packfile. Incorrect version (%d). Should be: %d", m_Header.m_iVersion, PACK_VERSION ));
		eRetVal = RET_ERR;
	}
				
	//...name buffer.......
	if (eRetVal==RET_OK)
	{
		m_pBuffNames = NEW char[m_Header.m_iNamesSize];
		iBytesRead = fread( m_pBuffNames, 1, m_Header.m_iNamesSize, (FILE*)m_pFile );
		m_uStartFileData += iBytesRead;
		if (iBytesRead!=m_Header.m_iNamesSize)
				eRetVal = RET_ERR;
	}
		
		
	//....directories....
	if (eRetVal==RET_OK)
	{
		m_paDirs = NEW TDir[m_Header.m_iNumDirs];
		TPackRawDir* paRawDirs = NEW TPackRawDir[ m_Header.m_iNumDirs ];
				
		int iBytesToRead = m_Header.m_iNumDirs*sizeof(TPackRawDir);
		iBytesRead = fread( paRawDirs, 1, iBytesToRead, (FILE*)m_pFile );
		m_uStartFileData += iBytesRead;
		if (iBytesRead!=iBytesToRead || iBytesRead==0)
			eRetVal = RET_ERR;
		else
		{
			for (int d=0; d<m_Header.m_iNumDirs; d++)
			{
				m_paDirs[d].m_iFirstFile    = paRawDirs[d].m_iFirstFile;
				m_paDirs[d].m_iFirstSubDir  = paRawDirs[d].m_iFirstSubDir;
				m_paDirs[d].m_iNumFiles     = paRawDirs[d].m_iNumFiles;
				m_paDirs[d].m_iNumSubDirs   = paRawDirs[d].m_iNumSubDirs;
				m_paDirs[d].m_pszName = m_pBuffNames + paRawDirs[d].m_iFileName;
				m_paDirs[d].m_iParentDir    = paRawDirs[d].m_iParentDir;
				m_paDirs[d].m_iIndex        = d;
			}
		}
		SAFE_DELETE_ARRAY( paRawDirs );
	}
		


	//....files info....
	if (eRetVal==RET_OK)
	{
		m_paFiles = NEW TFile[m_Header.m_iNumFiles];
		TPackRawFile* paRawFiles = NEW TPackRawFile[ m_Header.m_iNumFiles ];
				
		int iBytesToRead = m_Header.m_iNumFiles*sizeof(TPackRawFile);
		iBytesRead = fread( paRawFiles, 1, iBytesToRead, (FILE*)m_pFile );
		m_uStartFileData += iBytesRead;
		if (iBytesRead!=iBytesToRead || iBytesRead==0)
			eRetVal = RET_ERR;
		else
		{
			for (int d=0; d<m_Header.m_iNumFiles; d++)
			{
				m_paFiles[d].m_iSize    = paRawFiles[d].m_iSize;
				m_paFiles[d].m_uStart   = paRawFiles[d].m_uStart;
				m_paFiles[d].m_pszName  = m_pBuffNames + paRawFiles[d].m_iFileName;
				m_paFiles[d].m_bOpened  = false;
				m_paFiles[d].m_iCursor  = 0;
				m_paFiles[d].m_iDir     = paRawFiles[d].m_iDir;
			}
		}
		SAFE_DELETE_ARRAY( paRawFiles );
	}
		
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////

void CFilePack::CloseFile( TFile* _pFile )
{
	ASSERT( _pFile->m_bOpened );
		
	_pFile->m_bOpened = false;
	m_pCurrFile = NULL;
}


//////////////////////////////////////////////////////////////////////////

void CFilePack::GoStartFile( TFile* _pFile )
{
	ASSERT( _pFile->m_bOpened );
		
	_pFile->m_iCursor = 0;
	if (m_pCurrFile!=_pFile)
		m_pCurrFile = _pFile;
	fseek( (FILE*)m_pFile, m_uStartFileData + _pFile->m_uStart+_pFile->m_iCursor, SEEK_SET );
}


//////////////////////////////////////////////////////////////////////////

ERetVal CFilePack::ReadFile( void* _pBuffer, int _iBytes, TFile* _pFile )
{
	ERetVal eRetVal = RET_OK;
	ASSERT( _pFile->m_bOpened );
		
	ASSERT( _pFile->m_iCursor + _iBytes <= _pFile->m_iSize );
		
	//...re-seek if needed
	if (m_pCurrFile!=_pFile)
	{
		m_pCurrFile = _pFile;
		int iSuccess = fseek( (FILE*)m_pFile, m_uStartFileData + _pFile->m_uStart+_pFile->m_iCursor, SEEK_SET );
		if (iSuccess!=0)
			eRetVal = RET_ERR;
	}
		
	if (eRetVal==RET_OK)
	{
		fread( _pBuffer, _iBytes, 1, (FILE*)m_pFile );
		_pFile->m_iCursor += _iBytes;
	}
		
	return eRetVal;
}



//////////////////////////////////////////////////////////////////////////
// only for internal use 

void CFilePack::ReadFileDirect( void* _pBuffer, const TFile* _pFile )
{
	ASSERT( !m_pCurrFile );
	fseek( (FILE*)m_pFile, m_uStartFileData + _pFile->m_uStart, SEEK_SET );
	fread( _pBuffer, _pFile->m_iSize, 1, (FILE*)m_pFile );
}



//////////////////////////////////////////////////////////////////////////

CFilePack::TFile* CFilePack::OpenFile( const char* _pszFileName, bool _bShowError )
{
	TFile* pFile = FindFile( _pszFileName, _bShowError );
		
	if (pFile)
	{
		ASSERT( !pFile->m_bOpened );
		pFile->m_bOpened = true;
		pFile->m_iCursor = 0;
	}

	return pFile;
}


//////////////////////////////////////////////////////////////////////////
// finds the directory of a file

CFilePack::TDir* CFilePack::FindDirOfFile( const char* _pszFileName, bool _bShowError )
{
	//...skips initial dir
	static int iL = strlen( DIR_DATA );
	ASSERT( int(strlen(_pszFileName))>=iL );
	char szFileName[ MAX_FILENAME_SIZE ];
	{  //..to upper case
		int i=iL;
		for (; _pszFileName[i]!=0; i++)
				szFileName[i-iL] = toupper( _pszFileName[i] );
		szFileName[i-iL] = 0;
	}
				
		
	//...parse each directory and finds the file in it
	const char* pszC        = szFileName;
	TDir*       pDir        = m_paDirs;   // dir root (DATA)
	const char* pszSlash    = strchr( pszC, SLASH );
		
	ERetVal eRetVal = RET_OK;
		
	//...if there is still any slash keeps looking in subdirectories
	while (pszSlash && eRetVal==RET_OK) 
	{
		TDir* pSubDir = FindSubDir( pDir, pszC );
				
		if (pSubDir)
		{
			pDir = pSubDir;
			pszC = pszSlash + 1;
			pszSlash = strchr( pszC, SLASH );
		}
		else
		{
			ASSERTM( !_bShowError, ("ERROR, could not find the folder: '%s' in the folder '%s'", pszC, pDir->m_pszName ));
			eRetVal = RET_ERR;
		}
	}
		
	if (eRetVal!=RET_OK)
		pDir = NULL;
				
	return pDir;
}



//////////////////////////////////////////////////////////////////////////
// looks for a file in the whole pack
//----------------------------------------------------------------------

CFilePack::TFile* CFilePack::FindFile( const char* _pszFileName, bool _bShowError )
{
	TFile* pFile = NULL;
		
	TDir* pDir = FindDirOfFile( _pszFileName, _bShowError );
				
	if (pDir)
	{
		char szFile[ MAX_FILENAME_SIZE ];
		RemoveDir( szFile, sizeof(szFile), _pszFileName );
		pFile = FindFileInDir( pDir, szFile );
		if (!pFile)
		{
			ASSERTM( !_bShowError, ("ERROR, could not find the file: '%s' in the folder: '%s'", _pszFileName, pDir->m_pszName ));
		}
	}

	return pFile;
}



//////////////////////////////////////////////////////////////////////////
// looks for a subdirectory inside a directory
// IMPORTANT the subdirectory string finishes in '/', not in 0
//----------------------------------------------------------------------

CFilePack::TDir* CFilePack::FindSubDir( TDir* _pDir, const char* _pszSubDir )
{
	TDir* pDirFound = NULL;
		
	const char* pszC = _pszSubDir;
		
	for (int d=0; d<_pDir->m_iNumSubDirs && !pDirFound; d++)
	{
		TDir* pSubDir = m_paDirs + _pDir->m_iFirstSubDir + d;
		bool bDiferent = false;
				
		int c = 0;
		while (!bDiferent && pszC[c]!=SLASH)    //..checks directory name
		{
			if (pszC[c]!=pSubDir->m_pszName[c])
				bDiferent = true;
			c++;
		};
		if (!bDiferent)
			bDiferent = ( pszC[c]!=SLASH || pSubDir->m_pszName[c]!=0 );   //..tests that both names finish at the same size
						
		if (!bDiferent)
			pDirFound = pSubDir;
	}
		
	return pDirFound;
}


//////////////////////////////////////////////////////////////////////////
// looks for a file inside a directory

CFilePack::TFile* CFilePack::FindFileInDir( TDir* _pDir, const char* _pszFile )
{
	TFile* pFileFound = NULL;
		
	for (int f=0; f<_pDir->m_iNumFiles && !pFileFound; f++)
	{
		TFile* pFile = m_paFiles + _pDir->m_iFirstFile + f;
		if (IsEqualStringNoCase( _pszFile, pFile->m_pszName ))
			pFileFound = pFile;
	}
	 
	return pFileFound;
}


//////////////////////////////////////////////////////////////////////////

void CFilePack::SeekFile( TFile* _pFile, uint _uPos )
{
	ASSERT( _pFile->m_bOpened );
		
	_pFile->m_iCursor = _uPos;
	if (m_pCurrFile!=_pFile)
		m_pCurrFile = _pFile;
	fseek( (FILE*)m_pFile, m_uStartFileData + _pFile->m_uStart+_pFile->m_iCursor, SEEK_SET );
}


//////////////////////////////////////////////////////////////////////////
// moves the file pointer the given number of characters ahead

void CFilePack::AdvanceFilePos( TFile* _pFile, uint _uAdvance )
{
	ASSERT( _pFile->m_bOpened );
		
	_pFile->m_iCursor += _uAdvance;
	if (m_pCurrFile!=_pFile)
		m_pCurrFile = _pFile;
	fseek( (FILE*)m_pFile, m_uStartFileData + _pFile->m_uStart+_pFile->m_iCursor, SEEK_SET );
}



//////////////////////////////////////////////////////////////////////////
// fills a vector with the files that match a wilcard value
// TODO: when looking inside the pack, the wildcard search has very limited versatility. It only works for 
// for searchs of the form [directory]*[end part]. Examples: "DATA/SCRIPTS/*.DTB", "DATA/*CACA"

void CFilePack::FindFiles( const char* _pszFind, vector<char*>* _paList )
{
	ASSERT( _paList->size()==0 );
		
	//.....without pack
	if (!m_bUsingPack)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hHandle = FindFirstFile( _pszFind, &FindFileData );

		bool bContinue = (hHandle != INVALID_HANDLE_VALUE);
		while ( bContinue )
		{
			char* psz = ALLOC_COPY_STRING( FindFileData.cFileName );
			_paList->push_back( psz );
			BOOL bValid = FindNextFile( hHandle, &FindFileData );
			bContinue = bValid != 0;
		}
		FindClose( hHandle );
	}
	else  //........with pack...
	{
		TDir* pDir = FindDirOfFile( _pszFind, false );
				
		if (pDir)
		{
			char szRoot[ MAX_FILENAME_SIZE ];
			RemoveDir( szRoot, sizeof(szRoot), _pszFind );
			COPY_STRING( szRoot, _pszFind );
			char* pCut = strchr( szRoot, '*' );
			if (pCut)
				pCut++;
								
			int iNumChars = strlen( pCut );
			for (int f=0; f<pDir->m_iNumFiles; f++)
			{
				TFile* pFile = m_paFiles + pDir->m_iFirstFile + f;
				int iLen = strlen(pFile->m_pszName);
				if (iLen>=iNumChars)
				{
					const char* pszFile = pFile->m_pszName + ( iLen - iNumChars );
					if (IsEqualStringNoCaseNumChars( pCut, pszFile, iNumChars ))
					{
						char* psz = ALLOC_COPY_STRING( pFile->m_pszName );
						_paList->push_back( psz );
					}
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
// fills _pszDest with the file name in _pszOri, but without any path

void CFilePack::RemoveDir( char* _pszDest, int _iSize, const char* _pszOri )
{
	int iLengthOri = strlen( _pszOri );
	int iLengthDes = 0;
		
	int i = iLengthOri - 1;
		
	while ( i>=0 && _pszOri[i]!='/' && _pszOri[i]!='\\' )
	{
		i--;
	}
		
	i++;
	CopyString( _pszDest, _iSize, _pszOri + i );
}



//////////////////////////////////////////////////////////////////////////
// compare a file from other pack with the one in this pack

bool CFilePack::FilesAreEqual( const char* _pszFullFileName, CFilePack* pOtherPack, const TFile& _File )
{
	TFile* pFile = FindFile( _pszFullFileName );
	ASSERT( pFile );
		
	bool bEqual = false;
		
	if (pFile->m_iSize==_File.m_iSize)
	{
		byte* pBuf0 = new byte[ pFile->m_iSize ];
		ReadFileDirect( pBuf0, pFile );
				
		byte* pBuf1 = new byte[ _File.m_iSize ];
		pOtherPack->ReadFileDirect( pBuf1, &_File );
				
		bEqual = (memcmp( pBuf0, pBuf1, _File.m_iSize )==0);
				
		SAFE_DELETE_ARRAY( pBuf0 );
		SAFE_DELETE_ARRAY( pBuf1 );
	}
		
	return bEqual;
}


//////////////////////////////////////////////////////////////////////////
// builds the full file name from the root directory of the pack (but not before that)

void CFilePack::BuildFileNameFromRoot( char* _pszBuf, int _iBufSize, const TFile& _File  )
{
	vector<int> aDirs;
		
	int iDir = _File.m_iDir;
	TDir* pDir = m_paDirs + iDir;

	do    
	{
		pDir = m_paDirs + iDir;
		aDirs.push_back( iDir );
		iDir = pDir->m_iParentDir;
	}
	while (iDir!=NONE);

	_pszBuf[0] = 0;
		
	for (uint i=0; i<aDirs.size(); i++)
	{
		int iInd = aDirs.size() - ( i + 1 );
		int iDir = aDirs[iInd];
		CatString( _pszBuf, _iBufSize, m_paDirs[iDir].m_pszName );
		CatString( _pszBuf, _iBufSize, "/" );
	}

	CatString( _pszBuf, _iBufSize, _File.m_pszName );
}            
