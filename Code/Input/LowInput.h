//----------------------------------------------------------------------------
// CLowInput
//----------------------------------------------------------------------------


#pragma once

struct IDirectInput8A;
struct IDirectInputDevice8A;

#include "Keys.h"

class CLowInput
{
	public:
		
			enum EEvent
			{
					//..the usual key press or button click event is EV_KEY_STROKE. EV_KEY_DOWN is produced in the exact moment
					//...when the key is pressed down, while EV_KEY_STROKE represents a normal cycle of press-release. 
					//...so, use EV_KEY_STROKE unless you really want to check when the key has been pushed down
				
					EV_KEY_DOWN,        ///> when the key/button is pressed down
					EV_KEY_UP,          ///> when the key/button is released
					EV_KEY_STROKE,      ///> when a key has been "pulsed".
					EV_HLBUFFER,        ///> sent when there are chars in the HLBuffer
					EV_MOUSE_MOVE,
					EV_MOUSE_WHEEL,
					EV_DOUBLE_CLICK,     ///> only for mouse buttons, when there is a second click fast after a first one.
															///> with the first click, there is the standard EV_KEY_UP, EV_KEY_DOWN, EV_KEY_STROKE
															///> for the second click, only EV_DOUBLE_CLICK is sent
			};
		
			struct TEvent
			{
					EEvent      m_eEvent;
					EKey        m_eKey;     ///< only used for some events
					int         m_iValue;   ///< only used for some events
			};


	public:
			
																	CLowInput               ();
																	~CLowInput              () { End(); }
			void                        WinInit                 ( uint hInst, uint hWnd );
			void                        Reset                   ();

			void                        Run                     ();
				
			bool                        IsKeyKeptPressed        ( EKey _EKey );
			bool                        IsKeyPressed            ( EKey _EKey );
			EKey                        GetKeyFromBuffer        () { EKey EKey = LT_NO_KEY; PopFromBuffer( &EKey ); return EKey;  }
			void                        FlushBuffer             () { m_uFirstFree = m_uFirstFull = 0; }
			bool                        IsBufferEmpty           () { return m_uFirstFree==m_uFirstFull; }

			uint                        GetHInst                () { return m_hInst; }
			EKey                        GetAnyKeyKeptPressed    ();
			EKey                        GetAnyKeyPressed        ();
				
			bool                        IsKeyPressedAndMod      ( EKey _eKey, EModsKey _eMod = MO_NOTHING );
			bool                        IsDKeyPressedAndMod     ( EKey _eKey1, EKey _eKey2, EModsKey _eMod = MO_NOTHING );
			bool                        IsKeyKeptPressedAndMod  ( EKey _eKey, EModsKey _eMod = MO_NOTHING );
			EModsKey                    GetModsKeyState         () { return m_eModsKey; }
								
			void                        SetUsingMouse           ( bool bUse );
			int                         GetMouseX               () { return m_iMouseX; }
			int                         GetMouseY               () { return m_iMouseY; }
			int                         GetMouseZ               () { return m_iMouseZ / m_iGranZ; }
			int                         WheelInc2Clicks         ( int _iWheelInc ) { return _iWheelInc / m_iGranZ; }
			void                        SetSensMouse            ( uint uSens );
			TEvent*                     GetEventsBuf            () { return m_aEvents; }
			int                         GetNumEvents            () { return m_iNumEvents; }
				
			const CKeysMgr&             GetKeysMgr              () { return m_KeysMgr; }
			bool                        IsDragging              () { return m_bDragging; }
			bool                        IsPreDragging           () { return m_bPreDragging; }
			bool                        IsStartPreDragging      () { return m_bStartPreDragging; }
			EKey                        GetDragKey              () { return m_eDragKey; }
			void                        NotifyWindowSetFocus    ();
			void                        NotifyWindowLostFocus   ();
			void                        Flush                   ();
				
			//....the high lvl (HL) buffer is the buffer of chars generated by window processed WM_CHAR msgs
			void                        ActivateHLBuffer        ( bool _bAct );
			byte                        GetCharFromHLBuffer     ();
			void                        AddCharToHLBuffer       ( byte _Char );                       
			void                        AddVKeyToHLBuffer       ( int _VirtKey );


	private:

			void                        End                     ();
			ERetVal                     DXInit                  ();
			void                        ReadKeyboard            ();
			ERetVal                     AcquireKeyboard         ();        
			void                        PushToBuffer            ( EKey _EKey );
			bool                        PopFromBuffer           ( EKey* _pEKey );
				
			ERetVal                     AcquireMouse            ();
			void                        ReadMouse               ();
			void                        AddEventKey             ( EKey _eKey, uint _uTimeStamp, bool _bCanMakeStroke = true );
			void                        AddEvent                ( const TEvent& _Event );
			void                        UpdateModsKey           ();
			void                        CheckDrag               ( uint _uTimeStampMouseMove, uint _uMovement );
			void                        KeyboardFlush           ();
			void                        MouseFlush              ();
				
		

	private:

			enum { KEYBOARD_BUFFER_SIZE = 1024 };
			enum { SIZE_EVENTS_BUF = 256 };
			enum { SIZE_HLBUFFER = 1024 };
		
		
			uint                        m_hInst;
			uint                        m_hWnd;
			IDirectInput8A*             m_pDirectInput;
			IDirectInputDevice8A*       m_pDeviceKeyboard;
				
			struct TInfoKey
			{
				uint    m_uTimePressed; ///< DX time stamp value for when the key was pressed. Is used for to know if a release of the key should produce a EV_PULSE. OJO, this time value is NOT related to any of the timers in the rest of the program.
				bool    m_bClick;       // true if it has been pressed in this tick. It gets cleared before next tick
				bool    m_bHold;        // true if it is being kept pressed, even if the action of press happened time ago. 
			}                           m_aKeysState[ LT_NUM_KEYS ];
			EKey                        m_aToCleanClick[ LT_NUM_KEYS ]; ///< every time a key is pressed, it is added to this array, so the "click" flag can be erased before next tick
			int                         m_iNumKeysToCleanClick;

			CKeysMgr                    m_KeysMgr;
				
			EKey                        m_aBuffer[ KEYBOARD_BUFFER_SIZE ];
			uint                        m_uFirstFree;  //...to manage the keyboard circular buffer
			uint                        m_uFirstFull;  // if m_uPrimFree==m_uPrimFull -> empty buffer
			EModsKey                    m_eModsKey;  ///< actual modkey state. It is used for all key clicks on every tick, wich is not totally accurate
				
			bool                        m_bUsingMouse;
			IDirectInputDevice8A*       m_pDeviceMouse;
				
			bool                        m_bPendingKeyboardFlush;
			bool                        m_bPendingMouseFlush;
				
			//...this buffer is cleared before each run. is NOT the same than m_aBuffer, wich is a basically ascii buffer and the keys
			//...stay there until is a flush or they are requested
			TEvent                      m_aEvents[ SIZE_EVENTS_BUF ];  //..events produced in this run
			int                         m_iNumEvents;
				
			/// those axys values have only how much the mouse has moved in this tick
			int                         m_iMouseX;
			int                         m_iMouseY;
			int                         m_iMouseZ;
			int                         m_iGranZ;
				
			float                       m_fSensMouse;
				
			EKey                        m_eLastMouseButton;  //..to control the double click, it has the last button clicked
			uint                        m_uLastTimeClick;    //..to control the double click, it has when last mouse button was pressed,

			//....for mouse drag        
			EKey                        m_eDragKey;  ///< key that is causing the mouse drag (one of the 3 mouse buttons)
			bool                        m_bDragging;
			bool                        m_bPreDragging;   ///< is predragging until the key is enough time pressed down to assure it was not a click
			bool                        m_bStartPreDragging; ///< only true the same frame that starts predragging
			int                         m_iMouseMovePreDrag; ///< for to account how much the omuse is moving while in predrag mode, to see if can enter in drag mode before the stroke time limit
				
			//..for the HLbuffer  (this is a separate buffer for characters processed by windows msgs, more suited for text input than the normal buffer)        
			byte                        m_aHLBuffer[ SIZE_HLBUFFER ];
			int                         m_iNumCharsInHLBuffer;
			bool                        m_bHLBufferActive;
				
			bool                        m_bInitialiced;
};




//////////////////////////////////////////////////////////////////////////
/// returns true while the key is pressed

inline bool CLowInput::IsKeyKeptPressed( EKey _eKey )
{
	if (_eKey>=LT_NUM_KEYS) return false;
		
	return m_aKeysState[ _eKey ].m_bHold;
}


//////////////////////////////////////////////////////////////////////////
/// true only if the key has been pressed in this tick

inline bool CLowInput::IsKeyPressed( EKey _eKey )
{
	if (_eKey>=LT_NUM_KEYS) return false;

	return m_aKeysState[ _eKey ].m_bClick;
}


//////////////////////////////////////////////////////////////////////////
// adds a char to the HLBuffer. Usually used only from the main window procedure

inline void CLowInput::AddCharToHLBuffer( byte _Char )
{
	if (m_bHLBufferActive && m_iNumCharsInHLBuffer<SIZE_HLBUFFER && _Char>=' ')
	{
		m_aHLBuffer[ m_iNumCharsInHLBuffer ] = _Char;
		m_iNumCharsInHLBuffer++;
	}
}



//////////////////////////////////////////////////////////////////////////
// adds a virtual key to the HLBuffer. Only does really add keys that are translated into editing keys. Usually used only from the main window procedure

inline void CLowInput::AddVKeyToHLBuffer( int _VirtKey )
{
	if (m_bHLBufferActive && m_iNumCharsInHLBuffer<SIZE_HLBUFFER)
	{
		EEditKey eEdit = VKeyToEditKey( _VirtKey );
		if (eEdit!=EK_NONE)
		{
			m_aHLBuffer[ m_iNumCharsInHLBuffer ] = eEdit;
			m_iNumCharsInHLBuffer++;
		}
	}
}
