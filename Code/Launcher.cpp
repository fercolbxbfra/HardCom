// Launcher.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include "launcher.h"
//#include "Vector.h"
//#include "D3DMgr.h" 
#include "log.h"
#include "Globals.h"
//#include "LowInput.h"
//#include "MemoryMgr.h"
//#include "ModesMgr.h"
//#include "Graphics.h"
#include "Setup.h"
//#include "UserInput.h"
//#include "StringsMgr.h"
//#include "MsgMgr.h"
//#include "Cursor.h"
//#include "Camera.h"
//#include "SoundMgr.h"
//#include "MusicMgr.h"
//#include "2DEngine.h"
//#include "PerfMeterMgr.h"
//#include "SysHRTimer.h"
//#include "InitSplashScreen.h"
#include "FilePack.h"
//#include "NetMgr.h"
//#include "Client.h"
//#include "WSADefines.h"
//#include "GameWorld.h"
//#include "Pruebas.h"
//#include "Terrain.h"
//#include "ItfMgr.h"
//#include "NodeMgr.h"
//#include "DebugInfoMgr.h"
//#include "Traces.h"
//#include "DataTables.h"
//#include "MsgWindowMgr.h"

//#include <winuser.h>
//#include <malloc.h> 
//#include <memory.h>
//#include <tchar.h>
#include <direct.h>
//#include <time.h>



DWORD WindowedStyleWindow = WS_CAPTION; //WS_BORDER | WS_CAPTION; //| WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX;

// Variables globales:
TCHAR*     pszTitle = "HardCom";
TCHAR*     pszWindowClass = "WindowClass";
HWND       hWndGame;


//CD3DMgr*            g_pD3DMgr           = NULL;
//CLowInput*          g_pLowInput         = NULL;
//CModesMgr*          g_pModesMgr         = NULL;
//CGraphics*          g_pGraphics         = NULL;
//CSetup*             g_pSetup            = NULL;
//CTraces*            g_pTraces           = NULL;
//CUserInput*         g_pUserInput        = NULL;
//CStringsMgr*        g_pStringsMgr       = NULL;
//CMsgMgr*            g_pMsgMgr           = NULL;
//CTerrain*           g_pTerrain          = NULL;
//CSoundMgr*          g_pSoundMgr         = NULL;
//CMusicMgr*          g_pMusicMgr         = NULL;
//CGameMgr*           g_pGameMgr          = NULL;
//CGameWorld*         g_pGameWorld        = NULL;
//C2DEngine*          g_p2DEngine         = NULL;
//CDebugInfoMgr*      g_pDebugInfoMgr     = NULL;
//CPerfMeterMgr*      g_pPerfMeterMgr     = NULL;
//CSysHRTimer*        g_pSysHRTimer       = NULL;
CFilePack*          g_pFilePack         = NULL;
//CNetMgr*            g_pNetMgr           = NULL;
//CClient*            g_pClient           = NULL;
//CGRWorld*           g_pGRWorld          = NULL;
//CItfMgr*            g_pItfMgr           = NULL;
//CNodeMgr*           g_pNodeMgr          = NULL;
//CMsgWindowMgr*      g_pMsgWindowMgr     = NULL;

//CMemoryMgr  g_MemoryMgr;

int             g_hInstance;
int             g_hGameWindow;


HWND    CreateGameWindow            ( HINSTANCE _hInstance, int _nCmdShow);
ERetVal InitProgram                 ( HINSTANCE _hInstance, int _nCmdShow );
void    EndProgram                  ();
//void    SwitchWindowMode            ();
void    CheckInitialDir             ();
//void    CalculateVersionChecksum    ();

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


//////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPTSTR _lpCmdLine, int _nCmdShow)
{
	MSG vMsg;

	g_hInstance = int(_hInstance);

	ERetVal RetVal = InitProgram( _hInstance, _nCmdShow );

	if (RetVal==RET_OK)
	{
		bool bQuit = false;

		// main message loop
		while (bQuit==false)
		{
			ZeroMemory( &vMsg, sizeof(vMsg) );
			while (PeekMessage( &vMsg, NULL, 0U, 0U, PM_REMOVE ) )
			{
				TranslateMessage( &vMsg );
				DispatchMessage( &vMsg );
			}
//			if (g_pD3DMgr->IsDeviceLost())
//				g_pD3DMgr->TryToRecoverDeviceLost();
//			else
//				bQuit = g_pModesMgr->MainLoop();

//			if (g_pLowInput->IsKeyKeptPressed( LT_LALT ) && g_pLowInput->IsKeyKeptPressed( LT_INTRO ) && !bQuit)
//				SwitchWindowMode();
		}

	}

	EndProgram();

	return 0; //(int) vMsg.wParam;
}


//////////////////////////////////////////////////////////////////////////
ERetVal InitProgram( HINSTANCE _hInstance, int _nCmdShow  )
{
	HWND hWnd;


	ERetVal eRetVal = RET_OK;

	//CheckVersionTimeOut();

//	g_MemoryMgr.Init();


	if (eRetVal==RET_OK)
	{
//		g_pSysHRTimer   = NEW CSysHRTimer;
//		eRetVal         = g_pSysHRTimer->Init();
	}

	if (eRetVal==RET_OK)
	{
//		g_pPerfMeterMgr = NEW CPerfMeterMgr;
//		eRetVal         = g_pPerfMeterMgr->Init();
	}

	LOG(( "-----------HARDCOM RUNNNNINNNNNGGGG------------------------" ));

	CheckInitialDir();

	//....filepack...
	if (eRetVal==RET_OK)
	{
		g_pFilePack = NEW CFilePack;
		eRetVal     = g_pFilePack->Init( PACK_FILENAME );
	}

	//....ficherito de setup...
	if (eRetVal==RET_OK)
	{
//		g_pSetup    = NEW CSetup;
//		eRetVal     = g_pSetup->Init();
	}

	//....logs....
	if (eRetVal==RET_OK)
		CLog::Init_PostSetup();

	//...strings manager        
	if (eRetVal==RET_OK)
	{
//		g_pStringsMgr       = NEW CStringsMgr;
//		eRetVal             = g_pStringsMgr->Init();   
	}     

	//... MsgMgr
	if (eRetVal==RET_OK)
	{
//		g_pMsgMgr = NEW CMsgMgr;
//		eRetVal = g_pMsgMgr->Init();   
	}     
	
	//..... crear ventana
//	if (eRetVal==RET_OK)
	{
		hWnd            = CreateGameWindow( _hInstance, _nCmdShow );
		hWndGame        = hWnd;
//		eRetVal         = hWnd ? RET_OK : RET_ERR;
		g_hGameWindow   = int(hWndGame);
	}

	//.........net mgr................
	if (eRetVal==RET_OK)
	{
//		g_pNetMgr = NEW CNetMgr;
		//..is not initialized here, is done inside ModesMgr initialization
	}

	//.....low input. is created here, but is initialiced inside g_pD3DMgr initialization................
	if (eRetVal==RET_OK)
	{
//		g_pLowInput   = NEW CLowInput;
//		g_pLowInput->WinInit( (uint)_hInstance, g_hGameWindow );
//		g_pLowInput->SetUsarMouse( true );
	}

	//.......direct 3d.................
	if (eRetVal==RET_OK)
	{
//		g_pD3DMgr       = NEW CD3DMgr();
//		eRetVal         = g_pD3DMgr->Init( (int)hWnd );
		if (eRetVal==RET_OK)
		{
//			if (g_pSetup->GetInfo().m_bFullScreen)
//				g_pD3DMgr->SetModeFullScreen();
//			else
//				g_pD3DMgr->SetModeWindowed();
		}
	}

	//...splash screen..........
	if (eRetVal==RET_OK)
	{
//		DrawInitSplashScreen();
	}


	//....node mgr..........
	if (eRetVal==RET_OK)
	{
//		g_pNodeMgr      = NEW CNodeMgr;
//		eRetVal         = g_pNodeMgr->Init();
	}

	//.....graphics.............................
	if (eRetVal==RET_OK)
	{
//		g_pGraphics = NEW CGraphics;
//		eRetVal     = g_pGraphics->Init();
	}


	//....2d engine....
	if (eRetVal==RET_OK)
	{
//		g_p2DEngine = NEW C2DEngine;
//		eRetVal     = g_p2DEngine->Init();
	}


	//.......user input......
	if (eRetVal==RET_OK)
	{
//		g_pUserInput    = NEW CUserInput;
//		eRetVal         = g_pUserInput->Init();
	}


	// Traces manager
	if (eRetVal==RET_OK)
	{
//		g_pTraces   = NEW CTraces;
//		eRetVal     = g_pTraces->Init();
	}


	// Debug information manager
	if (eRetVal==RET_OK)
	{
//		g_pDebugInfoMgr = NEW CDebugInfoMgr;
//		eRetVal         = g_pDebugInfoMgr->Init();
	}


	// Sound engine
	if ( eRetVal == RET_OK )
	{
//		g_pSoundMgr     = NEW CSoundMgr;
//		eRetVal         = g_pSoundMgr->Init();
	}


	// Music manager
	if ( eRetVal == RET_OK )
	{
//		g_pMusicMgr     = NEW CMusicMgr;
//		eRetVal         = g_pMusicMgr->Init();
	}


	// Interfaces manager
	if ( eRetVal == RET_OK )
	{
//		g_pItfMgr       = NEW CItfMgr;
//		eRetVal         = g_pItfMgr->Init();
	}


	// Message window manager
	if ( eRetVal == RET_OK )
	{
//		g_pMsgWindowMgr = NEW CMsgWindowMgr;
//		eRetVal         = g_pMsgWindowMgr->Init();
	}


	//..global data tables
	if (eRetVal==RET_OK)
	{
//		eRetVal = CDataTables::Init();
	}        

	//....gestor de modos de programa...
	if (eRetVal==RET_OK)
	{
//		g_pModesMgr = NEW CModesMgr;
//		eRetVal = g_pModesMgr->Init();
	}
	


	return eRetVal; 
}


//////////////////////////////////////////////////////////////////////////

void EndProgram()
{
//	PruebasRun      ( true );
//	PruebasPreDraw  ( true );
//	PruebasDraw     ( true );
//	DISPOSEIF( g_pModesMgr );
//	DISPOSEIF( g_pMsgWindowMgr );
//	CDataTables::End();
//	DISPOSEIF( g_pItfMgr );
//	DISPOSEIF( g_pMusicMgr );
//	DISPOSEIF( g_pSoundMgr );
//	DISPOSEIF( g_pDebugInfoMgr );
//	DISPOSEIF( g_pTraces );
//	DISPOSEIF( g_pUserInput );
//	DISPOSEIF( g_p2DEngine );
//	DISPOSEIF( g_pGraphics );
//	DISPOSEIF( g_pLowInput ); 
//	DISPOSEIF( g_pNodeMgr );
//	DISPOSEIF( g_pD3DMgr );
//	DISPOSEIF( g_pNetMgr );
//	DISPOSEIF( g_pMsgMgr );
	SAFE_DELETE( g_pFilePack );
//	DISPOSEIF( g_pStringsMgr );
//	DISPOSEIF( g_pSetup );
//	DISPOSEIF( g_pPerfMeterMgr );
//	DISPOSEIF( g_pSysHRTimer );
//	CDataTables::End();
//	g_MemoryMgr.End();

	CLog::End(); 
	
}


//////////////////////////////////////////////////////////////////////////

HWND CreateGameWindow(HINSTANCE _hInstance, int _nCmdShow)
{
	//......
	WNDCLASS wc;

	wc.style          = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc    = (WNDPROC)WndProc;
	wc.cbClsExtra     = 0;
	wc.cbWndExtra     = 0;
	wc.hInstance      = _hInstance;
	wc.hIcon          = LoadIcon( _hInstance, MAKEINTRESOURCE(IDI_HARDCOM) );
	wc.hCursor        = LoadCursor(NULL, 0 ); //IDC_ARROW);
	wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName   = NULL;
	wc.lpszClassName  = pszWindowClass;

	RegisterClass(&wc);

//	const V2I& vTamWindow = g_pSetup->GetInfoDev().m_vScreenSize;

	RECT rcWork;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);
	int x = ( (rcWork.right - rcWork.left) / 2 ) - 1024 /*vTamWindow.x*/ / 2;
	int y = ( (rcWork.bottom - rcWork.top) / 2 ) - 768 /*vTamWindow.y*/ / 2;

	RECT rcClient;
	rcClient.bottom = y + 768; //vTamWindow.y;
	rcClient.left   = x;
	rcClient.right  = x + 1024; //vTamWindow.x;
	rcClient.top    = y;
	BOOL bBien = AdjustWindowRect( &rcClient, WindowedStyleWindow, false );
	int iTamX = rcClient.right - rcClient.left;
	int iTamY = rcClient.bottom - rcClient.top;

	//......crear la ventana........
	HWND hWnd = CreateWindow(pszWindowClass, pszTitle, WindowedStyleWindow, rcClient.left, rcClient.top, iTamX, iTamY, NULL, NULL, _hInstance, NULL);

	SetCursor( NULL );

	//....visualizarla una primera vez............
	if (hWnd)
	{
		int x = 1024/2; //vTamWindow.x/2;
		int y = 768/2; //vTamWindow.y/2;
		SetCursorPos( x, y );
		ShowWindow  ( hWnd, _nCmdShow );
		UpdateWindow( hWnd );
	}

	return hWnd;
}


//////////////////////////////////////////////////////////////////////////

void SetWindowSize( int _sx, int _sy )
{
	RECT rcWork;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0);
	int x = ( (rcWork.right - rcWork.left) / 2 ) - _sx / 2;
	int y = ( (rcWork.bottom - rcWork.top) / 2 ) - _sy / 2;
	if (x<0)
		x = 0;
	if (y<5)  //,..arbitrary value to have at least some upper border for the window
		y = 5;
	RECT rcClient;
	rcClient.bottom = y + _sy;
	rcClient.left   = x;
	rcClient.right  = x + _sx;
	rcClient.top    = y;
	BOOL bOk = AdjustWindowRect( &rcClient, WindowedStyleWindow, false );
	int sx = rcClient.right - rcClient.left;
	int sy = rcClient.bottom - rcClient.top; 
	SetWindowPos( hWndGame, HWND_NOTOPMOST, rcClient.left, rcClient.top, sx, sy, NULL );
}


//////////////////////////////////////////////////////////////////////////
/*
void PasarDeFullScreenAWindowed()
{
	V2I vTamWindow = g_pD3DMgr->GetTamWindow();
	SetWindowTam( vTamWindow.x, vTamWindow.y );
	g_pD3DMgr->SetModeWindowed(); 
	SetWindowTam( vTamWindow.x, vTamWindow.y );
}
*/

//////////////////////////////////////////////////////////////////////////
/*
void SwitchWindowMode()
{
	if (g_pD3DMgr->EstaEnFullScreen())
		PasarDeFullScreenAWindowed();
	else
		g_pD3DMgr->SetModeFullScreen();
}
*/


//----------------------------------------------------------------------
// WndProc
//
// Bucle principal de mensajes de windows 
//----------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _uMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMessage) 
	{
	case WM_PAINT:
		{
			ValidateRect( _hWnd, NULL );
			break;
		}

	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

	case WM_MOUSEMOVE:
		{

			if (GetCursor()!=NULL)
				SetCursor( NULL );
//			if (g_pGraphics && g_pGraphics->GetCursor())
//			{
//				g_pGraphics->GetCursor()->NotificaPosMouseWindows( int(_lParam&0xffff), int(_lParam>>16) );
//			} 
			break;
		}

	case WM_ACTIVATE:
		{

//			if (g_pGraphics && g_pGraphics->GetCursor())
			{
//				bool bActive = LOWORD( _wParam )==WA_ACTIVE || LOWORD( _wParam )==WA_CLICKACTIVE;
//				g_pGraphics->GetCursor()->NotifyActiveWindowsChange( bActive ); 
			}

			break;
		}


	case WM_SETFOCUS:
		{
//			if (g_pLowInput)
//				g_pLowInput->NotifyWindowSetFocus();
//			if (g_pModesMgr)
//				g_pModesMgr->NotifyWindowSetFocus();
			break;
		}


	case WM_KILLFOCUS:
		{
//			if (g_pModesMgr)
//				g_pModesMgr->NotifyWindowLostFocus();
//			if (g_pLowInput)
//				g_pLowInput->NotifyWindowLostFocus();
			break;
		}

	case WM_CHAR:
		{
//			if (g_pLowInput)
//				g_pLowInput->AddCharToHLBuffer( _wParam );
			break;
		}

	case WM_KEYDOWN:
		{
//			if (g_pLowInput)
//				g_pLowInput->AddVKeyToHLBuffer( _wParam );
			break;
		}

//	case WM_WSAASYNC:
//		if (g_pNetMgr)
//			g_pNetMgr->HandleAsyncWSAMsg( _wParam, _lParam );
//		break;

	default:
		return DefWindowProc(_hWnd, _uMessage, _wParam, _lParam);
	}
	return 0;
}


//----------------------------------------------------------------------
// makes Sure that the program is running in the right folder, and if not, tries to change it

void CheckInitialDir()
{
	bool bFound = false;

	//..pack..
	FILE* pFilePack = fopen( PACK_FILENAME, "rb" );
	bFound = pFilePack!=NULL;

	//...check dir DATA 
	if (!bFound)
	{
		bFound = _chdir( DIR_DATA )==0;
		if (bFound)
			_chdir( ".." );
	}

	if (!bFound)
		bFound = _chdir( "../Game/" )==0;

	if (!bFound)
		bFound = _chdir( "../../Game/" )==0;

	if (pFilePack)
		fclose( pFilePack );

	ASSERTM( bFound, ("Cant find 'game' folder. Probably executable is at the wrong place") );
}

































//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// ORIGINAL CODE GENERATED BY VISUL STUDIO, LEFT FOR TEMPORARY REFERENCE /////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HARDCOM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HARDCOM));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HARDCOM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HARDCOM);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
*/