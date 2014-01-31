//----------------------------------------------------------------------------
// CLowInput
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "LowInput.h"
#include "Log.h"
#include "Keys.h"
#include "DXErrors.h"
#include "Globals.h"
//#include "ModesMgr.h"
//#include "D3DMgr.h"
#include "Setup.h"

#include <dinput.h>
#include <d3d9.h>


#define KEYBOARD_BUFFER_SIZE_DIRECTX    256     // defines the internal buffer size that DX will use for to store buffered data
#define MOUSE_BUFFER_SIZE_DIRECTX       1024    // defines the internal buffer size that DX will use for to store buffered data
//#define TIME_FOR_STROKE                 250     // max time (ms) between press-release of a key to produce an EV_KEY_STROKE event.
#define TIME_FOR_DOUBLECLICK            300     // max time (ms) betwen clicks to make a doubleclick event
#define TIME_FOR_DRAG                   500     // time (ms) that a mouse button must be pressed to start dragging (if not moving)
#define MOUSEMOVE_FOR_DRAG              2       // minimun movement that makes the mouse draging starts (it can be started also when there is a movement past the STROKE time)

//////////////////////////////////////////////////////////////////////////

CLowInput::CLowInput()
{
	m_pDirectInput          = NULL;
	m_pDeviceKeyboard       = NULL;
	m_hInst                 = NULL;
	m_hWnd                  = NULL;
	m_pDeviceMouse          = NULL;
	m_iNumEvents            = 0;
	m_eModsKey              = MO_NOTHING;
	m_eDragKey              = LT_NO_KEY;
	m_bDragging             = false;
	m_bPreDragging          = false;
	m_bStartPreDragging     = false;
	m_eLastMouseButton      = LT_NO_KEY;
	m_uLastTimeClick        = 0;
	m_uFirstFree            = 0;
	m_uFirstFull            = 0;
	m_bUsingMouse          = false;
	m_iNumKeysToCleanClick  = 0;    
	m_bPendingKeyboardFlush = false;
	m_bPendingMouseFlush    = false;
	m_iNumCharsInHLBuffer   = 0;
	m_bHLBufferActive       = false;
	m_bInitialiced          = false;
}


//////////////////////////////////////////////////////////////////////////

#define RELEASE( o ) if (o) { o->Release(); o = NULL; }

void CLowInput::End()
{
	if (m_pDeviceKeyboard) m_pDeviceKeyboard->Unacquire();
	RELEASE( m_pDeviceKeyboard );
	if (m_pDeviceMouse) m_pDeviceMouse->Unacquire();
	RELEASE( m_pDeviceMouse );
	RELEASE( m_pDirectInput );
	m_bInitialiced          = false;
}


//////////////////////////////////////////////////////////////////////////

void CLowInput::WinInit( uint hInst, uint hWnd )
{
	m_hInst = hInst;
	m_hWnd  = hWnd;
}



//////////////////////////////////////////////////////////////////////////

ERetVal CLowInput::DXInit()
{    
	ERetVal eRetVal    = RET_OK;
		
	//...clear state of all keys.......
	for (int k=0; k<LT_NUM_KEYS; k++)
	{
		m_aKeysState[k].m_bClick        = false;
		m_aKeysState[k].m_bHold         = false;
	}
		
	m_KeysMgr.Init();    

	//...........create direct input object..........
	LOG(( "INF: Creating Direct Input object" ));

	ASSERT( m_pDirectInput == NULL );

	HRESULT hr; 

	hr = DirectInput8Create((HINSTANCE)m_hInst, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&m_pDirectInput, NULL); 
	eRetVal = CHECKDXERROR( hr,   F_DIRECTINPUT8CREATE );


	//.......create keyboard object........
	if (eRetVal==RET_OK)
	{
		hr = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pDeviceKeyboard, NULL); 
		eRetVal = CHECKDXERROR( hr,   F_CREATEDEVICE );
	}


	//....set keyboard data format...
	if (eRetVal==RET_OK)
	{
		hr = m_pDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard); 
		eRetVal = CHECKDXERROR( hr, F_SETDATAFORMAT );
	}
		
	//...set buffer size for keyboard...
	if (eRetVal==RET_OK)
	{
		DIPROPDWORD dipdw; 
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD); 
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		dipdw.diph.dwObj        = 0; 
		dipdw.diph.dwHow        = DIPH_DEVICE; 
		dipdw.dwData            = KEYBOARD_BUFFER_SIZE_DIRECTX;    

		hr = m_pDeviceKeyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
		eRetVal = CHECKDXERROR( hr, F_SETPROPERTY );
	}


	//...keyboard cooperative lvl...
	if (eRetVal==RET_OK)
	{
		hr = m_pDeviceKeyboard->SetCooperativeLevel( (HWND)m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		eRetVal = CHECKDXERROR( hr, F_SETCOOPERATIVELEVEL );
	}
		
	if (eRetVal==RET_OK)
	{
		//....device mouse....
		hr = m_pDirectInput->CreateDevice( GUID_SysMouse, &m_pDeviceMouse, NULL );
		eRetVal = CHECKDXERROR( hr, F_CREATEDEVICE );
	}
		
	//....mouse data format...
	if (eRetVal==RET_OK)
	{
		hr = m_pDeviceMouse->SetDataFormat( &c_dfDIMouse2 );
		eRetVal = CHECKDXERROR( hr, F_SETDATAFORMAT );
	}
		
	//...mouse cooperative lvl...
	if (eRetVal==RET_OK)
	{
		DWORD dwFlags = DISCL_FOREGROUND;
//		if (g_pD3DMgr->EstaEnFullScreen())
//			dwFlags |= DISCL_EXCLUSIVE;
//		else
			dwFlags |= DISCL_NONEXCLUSIVE;
		hr = m_pDeviceMouse->SetCooperativeLevel((HWND)m_hWnd, dwFlags );
		eRetVal = CHECKDXERROR( hr, F_SETCOOPERATIVELEVEL );
	} 
		
	//...set buffer size for mouse...
	if (eRetVal==RET_OK)
	{
		DIPROPDWORD dipdw; 
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD); 
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		dipdw.diph.dwObj        = 0; 
		dipdw.diph.dwHow        = DIPH_DEVICE; 
		dipdw.dwData            = MOUSE_BUFFER_SIZE_DIRECTX;    

		hr = m_pDeviceMouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
		eRetVal = CHECKDXERROR( hr, F_SETPROPERTY );
	}
		
	//....mouse wheel granularity...
	if (eRetVal==RET_OK)
	{
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD); 
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		dipdw.diph.dwObj        = 8;
		dipdw.diph.dwHow        = DIPH_BYOFFSET;
		hr = m_pDeviceMouse->GetProperty( DIPROP_GRANULARITY, &dipdw.diph );
		if (hr==DIERR_OBJECTNOTFOUND)
			m_iGranZ = 1;
		else
		{
			eRetVal = CHECKDXERROR( hr, F_GETPROPERTY );
			m_iGranZ = LOWORD(dipdw.dwData);
		}
	}
				
	ASSERTM( eRetVal==RET_OK, ("There was a problem with keyboard or mouse initialization\n") );
		
	m_bInitialiced = true;
		
	return eRetVal;
}

//////////////////////////////////////////////////////////////////////////

void CLowInput::Reset()
{
	End();
	DXInit();
}


//////////////////////////////////////////////////////////////////////////

void CLowInput::Run()
{
	m_iNumEvents = 0;
	ReadKeyboard();
		
	if (m_bUsingMouse ) 
		ReadMouse();
				
	UpdateModsKey();        
		
	if (m_bHLBufferActive && m_iNumCharsInHLBuffer>0)
	{
		TEvent Event;
		Event.m_eEvent  = EV_HLBUFFER;
		AddEvent( Event );
	}
}

//////////////////////////////////////////////////////////////////////////
// tries to acquire, and returns an error if cant for any reason
// WARNING, does NOT return error if cant acquire for a normal reason like game not in focus,etc

ERetVal CLowInput::AcquireKeyboard()
{
	ERetVal RetVal = RET_ERR;
	if (m_pDeviceKeyboard)
	{
		HRESULT hr = m_pDeviceKeyboard->Acquire();
		if (hr==DIERR_INPUTLOST ||      // probably does not have focus
			hr==S_FALSE ||              // because is already acquired
			hr==DIERR_OTHERAPPHASPRIO)   // another program has it bloqued or something
			RetVal = RET_OK;
		else
			RetVal = CHECKDXERROR( hr, F_ACQUIRE );
	}
	return RetVal;
}


//////////////////////////////////////////////////////////////////////////
// tries to acquire, and returns an error if cant for any reason
// WARNING, does NOT return error if cant acquire for a normal reason like game not in focus,etc

ERetVal CLowInput::AcquireMouse()
{
	ERetVal RetVal = RET_ERR;
	if (m_pDeviceMouse)
	{
		HRESULT hr = m_pDeviceMouse->Acquire();
		if (hr==DIERR_INPUTLOST ||      // probably does not have focus
			hr==S_FALSE ||              // because is already acquired
			hr==DIERR_OTHERAPPHASPRIO)   // another program has it bloqued or something
			RetVal = RET_OK;
		else
			RetVal = CHECKDXERROR( hr, F_ACQUIRE );
	}
	return RetVal;
}


//////////////////////////////////////////////////////////////////////////

void CLowInput::ReadTKeyboard()
{
		//...clear "click" flag on all keys that had it
		for (int i=0; i<m_iNumKeysToCleanClick; i++)
			m_aKeysState[ m_aToCleanClick[i] ].m_bClick = false;
		m_iNumKeysToCleanClick = 0;        

		if (m_pDeviceKeyboard)
		{
			//....read data from direct input
			ERetVal eRetVal = RET_OK;
			AdquirirTeclado();
			static DIDEVICEOBJECTDATA Buffer[ KEYBOARD_BUFFER_SIZE_DIRECTX ];
			DWORD uNumItems = KEYBOARD_BUFFER_SIZE_DIRECTX;
			HRESULT hr = m_pDeviceKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), Buffer, &uNumItems, 0 );
			if (hr==DI_BUFFEROVERFLOW)
			{
				ASSERTM_ONCE( false, ( "CLowInput::ReadTeclado() -> The DirectX buffer for keyboard input has suffered an overflow. Change the define, caraculo" ));
			}
			else 
				if (hr==DIERR_NOTACQUIRED)
				{
					eRetVal = RET_ERR;   //...does not call CHECKDXERROR because this is normal, it can happen when the windows lose the focus
				}
				else
					eRetVal = CHECKDXERROR( hr, F_GETDEVICEDATA );
								
			if (m_bPendingKeyboardFlush && eRetVal==RET_OK)
			{
				KeyboardFlush();   // to make sure everything is cleared
				eRetVal = RET_ERR;
			}
								
								
			//...............read the buffer, one element each time.
			if (eRetVal==RET_OK)
			{
				for (uint i=0; i<uNumItems; i++)
				{
					uint uDXCode    = Buffer[i].dwOfs;
					bool bPressed   = ( Buffer[i].dwData & 0x80 ) != 0;
					EKey eKey       = m_KeysMgr.TransDXKeyboardToKey( uDXCode );
								
					if (bPressed) 
					{
						m_aKeysState[ eKey ].m_bClick       = true; 
						m_aKeysState[ eKey ].m_bHold        = true; 
						m_aKeysState[ eKey ].m_uTimePressed = Buffer[i].dwTimeStamp;
						m_aToCleanClick[ m_iNumKeysToCleanClick ] = eKey;
						m_iNumKeysToCleanClick++;
						if (m_KeysMgr.KeyIsBuffereable( eKey ))
							PushToBuffer( eKey );
					}
					else
						m_aKeysState[ eKey ].m_bHold    = false; 
										
					AddEventKey( eKey, Buffer[i].dwTimeStamp );                    
				}
			}            
	}
}    
		

//////////////////////////////////////////////////////////////////////////

void CLowInput::PushToBuffer( EKey _eKey )
{
	m_aBuffer[ m_uFirstFree ] = _eKey;
	m_uFirstFree++;
	m_uFirstFree %= KEYBOARD_BUFFER_SIZE;

	if (m_uFirstFree==m_uFirstFull) //...buffer is already full
	{ 
		m_uFirstFull++;          //...loses the oldest char
		m_uFirstFull %= KEYBOARD_BUFFER_SIZE;
	}
}


//////////////////////////////////////////////////////////////////////////
// returns the oldest key/button in the keyboard buffer
// true if there was actually something in the buffer

bool CLowInput::PopFromBuffer( EKey* _peKey )
{
	EKey eKeyRes = LT_NO_KEY;
	bool bKey = !IsBufferEmpty();
		
	if (bKey)
	{
		eKeyRes = m_aBuffer[ m_uFirstFull ];
		m_uFirstFull++;
		m_uFirstFull %= KEYBOARD_BUFFER_SIZE;
	}
	*_peKey = eKeyRes;
	return bKey;
}


//////////////////////////////////////////////////////////////////////////
// returns one of the currently kept pressed keys, if there is any

EKey CLowInput::GetAnyKeyKeptPressed()
{
	EKey eKey = LT_NO_KEY;
		
	for (int k=0; k<LT_NUM_KEYS && eKey==LT_NO_KEY; k++)
	{
		if (m_aKeysState[k].m_bHold)
			eKey = EKey(k);
	}
		
	return eKey;
}


//////////////////////////////////////////////////////////////////////////
// returns one of the currently pressed keys, if there is any (pressed as in pressed down and released)

EKey CLowInput::GetAnyKeyPressed()
{
	EKey eKey = LT_NO_KEY;

	for (int k=0; k<LT_NUM_KEYS && eKey==LT_NO_KEY; k++)
	{
		if (m_aKeysState[k].m_bClick)
			eKey = EKey(k);
	}
		
	return eKey;
}



//////////////////////////////////////////////////////////////////////////
/// calculates the value of the modskey (alt, shift, ctrl, etc ) 

void CLowInput::UpdateModsKey()
{
	int iMod = MO_NOTHING; 
		
	if (IsKeyKeptPressed( LT_LSHIFT ) || IsKeyKeptPressed( LT_RSHIFT ) )
		iMod = MO_SHIFT;
				
	if (IsKeyKeptPressed( LT_LCONTROL ) || IsKeyKeptPressed( LT_RCONTROL ) )
		iMod |= MO_CTRL;
				
	if (IsKeyKeptPressed( LT_ALT ))
		iMod |= MO_ALT;
				
	m_eModsKey = EModsKey( iMod );        
}


//////////////////////////////////////////////////////////////////////////
// returns true if the key has been pressed and the given keymods combination is pressed

bool CLowInput::IsKeyPressedAndMod ( EKey _eKey, EModsKey _eMod )
{
	return (m_eModsKey==_eMod) && IsKeyPressed( _eKey );
}       


//////////////////////////////////////////////////////////////////////////
// returns true if any of both keys is been pressed and the given keymods combination is pressed
//----------------------------------------------------------------------

bool CLowInput::IsDKeyPressedAndMod ( EKey _eKey1, EKey _eKey2, EModsKey _eMod )
{
	return IsKeyPressedAndMod( _eKey1, _eMod ) || IsKeyPressedAndMod( _eKey2, _eMod );
}       




//////////////////////////////////////////////////////////////////////////

bool CLowInput::IsKeyKeptPressedAndMod ( EKey _eKey, EModsKey _eMod )
{
	return (m_eModsKey==_eMod) && IsKeyKeptPressed( _eKey );
}       



//////////////////////////////////////////////////////////////////////////
// enables or disables mouse

void CLowInput::SetUsingMouse( bool bUsar )
{
	HRESULT hr;
		
	if (bUsar!=m_bUsingMouse)
	{
		//...
		if (m_bUsingMouse)
		{
			hr = m_pDeviceMouse->Unacquire();
			if (hr!=DI_NOEFFECT)
				CHECKDXERROR( hr, F_UNACQUIRE );
			m_bUsingMouse = false;
		}
		else //...
		{
			AdquirirMouse();
			m_bUsingMouse = true;
		}
				
		m_iMouseX = 0;
		m_iMouseY = 0;
		m_iMouseZ = 0;
	}
}


//////////////////////////////////////////////////////////////////////////

void CLowInput::ReadMouse()
{
	HRESULT hr;
		
	m_iMouseX = 0;
	m_iMouseY = 0;
	m_iMouseZ = 0;
		
	m_bStartPreDragging = false;
		
	//....read data from direct input
	if (m_pDeviceMouse)
	{
		ERetVal eRetVal = RET_OK;
		AcquireMouse();
		static DIDEVICEOBJECTDATA Buffer[ MOUSE_BUFFER_SIZE_DIRECTX ];
		DWORD uNumItems = MOUSE_BUFFER_SIZE_DIRECTX;
		hr = m_pDeviceMouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), Buffer, &uNumItems, 0 );
						
		if (eRetVal==RET_OK)
		{
			if (hr==DI_BUFFEROVERFLOW)
			{
				ASSERTM_ONCE( false, ("CLowInput::ReadTeclado() -> The DirectX buffer for mouse input has suffered an overflow. Change the define, carapedo" ));
			}
			else 
				if (hr==DIERR_NOTACQUIRED)
				{
					eRetVal = RET_ERR;   //...does not call CHECKDXERROR because this is normal, it can hapens when the windows does not have the focus
				}
				else
					eRetVal = CHECKDXERROR( hr, F_GETDEVICEDATA );
		}
		bool bMouseMoved = false;
				
		if (m_bPendingMouseFlush && eRetVal==RET_OK)
		{
			MouseFlush();    // to make sure everything is cleared
			eRetVal = RET_ERR;
		}
		
		//...............read the buffer, one element each time.
		if (eRetVal==RET_OK)
		{
			for (uint i=0; i<uNumItems; i++)
			{
				uint uDXCode    = Buffer[i].dwOfs;
								
				if (uDXCode==DIMOFS_X)  // mouse leftright
				{
					int iMove = int(Buffer[i].dwData);
					if (g_pD3DMgr->EstaEnFullScreen())
						iMove = int (iMove * g_pSetup->GetInfo().m_fMouseSpeed);
					m_iMouseX += iMove;
					CheckDrag( Buffer[i].dwTimeStamp, iMove );
					bMouseMoved = true;
				}
				else if (uDXCode==DIMOFS_Y)  // mouse updown
				{
					int iMove = int(Buffer[i].dwData);
//					if (g_pD3DMgr->EstaEnFullScreen())
//							iMove = int( iMove * g_pSetup->GetInfo().m_fMouseSpeed );
					m_iMouseY += iMove;
					CheckDrag( Buffer[i].dwTimeStamp, iMove );
					bMouseMoved = true;
				}
				else if (uDXCode==DIMOFS_Z)  //..mouse wheel
				{
					m_iMouseZ +=Buffer[i].dwData;
					TEvent Event;
					Event.m_eEvent  = EV_MOUSE_WHEEL;
					Event.m_iValue  = Buffer[i].dwData;
					AddEvent( Event );
				}
				else  //...is a button...
				{
					bool bPressed   = ( Buffer[i].dwData & 0x80 ) != 0;
					EKey eKey       = m_KeysMgr.TransDXMouseToKey( uDXCode );
										
					if (bPressed) 
					{
						m_aKeysState[ eKey ].m_bClick   = true; 
						m_aKeysState[ eKey ].m_bHold    = true; 
						m_aKeysState[ eKey ].m_uTimePressed = Buffer[i].dwTimeStamp;
						m_aToCleanClick[ m_iNumKeysToCleanClick ] = eKey;
						m_iNumKeysToCleanClick++;
						if (m_KeysMgr.KeyIsBuffereable( eKey ))
							MeterEnBuffer( eKey );
														
						//...check if should enter the pre-dragging mode (is in predragging mode until there is enough time with the key pressed)
						if (!m_bDragging)
						{
							m_eDragKey          = eKey;
							m_bPreDragging      = true;
							m_bStartPreDragging = true;
							m_iMouseMovePreDrag = 0;
						}
						AddEventKey( eKey, Buffer[i].dwTimeStamp );                    
					}
					else
					{
						bool bCanMakeKeyStroke = !m_bDragging;
						m_aKeysState[ eKey ].m_bHold    = false; 
						m_bDragging                     = false;
						m_bPreDragging                  = false;
												
						//....check doubleclick
						if (eKey==m_eLastMouseButton && Buffer[i].dwTimeStamp-m_uLastTimeClick<TIME_FOR_DOUBLECLICK)
						{
							TEvent Event;
							Event.m_eEvent  = EV_DOUBLE_CLICK;
							Event.m_eKey    = eKey;
							AddEvent( Event );
							m_eLastMouseButton = LT_NO_KEY;
						}
						else  //..when is not a doubleclick
						{
							AddEventKey( eKey, Buffer[i].dwTimeStamp, bCanMakeKeyStroke );
							m_eLastMouseButton  = eKey;                       // prepare in case next is a doubleclick
							m_uLastTimeClick    = Buffer[i].dwTimeStamp;      // same
						}
					}
				}
			}
						
			if (bMouseMoved)
			{
				TEvent Event;
				Event.m_eEvent  = EV_MOUSE_MOVE;
				AddEvent( Event );
			}
		}          
	}  
}    


//////////////////////////////////////////////////////////////////////////
// checks if can enter on drag mode, and if so, makes it so 

void CLowInput::CheckDrag( uint _uTimeStampMouseMove, uint _uMovement )
{
	if (m_bPreDragging)
	{
		int iMove = abs(int(_uMovement));
		m_iMouseMovePreDrag += iMove;
		if (_uTimeStampMouseMove-m_aKeysState[ m_eDragKey ].m_uTimePressed>TIME_FOR_DRAG ||
			m_iMouseMovePreDrag>=MOUSEMOVE_FOR_DRAG)
		{
			m_bPreDragging  = false;
			m_bDragging     = true;
		}
	}
}



//////////////////////////////////////////////////////////////////////////
// add a key event to the buffer event.

void CLowInput::AddEventKey( EKey _eKey, uint _uTimeStamp, bool _bCanMakeStroke )
{
	ASSERT( m_iNumEvents<SIZE_EVENTS_BUF );
	if (m_iNumEvents<SIZE_EVENTS_BUF)
	{
		TEvent Event;
		Event.m_eKey    = _eKey;
				
		if (m_aKeysState[ _eKey ].m_bHold)
			Event.m_eEvent  = EV_KEY_DOWN;
		else
			Event.m_eEvent      = EV_KEY_UP;

		AddEvent( Event );        
				
		//...when the key is relased, it can produce a EV_KEY_STROKE event also, if the time was short enough since the press-down
		if (Event.m_eEvent==EV_KEY_UP && _bCanMakeStroke)
		{
//            if (_uTimeStamp - m_aKeysState[ _eKey ].m_uTimePressed <= TIME_FOR_STROKE)
			{
				Event.m_eEvent  = EV_KEY_STROKE;
				AddEvent( Event );
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
// add a event to the buffer event.

void CLowInput::AddEvent( const TEvent& _Event )
{
	ASSERT( m_iNumEvents<SIZE_EVENTS_BUF );
	m_aEvents[ m_iNumEvents ] = _Event;
	m_iNumEvents++;
}



//////////////////////////////////////////////////////////////////////////
// sets mouse sensibility in X

void CLowInput::SetSensMouse( uint uSens )
{
	m_fSensMouse = float(uSens) / 50.f;
}


//////////////////////////////////////////////////////////////////////////
// is called when the game window gets the focus

void CLowInput::NotifyWindowSetFocus()
{
	if (m_bInitialiced)
	{
		m_bPendingKeyboardFlush = true;
		m_bPendingMouseFlush    = true;
		Flush();
	}
}


//////////////////////////////////////////////////////////////////////////
// is called when the game window lose the focus ( suposedly, is called always before the run )

void CLowInput::NotifyWindowLostFocus()
{
	m_bDragging         = false;
	m_bPreDragging      = false;
}



//////////////////////////////////////////////////////////////////////////
// read and discard all buffered input

void CLowInput::Flush()
{
	KeyboardFlush();
	MouseFlush();
}


//////////////////////////////////////////////////////////////////////////
// read and discard all keyboard buffered input

void CLowInput::KeyboardFlush()
{
	AcquireKeyboard();
	DWORD uNumItems = INFINITE;
	HRESULT hr = m_pDeviceKeyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), NULL, &uNumItems, 0 );
	if (hr==D3D_OK)
		m_bPendingKeyboardFlush = false;
	m_iNumKeysToCleanClick  = 0;
	for (int k=0; k<LT_NUM_KEYS; k++)
	{
		m_aKeysState[k].m_bClick    = false;    
		m_aKeysState[k].m_bHold     = false;
	}
}
		
//////////////////////////////////////////////////////////////////////////
// read and discard all mouse buffered input

void CLowInput::MouseFlush()
{
	AcquireMouse();
	DWORD uNumItems = INFINITE;
	HRESULT hr = m_pDeviceMouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), NULL, &uNumItems, 0 );
	if (hr==D3D_OK)
		m_bPendingMouseFlush = false;
}


//////////////////////////////////////////////////////////////////////////
// extract a char from the HLBuffer

byte CLowInput::GetCharFromHLBuffer()
{
	byte Char = 0;
	if (m_bHLBufferActive && m_iNumCharsInHLBuffer>0)
	{
		Char = m_aHLBuffer[0];
		m_iNumCharsInHLBuffer--;
		for (int i=0; i<m_iNumCharsInHLBuffer; i++)
			m_aHLBuffer[i] = m_aHLBuffer[i+1];
	}
		
	return Char;
}


//////////////////////////////////////////////////////////////////////////
// extract a char from the HLBuffer

void CLowInput::ActivateHLBuffer( bool _bAct )
{
	m_bHLBufferActive       = _bAct;
	m_iNumCharsInHLBuffer   = 0;
}
