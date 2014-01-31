//----------------------------------------------------------------------------
// Keys
//----------------------------------------------------------------------------


#pragma once

enum EModsKey 
{
	MO_NOTHING,
	MO_SHIFT        = 0x0001,
	MO_CTRL         = 0x0002,
	MO_ALT          = 0x0004,
		
	MO_SHIFT_ALT    = MO_SHIFT | MO_ALT,
	MO_SHIFT_CTRL   = MO_SHIFT | MO_CTRL,
	MO_ALT_CTRL     = MO_ALT | MO_CTRL,
};

#define NUM_DX_KEYBOARD_CODES    256    //...how many diferent key codes DX uses
#define NUM_DX_MOUSE_CODES       16     //...how many diferent button codes DX uses

struct TInfoKey
{
	char ascii;
	uint uDXCode;
	const char* pszDesc;
	bool bBuffereable;
};

//....order must bet exactly the same than the local codes in keys.cpp
//extern TInfoKey st_aInfoKeys[];


enum EKey
{
	LT_NO_KEY   = 0,
		
	LT_0,
	LT_1,
	LT_2,
	LT_3,
	LT_4,
	LT_5,
	LT_6,
	LT_7,
	LT_8,
	LT_9,
	LT_A,
	LT_ABNT_C1,
	LT_ABNT_C2,
	LT_ADD,                 // numpad add
	LT_APOSTROPHE,
	LT_APPS,
	LT_AT,
	LT_AX,
	LT_B,
	LT_BACK,
	LT_BACKSLASH,
	LT_C,
	LT_CALCULATOR,
	LT_CAPITAL,
	LT_COLON,
	LT_COMMA,
	LT_CONVERT,
	LT_D,
	LT_DECIMAL,
	LT_DELETE,
	LT_DIVIDE,
	LT_DOWN,
	LT_E,
	LT_END,
	LT_EQUALS,
	LT_ESCAPE,
	LT_F,
	LT_F1,
	LT_F2,
	LT_F3,
	LT_F4,
	LT_F5,
	LT_F6,
	LT_F7,
	LT_F8,
	LT_F9,
	LT_F10,
	LT_F11,
	LT_F12,
	LT_F13,
	LT_F14,
	LT_F15,
	LT_G,
	LT_GRAVE,
	LT_H,
	LT_HOME,
	LT_I,
	LT_INSERT,
	LT_J,
	LT_K,
	LT_KANA,
	LT_KANJI,
	LT_L,
	LT_LBRACKET,
	LT_LCONTROL,
	LT_LEFT,
	LT_LMENU,
	LT_LSHIFT,
	LT_LWIN,
	LT_M,
	LT_MAIL,
	LT_MEDIASELECT,
	LT_MEDIASTOP,
	LT_MINUS,
	LT_MULTIPLY,
	LT_MUTE,
	LT_MYCOMPUTER,
	LT_N,
	LT_NEXT,
	LT_NEXTTRACK,
	LT_NOCONVERT,
	LT_NUMLOCK,
	LT_NUMPAD0,
	LT_NUMPAD1,
	LT_NUMPAD2,
	LT_NUMPAD3,
	LT_NUMPAD4,
	LT_NUMPAD5,
	LT_NUMPAD6,
	LT_NUMPAD7,
	LT_NUMPAD8,
	LT_NUMPAD9,
	LT_NUMPADCOMMA,
	LT_NUMPADENTER,
	LT_NUMPADEQUALS,
	LT_O,
	LT_OEM_102,
	LT_P,
	LT_PAUSE,
	LT_PERIOD,
	LT_PLAYPAUSE,
	LT_POWER,
	LT_PREVTRACK,
	LT_PRIOR,
	LT_Q,
	LT_R,
	LT_RBRACKET,
	LT_RCONTROL,
	LT_RETURN,
	LT_RIGHT,
	LT_RMENU,
	LT_RSHIFT,
	LT_RWIN,
	LT_S,
	LT_SCROLL,
	LT_SEMICOLON,
	LT_SLASH,
	LT_SLEEP,
	LT_SPACE,
	LT_STOP,
	LT_SUBTRACT,                // numpad subtract
	LT_SYSRQ,
	LT_T,
	LT_TAB,
	LT_U,
	LT_UNDERLINE,
	LT_UNLABELED,
	LT_UP,
	LT_V,
	LT_VOLUMEDOWN,
	LT_VOLUMEUP,
	LT_W,
	LT_WAKE,
	LT_WEBBACK,
	LT_WEBFAVORITES,
	LT_WEBFORWARD,
	LT_WEBHOME,
	LT_WEBREFRESH,
	LT_WEBSEARCH,
	LT_WEBSTOP,
	LT_X,
	LT_Y,
	LT_YEN,
	LT_Z,
		
	LT_NUM_KEYS_KEYBOARD, //...is not a key, is to mark where the keyboard codes finish
		
	LT_BUTTON_1,    // Mouse left button
	LT_FIRST_MOUSE_BUTTON = LT_BUTTON_1, // Used internally for diferetiation (logically there is no differences between buttons and keys)
	LT_BUTTON_2,    // Mouse right button
	LT_BUTTON_3,    // Mouse wheel button
	LT_BUTTON_4,
	LT_BUTTON_5,
	LT_BUTTON_6,
	LT_BUTTON_7,
	LT_BUTTON_8,
	LT_LAST_MOUSE_BUTTON = LT_BUTTON_8,
		
	LT_NUM_KEYS,
		
		
	LT_ERROR = 255,   // No key, error code
		
	// Key synonyms
	LT_ESC      = LT_ESCAPE,
	LT_LALT     = LT_LMENU,
	LT_RALT     = LT_RMENU,
	LT_PGUP     = LT_PRIOR,
	LT_PGDOWN   = LT_NEXT,
	LT_CTRL     = LT_LCONTROL,
	LT_CUR_ARR  = LT_UP,
	LT_CUR_ABA  = LT_DOWN,
	LT_CUR_DER  = LT_RIGHT,
	LT_CUR_IZQ  = LT_LEFT,
	LT_CUR_UP   = LT_UP,
	LT_CUR_DOWN = LT_DOWN,
	LT_CUR_RIGHT= LT_RIGHT,
	LT_CUR_LEFT = LT_LEFT,
	LT_AVA_PAG  = LT_PGDOWN,
	LT_RET_PAG  = LT_PGUP,
	LT_INTRO    = LT_RETURN,
	LT_ENTER    = LT_RETURN,
	LT_ALT      = LT_LALT,
	LT_NUMPAD_ADD   = LT_ADD,
	LT_NUMPAD_SUB   = LT_SUBTRACT
};

//...those codes have to be less than 32, because they share buffer with normal characters
enum EEditKey
{
	EK_NONE,
		
	EK_RIGHT,
	EK_LEFT,
	EK_INS,
	EK_DEL,
	EK_BACK,
	EK_HOME,
	EK_END,
	EK_RETURN,
	EK_CANCEL,
};

// this class encapsulates all the management needed for the keys and mouse buttons, so the DInput_G can be more clean
class CKeysMgr
{
	public:
		
			void                        Init                    ();
				

			uint                        TransKeyToDX            ( EKey _eKey ) const;
			EKey                        TransDXKeyboardToKey    ( uint _uDXKeyCode ) const;
			EKey                        TransDXMouseToKey       ( uint _uDXButtonCode ) const;
			char                        KeyToAscii              ( EKey _eKey ) const;
			EKey                        NameToKey               ( const char* _pszName ) const;
			bool                        KeyIsBuffereable        ( EKey _eKey ) const;
			const char*                 GetKeyName              ( EKey _eKey ) const;
			const char*                 GetModifKeyName         ( EModsKey _eModifKey ) const;
				
	private:
		
			EKey                        m_aDXKeyboardToKey[NUM_DX_KEYBOARD_CODES];
			EKey                        m_aDXMouseToKey[NUM_DX_MOUSE_CODES];
				
			static TInfoKey             m_aInfoKeys[ LT_NUM_KEYS ];
};

//////////////////////////////////////////////////////////////////////////
// converts from game key code to dx key code

inline uint CKeysMgr::TransKeyToDX( EKey _eKey ) const
{
	ASSERT( _eKey<LT_NUM_KEYS_KEYBOARD );
	if (_eKey<LT_NUM_KEYS_KEYBOARD)
		return m_aInfoKeys[ _eKey ].uDXCode;
	else
		return m_aInfoKeys[ LT_ERROR ].uDXCode;
}    

//////////////////////////////////////////////////////////////////////////
// converts from dx key code into game key code

inline EKey CKeysMgr::TransDXKeyboardToKey( uint _uDXKeyCode ) const
{
	ASSERT( _uDXKeyCode<NUM_DX_KEYBOARD_CODES );
	ASSERT( m_aDXKeyboardToKey[ _uDXKeyCode ]!= NONE );
	return m_aDXKeyboardToKey[ _uDXKeyCode ];
}


//////////////////////////////////////////////////////////////////////////
// converts from dx key code into game key code

inline EKey CKeysMgr::TransDXMouseToKey( uint _uDXButtonCode ) const
{
	ASSERT( _uDXButtonCode<NUM_DX_MOUSE_CODES );
	ASSERT( m_aDXMouseToKey[ _uDXButtonCode ]!= NONE );
	return m_aDXMouseToKey[ _uDXButtonCode ];
}


//////////////////////////////////////////////////////////////////////////
// returns the ascii asociated with a game key code

inline char CKeysMgr::KeyToAscii ( EKey _eKey ) const
{
	ASSERT( _eKey<LT_NUM_KEYS );
	return m_aInfoKeys[_eKey].ascii;
}

//////////////////////////////////////////////////////////////////////////
// true if is a key that is added into the buffer

inline bool CKeysMgr::KeyIsBuffereable( EKey _eKey ) const
{
	if (_eKey==LT_ERROR) return false;
	ASSERT( _eKey<LT_NUM_KEYS );
	return m_aInfoKeys[ _eKey ].bBuffereable;
}


//////////////////////////////////////////////////////////////////////////

inline const char* CKeysMgr::GetKeyName( EKey _eKey ) const
{
	ASSERT( _eKey<LT_NUM_KEYS );
	return m_aInfoKeys[ _eKey ].pszDesc;
}


EEditKey VKeyToEditKey( int _VirtKey );
