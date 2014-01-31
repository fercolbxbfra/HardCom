//----------------------------------------------------------------------------
// the huge FILEPACK
//----------------------------------------------------------------------------

#pragma once

#define PACK_VERSION        1
#define ID_PACKFILE         'WLPK'

class CFilePack
{
	public:

		struct TFile
		{
			const char* m_pszName;   //....points into the array of filenames. WARNING, inside the file this is an index to the first character inside the array of names
			uint        m_uStart;        //..start index inside the megafile
			int         m_iSize;         
			int         m_iCursor;      //...current read position in the file
			bool        m_bOpened;      //...to prevent the file from being opened more than one time at once
			int         m_iDir;
		};

		struct TDir
		{
			const char*     m_pszName;   //....points into the array of filenames. WARNING, inside the file this is an index to the first character inside the array of names
			int             m_iFirstSubDir; 
			int             m_iNumSubDirs;
			int             m_iFirstFile;
			int             m_iNumFiles;
			int             m_iParentDir;
			int             m_iIndex;  // index inside the dir array
		};
				
		//...........header del file empaketado....
		struct THeader
		{
			uint        m_ID;
			int         m_iVersion;
			int         m_iNamesSize;  //..total size of the array of names
			int         m_iNumDirs;
			int         m_iNumFiles;
		};

		//...those 2 are the structs as they are in the file. 
		struct TPackRawFile
		{
			int     m_iFileName;   //....index inside the array of names
			uint    m_uStart;        //..start index inside the megafile
			int     m_iSize;         
			int     m_iDir;
		};

		struct TPackRawDir
		{
			int             m_iFileName;   //....index inside the array of names
			int             m_iFirstSubDir; 
			int             m_iNumSubDirs;
			int             m_iFirstFile;
			int             m_iNumFiles;
			int             m_iParentDir;
		};

	public:
																CFilePack               ();
																~CFilePack               ();
																	 
		ERetVal                     Init                    ( const char* _pszPackFileName );         
		ERetVal                     Init                    ( const char* _pszDir, const char* _pszPackFileName );         
		ERetVal                     InitStud                () { return RET_OK; }
				
		bool                        IsUsingPack             () { return m_bUsingPack; }

		void                        CloseFile               ( TFile* _pFile );
		TFile*                      OpenFile                ( const char* _pszFileName, bool _bShowError = true );
		ERetVal                     ReadFile                ( void* _pBuffer, int _iBytes, TFile* _pFile );
		void                        GoStartFile             ( TFile* _pFile );
		bool                        ExistsFile              ( const char* _pszFileName ) { return FindFile( _pszFileName, false)!=NULL; }
		void                        SeekFile                ( TFile* _pFile, uint _uPos );
		void                        AdvanceFilePos          ( TFile* _pFile, uint _uAdvance );
				
		void                        FindFiles               ( const char* _pszFind, vector<char*>* _paList );
				
		static  void                ForceFilePack           () { m_bFilePackForced = true; }
		void                        BuildFileNameFromRoot   ( char* _pszBuf, int _iBufSize, const TFile& _File );
		const TDir&                 FindDir                 ( const char* _pszDir );
				
				
		//...for direct use, handle with care! dont touch unless you know what you are doing!....
		int                         GetNumDirs              () { return m_Header.m_iNumDirs; }
		int                         GetNumFiles             () { return m_Header.m_iNumFiles; }
		const TDir&                 GetDir                  ( int _iDir ) { return m_paDirs[_iDir]; }
		const TFile&                GetFile                 ( int _iFile ) { return m_paFiles[_iFile]; }
		bool                        FilesAreEqual           ( const char* _pszFullFileName, CFilePack* pOtherPack, const TFile& _File );
		void                        ReadFileDirect          ( void* _pBuffer, const TFile* _pFile );
		TDir*                       FindDirOfFile           ( const char* _pszFileName, bool _bShowError = true );
				

	private:
		
		ERetVal                     ReadPackFileInfo        ();
		TDir*                       FindSubDir              ( TDir* _pDir, const char* _pszSubDir );
		TFile*                      FindFileInDir           ( TDir* _pDir, const char* _pszFile );
		TFile*                      FindFile                ( const char* _pszFileName, bool _bShowError = true );
		void                        RemoveDir               ( char* _pszDest, int _iSize, const char* _pszOri );
				
																					
				
	private:
		
		void*                       m_pFile;   //..is a FILE*
		THeader                     m_Header;
		char*                       m_pBuffNames;   //...all filename and directory names are in this buffer
		TDir*                       m_paDirs;  // the first directory is the DATA directory, always. It is the root. And there are not other roots.
		TFile*                      m_paFiles;
		uint                        m_uStartFileData;   //...position inside the megafile where the data for the files starts
		const TFile*                m_pCurrFile;  //...this points to the file which is being currently read, and his position pointer is at the same position than the actual megafile pointer
																							//. this is needed to know when a read can be done without needing a seek, which is the usual situation.
																							// only when 2 or more files are being read at the same time in sequentially way is when we need to make a seek before each read.
				
		char                        m_szPackFileName[ MAX_FILENAME_SIZE ];
		bool                        m_bUsingPack;
				
		static bool                 m_bFilePackForced;
}; 

void  FindFilesInAndOutPack ( const char* _pszFind, vector<char*>* _paList );
