//----------------------------------------------------------------------
// TODO: size checks are not 100% safe, really big log messages could overdlow buffers in some situations
//----------------------------------------------------------------------

#include "stdafx.h"

#include "Log.h"
#include "globals.h"
//#include "NetMgr.h"
//#include "D3DMgr.h"

#include <signal.h>


void NotifyErrorInternal( const char *_pszBuffer );
bool st_bShowAsserts = true;


void CheckFullScreen();
void NotifyAssertFailureNet( const char *_pszExpr, const char* _pszInfo, const char *_pszFile, unsigned _uLine );

//////////////////////////////////////////////////////////////////////////
// returns an string from a sprintf style call. MBT -> Message Box Thingies

const char* MBT_FormatText( const char *_pszFmt, ... )
{
	static char szBuffer[500];  
	if ( strlen(_pszFmt)>sizeof(szBuffer)-200)
	{
		CheckFullScreen();
		MessageBox( NULL, "Assert with text probably too long", "Assert Error", MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );
		exit(3);
	}
	va_list ap;
	va_start(ap, _pszFmt);
	vsprintf(szBuffer,_pszFmt, ap);
	va_end(ap);
	if ( strlen(szBuffer)>sizeof(szBuffer))
	{
		CheckFullScreen();
		MessageBox( NULL, "Assert with text probably too long", "Assert Error", MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );
		exit(3);
	}
	return szBuffer;
}


#ifdef _ASSERTS_
//////////////////////////////////////////////////////////////////////////
// shows the assert msgbox and reacts to the clicks on it

void NotifyAssertFailureInternal( const char *_pszBuffer )
{
	if (!st_bShowAsserts)
		return;
	CheckFullScreen();
	int nCode = MessageBox( NULL, _pszBuffer, "Assert Error", MB_ABORTRETRYIGNORE|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );

	switch( nCode )
	{
		case IDABORT:
		raise( SIGABRT ); // raise abort signal
		_exit(3);         // in case the exception is ignored
		break;

		case IDRETRY:
		_asm int 3;
		return;           // return to user code

		case IDIGNORE:
		break;

		default:
		raise( SIGABRT ); // raise abort signal
		_exit(3);         // in case the exception is ignored
	}
}


//////////////////////////////////////////////////////////////////////////
// builds the text string to show with the assert

void NotifyAssertFailure( const char *_pszExpr, const char* _pszInfo, const char *_pszFile, unsigned _uLine )
{
//	if (g_pNetMgr && g_pNetMgr->IsInsideAsyncLoop())
//		NotifyAssertFailureNet( _pszExpr, _pszInfo, _pszFile, _uLine );
//	else
	{
		char Buffer[ 500 ];
		if (_pszInfo)
		{
			char* pszFormato = "Msg: %s   \n\nExpr: %s\nFile: %s\nLine: %ld\n";
			if ( strlen(pszFormato) + strlen(_pszExpr) + strlen(_pszInfo) + strlen(_pszFile) > sizeof(Buffer)-100)
			{
				CheckFullScreen();
				MessageBox( NULL, "Assert with text probably too long", "Assert Error", MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );
				exit(3);
			}
			sprintf( Buffer, pszFormato, _pszInfo, _pszExpr, _pszFile, _uLine );
		}
		else
		{
			char* pszFormato = "Expr: %s\nFile: %s\nLine: %ld\n";
			if ( strlen(pszFormato) + strlen(_pszExpr) + strlen(_pszFile) > sizeof(Buffer)-100 )
			{
				CheckFullScreen();
				MessageBox( NULL, "Assert with text probably too long", "Assert Error", MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );
				exit(3);
			}
			sprintf( Buffer, pszFormato, _pszExpr, _pszFile, _uLine );
		}
						
		NotifyAssertFailureInternal( Buffer );
	}
}


//////////////////////////////////////////////////////////////////////////
// builds the text string to show with the assert

void NotifyAssertFailureNet( const char *_pszExpr, const char* _pszInfo, const char *_pszFile, unsigned _uLine )
{
	char Buffer[ 500 ];
	if (_pszInfo)
	{
		char* pszFormato = "Msg: %s   \n\nExpr: %s\nFile: %s\nLine: %ld\n";
		if ( strlen(pszFormato) + strlen(_pszExpr) + strlen(_pszInfo) + strlen(_pszFile) > sizeof(Buffer)-100)
		{
			CheckFullScreen();
			LOG(( "ERR: Assert with text probably too long", "Assert Error" ));
			exit(3);
		}
		sprintf( Buffer, pszFormato, _pszInfo, _pszExpr, _pszFile, _uLine );
	}
	else
	{
		char* pszFormato = "Expr: %s\nFile: %s\nLine: %ld\n";
		if ( strlen(pszFormato) + strlen(_pszExpr) + strlen(_pszFile) > sizeof(Buffer)-100 )
		{
			CheckFullScreen();
			LOG(( "ERR: Assert with text probably too long", "Assert Error" ));
			exit(3);
		}
		sprintf( Buffer, pszFormato, _pszExpr, _pszFile, _uLine );
	}
		
	if (!st_bShowAsserts)
			return;
				
		LOG(("ASSERTNET: %s %s %d", Buffer, _pszFile, _uLine ));        
				
//		g_pNetMgr->NotifAssertMsgLoop(); 
}

#endif 


//////////////////////////////////////////////////////////////////////////
// messagebox with a message. Used when we want to warn about something at the start of the program but that program can continue without problem

void Warning( const char *_pszMsg )
{
	CheckFullScreen();
	MessageBox( NULL, _pszMsg, "Warning", MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );
}


//////////////////////////////////////////////////////////////////////////

void ErrorUberCritical( const char *pszMsg )
{
	CheckFullScreen();
	MessageBox( NULL, pszMsg, "Critical Error", MB_OK|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );
	exit(3);
}



//////////////////////////////////////////////////////////////////////////

void NotifyErrorInternal( const char *pszBuffer )
{
	if (!st_bShowAsserts)
		return;
	CheckFullScreen();
	int nCode = MessageBox( NULL, pszBuffer, "ERROR", MB_ABORTRETRYIGNORE|MB_ICONHAND|MB_SETFOREGROUND|MB_TASKMODAL );

	switch( nCode )
	{
		case IDABORT:
		raise( SIGABRT ); // raise abort signal
		_exit(3);         // in case the exception is ignored
		break;

		case IDRETRY:
		_asm int 3;
		return;           // return to user code

		case IDIGNORE:
		break;

		default:
		raise( SIGABRT ); // raise abort signal
		_exit(3);         // in case the exception is ignored
	}
}


//////////////////////////////////////////////////////////////////////////
// goes back to windowed mode in case we need to show a messagebox

void CheckFullScreen()
{
//	if (g_pD3DMgr && g_pD3DMgr->EstaEnFullScreen())
	{
//			PasarDeFullScreenAWindowed();  //..esta funcion esta en main.cpp
	}
}
