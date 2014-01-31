//----------------------------------------------------------------------------
// basic file management. It uses transparently (or sort of) files inside a  PACK or normal files
//----------------------------------------------------------------------------

#pragma once

#include "NameID.h"
#include "FilePack.h"

class CFile
{
	public:
																	CFile                   ();
																	~CFile                  ();
				
			void                        End                     ();
			ERetVal                     OpenFileExt             ( const char* _pszFileName );
			ERetVal                     Open                    ( const char* _pszFileName );
			ERetVal                     Open                    ( const char* _pszDir, const char* _pszFileName );
			ERetVal                     Open                    ( const char* _pszDir, const char* _pszFileName, const char* _pszExt );
			ERetVal                     OpenWrite               ( const char* _pszFileName );
			ERetVal                     OpenWrite               ( const char* _pszDir, const char* _pszFileName );
			ERetVal                     OpenWrite               ( const char* _pszDir, const char* _pszFileName, const char* _pszExt );
				
			byte*                       ReadIntoMem             ( const char* _pszFileName, int* _piSize = NULL );
				
			ERetVal                     Read                    ( void* _pBuffer, int _iBytes );
			ERetVal                     Read_Int                ( int* _pVal );
			ERetVal                     Read_Uint               ( uint* _pVal );
			ERetVal                     Read_Short              ( short* _pVal );
			ERetVal                     Read_UShort             ( ushort* _pVal );
			ERetVal                     Read_Float              ( float* _pVal );
			ERetVal                     Read_Bool               ( bool* _pVal );
			ERetVal                     Read_NameID             ( CNameID* _pNameID );
				
			ERetVal                     Write                   ( void* _pBuffer, int _iBytes );
			ERetVal                     Write                   ( const char* _pszBuffer );
			ERetVal                     WriteCRLF               ( const char* _pszBuffer );
			ERetVal                     Writef                  ( const char* _pszFmt, ... );
			void                        Seek                    ( uint _uPos );
			void                        Close                   ();
			ERetVal                     WriteCRLF               () { return Write( "\r\n" ); }
				
			void                        GoStart                 ();
			void                        AdvanceFilePos          ( uint _uAdvance );
				
			void                        SetNoPack               ();
			void                        SetLookInAndOutPack     ();
			void                        UseLanguageVersions     () { m_bLanguageVersions = true; }

			char*                       GetName                 () { return m_pszFileName; }
			uint                        GetFilePos              ();

			int                         GetSize                 ();
			bool                        IsFileEmpty             () { return ( GetSize() == 0 ); } // NOTE: This function resets read pointer to the begining
			bool                        IsFileOpen              () { return m_pFile!=NULL || m_pPackFile!=NULL; }
			void                        SetLog                  ( bool _bSet ) { m_bLog = _bSet; }
			static bool                 Exists                  ( const char* _pszFileName, bool _bInPack = true );
			static bool                 Exists                  ( const char* _pszDir, const char* _pszFileName, bool _bInPack = true );
			bool                        HayError                () { return m_bHadError; }
			ERetVal                     GetErrorState           () { return m_bHadError ? RET_ERR : RET_OK; }
			void                        ClearError              () { m_bHadError = false; }
				
	private:
		
			void                        UpdateError             ( ERetVal eRetVal );
			ERetVal                     Open_LowLvl             ( const char* _pszFile );
			char*                       BuildLanguageFileName   ( const char* _pszFile );
				
	private:
		
			void*                       m_pFile;   //..is a FILE*, is void to not include more headers and stuff. Only used when there is no PACK
			CFilePack::TFile*           m_pPackFile;   //..only when there is PACK

			char*                       m_pszFileName;
			bool                        m_bLog;
			bool                        m_bHadError;  // set true when there is any kind of error with the operations in this file. Used to not need to check on every call
			bool                        m_bPackFile; // true id the file is inside a PACK
																								// by defulta everything is a packfile, unless specified otherwise. But after creation, this become false if there is not actual PACK
			bool                        m_bLanguageVersions; // if this is set a true before opening a file, the real file that will be opened will be with a language suffix added                                                 ç
			bool                        m_bLookInAndOutPack; // when true, the file is first looked into the pack, then, if not found, is looked outside
}; 



