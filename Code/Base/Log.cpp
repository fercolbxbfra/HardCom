//-----------------------------------------------------------------------------
// TODO: size checks are not 100% safe, really big log messages could overdlow buffers in some situations
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Log.h"
//#include "NetMgr.h"
#include "Globals.h"
//#include "Setup.h"
//#include "ModesMgr.h"

#include <time.h>

#define MAX_SIZE_LOG_LINE 1024
#define VAL_CHECK_END_BUFFER 0x574Ab719   //...just a randon value


bool                CLog::m_bLogInFile      = false;
char                CLog::m_szLogFile[ MAX_FILENAME_SIZE ] = "\0";
FILE*               CLog::m_fp              = NULL;

bool                CLog::m_bDateInLogs     = false;
bool                CLog::m_bTimeInLogs     = true;
bool                CLog::m_bTickInLogs     = true;

bool                CLog::m_bLogExternal    = false;
bool                CLog::m_bReadyToSend    = false;

HANDLE              CLog::m_hChildProc      = NULL;
HANDLE              CLog::m_hReadPipe       = NULL;
HANDLE              CLog::m_hWritePipe      = NULL;

//////////////////////////////////////////////////////////////////////////

void CLog::Init_PostSetup()
{
	m_bLogInFile = false; //g_pSetup->GetInfoDev().m_bLogsInFile;
/*	CAT_2_STRINGS( m_szLogFile, DIR_OUTPUT, "log.dat" g_pSetup->GetInfoDev().m_szLogFileName );
		
	if (m_bLogInFile && strlen(g_pSetup->GetInfoDev().m_szLogFileName)>0)
	{
		m_fp = fopen( m_szLogFile, "wb" );
		if (!m_fp)
			ERROR_UBER_CRITICAL(( "could not creathe the file: %s", m_szLogFile ));
	}
	*/

	m_bDateInLogs = false; //g_pSetup->GetInfoDev().m_bDateInLogs;

	//...redirect msgs to external viewer
	m_bLogExternal  = false; //g_pSetup->GetInfoDev().m_bLogsToExternal;

	if ( m_bLogExternal )
	{
		m_bReadyToSend = false;

		// Create pipe
		SECURITY_ATTRIBUTES saAttr;
				
		saAttr.nLength              = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle       = true;
		saAttr.lpSecurityDescriptor = NULL;

		if ( CreatePipe( &m_hReadPipe, &m_hWritePipe, &saAttr, 0 ) )
			m_bReadyToSend = true;

		// Create child process
		if ( m_bReadyToSend )
		{
			char szBufCmdLine[255];
			sprintf( szBufCmdLine, "%s %ld", DIR_LOGS EXTERNAL_LOG_PROGRAM, (int) m_hReadPipe );

			PROCESS_INFORMATION piProcInfo; 
			STARTUPINFO         siStartInfo; 
			ZeroMemory( &siStartInfo, sizeof(siStartInfo) );

			// Set up members of STARTUPINFO structure.
			siStartInfo.cb = sizeof(STARTUPINFO); 
			siStartInfo.lpReserved = NULL; 
			siStartInfo.lpReserved2 = NULL; 
			siStartInfo.cbReserved2 = 0; 
			siStartInfo.lpDesktop = NULL;  
			siStartInfo.dwFlags = STARTF_USESHOWWINDOW;
			siStartInfo.wShowWindow = SW_SHOWNOACTIVATE;
					
			// Create the child process.
			BOOL bCreateProcessOk = CreateProcess( NULL, szBufCmdLine,  /* command line                         */ 
																					NULL,                /* process security attributes          */ 
																					NULL,                /* primary thread security attributes   */ 
																					true,                /* handles are inherited                */ 
																					0,                   /* creation flags                       */ 
																					NULL,                /* use parent's environment             */ 
																					NULL,                /* use parent's current directory       */ 
																					&siStartInfo,        /* STARTUPINFO pointer                  */ 
																					&piProcInfo );       /* receives PROCESS_INFORMATION         */ 

			if( bCreateProcessOk )
			{
				m_hChildProc    = piProcInfo.hProcess;
				m_bReadyToSend  = true;
			}
			else
				m_bReadyToSend = false;
		}
	}
}


//////////////////////////////////////////////////////////////////////////

void CLog::End()
{
	if (m_fp)
		fclose( m_fp );
		
	// Close pipe
	CloseHandle( m_hWritePipe );
}
		
		
//////////////////////////////////////////////////////////////////////////

void CLog::Log( const char* _pszMsg, bool bPutDate )
{
	if (_pszMsg)
	{
		char szBuffer[MAX_SIZE_LOG_LINE];
		memset( szBuffer, 0, sizeof(szBuffer) );

		if ( bPutDate )
			AddDateAndTime( szBuffer, sizeof(szBuffer) ); 
		CatString( szBuffer, sizeof(szBuffer), _pszMsg );

		CatString( szBuffer, sizeof(szBuffer), "\n" );
				
		OutputDebugString( szBuffer );
				
		// Si salvamos en fichero
		if ( m_fp )
		{
			fwrite( szBuffer, strlen(szBuffer), 1, m_fp );
			fwrite( "\r", 1, 1, m_fp );
			fflush( m_fp );
		}

		// msg to external viewer
		if ( m_bLogExternal && m_bReadyToSend )
			SendToExternal( szBuffer );
	}
}


//////////////////////////////////////////////////////////////////////////

void CLog::Logf( const char *_pszFmt, ... )
{
	MACRO_PRINTF( szBuffer, MAX_SIZE_LOG_LINE )
		Log(szBuffer);
}


void CLog::LogfNoDate( const char *_pszFmt, ... )
{
	MACRO_PRINTF( szBuffer, MAX_SIZE_LOG_LINE )
		Log( szBuffer, false );
}



//////////////////////////////////////////////////////////////////////////
// adds date yand time into the given string

void CLog::AddDateAndTime( char* _pszBuf, int _iSize )
{
	_pszBuf[0] = 0;
	char szDate[20];
	szDate[0] = 0;
	char szTime[20];
	szTime[0] = 0;
	char szTick[20];
	szTick[0] = 0;
	if (m_bDateInLogs)
	{
			_strdate( szDate );
			CatString( szDate, sizeof(szDate), " " ); 
	}
	if (m_bTimeInLogs)
	{
			_strtime( szTime );
			CatString( szTime, sizeof(szTime), " " ); 
	}
		
//    if (m_bTickInLogs && g_pModesMgr)
//    {
//        SprintfSafe( szTick, sizeof(szTick), "%d ", g_pModesMgr->GetTick() );
//    }

	CatString( _pszBuf, _iSize, szDate );
	CatString( _pszBuf, _iSize, szTime );
	CatString( _pszBuf, _iSize, szTick );
}


//////////////////////////////////////////////////////////////////////////
// Sends a message through the pipe

void CLog::SendToExternal( const char* _pszMsg )
{
	DWORD dwExitCode;

	if ( GetExitCodeProcess( m_hChildProc, &dwExitCode ) )
	{
		if ( dwExitCode == STILL_ACTIVE )  
		{
			DWORD   dwWritten = (DWORD) strlen( _pszMsg ); 
			DWORD   dwWrittenReal;
			BOOL    bSuccess;

			bSuccess = WriteFile( m_hWritePipe, _pszMsg, dwWritten, &dwWrittenReal, NULL );
			if ( !bSuccess )
				m_bReadyToSend = false;            
		}
		else
			m_bReadyToSend = false;
	}
}


