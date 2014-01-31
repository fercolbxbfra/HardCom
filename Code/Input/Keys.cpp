//----------------------------------------------------------------------------
// Keys
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Keys.h"
#include <DInput.h>

//....order must bet exactly the same than the local codes in keys.h
TInfoKey CKeysMgr::m_aInfoKeys[LT_NUM_KEYS]=
{
	0  ,          255,                  "<NO_KEY>",                 false,
	'0',          DIK_0,                "0",                        true ,    
	'1',          DIK_1,                "1",                        true ,
	'2',          DIK_2,                "2",                        true ,
	'3',          DIK_3,                "3",                        true ,
	'4',          DIK_4,                "4",                        true ,
	'5',          DIK_5,                "5",                        true ,
	'6',          DIK_6,                "6",                        true ,
	'7',          DIK_7,                "7",                        true ,
	'8',          DIK_8,                "8",                        true ,
	'9',          DIK_9,                "9",                        true ,
	'a',          DIK_A,                "A",                        true ,
	0  ,          DIK_ABNT_C1,          "ABNT_C1",                  false,
	0  ,          DIK_ABNT_C2,          "ABNT_C2",                  false,
	'+',          DIK_ADD,              "ADD",                      true ,
	0  ,          DIK_APOSTROPHE,       "APOSTROPHE",               true ,
	0  ,          DIK_APPS,             "APPS",                     false,
	0  ,          DIK_AT,               "AT",                       false,
	0  ,          DIK_AX,               "AX",                       false,
	'b',          DIK_B,                "B",                        true ,
	0  ,          DIK_BACK,             "BACK",                     true ,
 '\\',          DIK_BACKSLASH,        "BACKSLASH",                true ,
	'c',          DIK_C,                "C",                        true ,
	0  ,          DIK_CALCULATOR,       "CALCULATOR",               false,
	0  ,          DIK_CAPITAL,          "CAPITAL",                  false,
	',',          DIK_COLON,            "COLON",                    true ,
	',',          DIK_COMMA,            "COMMA",                    true ,
	0  ,          DIK_CONVERT,          "CONVERT",                  false,
	'd',          DIK_D,                "D",                        true ,
	0  ,          DIK_DECIMAL,          "DECIMAL",                  true ,
	0  ,          DIK_DELETE,           "DELETE",                   true ,
	'/',          DIK_DIVIDE,           "DIVIDE",                   true ,
	0  ,          DIK_DOWN,             "DOWN",                     true ,
	'e',          DIK_E,                "E",                        true ,
	0  ,          DIK_END,              "END",                      true ,
	'=',          DIK_EQUALS,           "EQUALS",                   true ,
	0  ,          DIK_ESCAPE,           "ESCAPE",                   true ,
	'f',          DIK_F,                "F",                        true ,
	0  ,          DIK_F1,               "F1",                       true ,
	0  ,          DIK_F2,               "F2",                       true ,
	0  ,          DIK_F3,               "F3",                       true ,
	0  ,          DIK_F4,               "F4",                       true ,
	0  ,          DIK_F5,               "F5",                       true ,
	0  ,          DIK_F6,               "F6",                       true ,
	0  ,          DIK_F7,               "F7",                       true ,
	0  ,          DIK_F8,               "F8",                       true ,
	0  ,          DIK_F9,               "F9",                       true ,
	0  ,          DIK_F10,              "F10",                      true ,
	0  ,          DIK_F11,              "F11",                      true ,
	0  ,          DIK_F12,              "F12",                      true ,
	0  ,          DIK_F13,              "F13",                      true ,
	0  ,          DIK_F14,              "F14",                      true ,
	0  ,          DIK_F15,              "F15",                      true ,
	'g',          DIK_G,                "G",                        true ,
	0  ,          DIK_GRAVE,            "GRAVE",                    false,
	'h',          DIK_H,                "H",                        true ,
	0  ,          DIK_HOME,             "HOME",                     true ,
	'i',          DIK_I,                "I",                        true ,
	0  ,          DIK_INSERT,           "INSERT",                   true ,
	'j',          DIK_J,                "J",                        true ,
	'k',          DIK_K,                "K",                        true ,
	0  ,          DIK_KANA,             "KANA",                     false,
	0  ,          DIK_KANJI,            "KANJI",                    false,
	'l',          DIK_L,                "L",                        true ,
	'[',          DIK_LBRACKET,         "LBRACKET",                 true ,
	0  ,          DIK_LCONTROL,         "LCONTROL",                 false,
	0  ,          DIK_LEFT,             "LEFT",                     true ,
	0  ,          DIK_LMENU,            "LALT",                     false,
	0  ,          DIK_LSHIFT,           "LSHIFT",                   false,
	0  ,          DIK_LWIN,             "LWIN",                     false,
	'm',          DIK_M,                "M",                        true ,
	0  ,          DIK_MAIL,             "MAIL",                     false,
	0  ,          DIK_MEDIASELECT,      "MEDIASELECT",              false,
	0  ,          DIK_MEDIASTOP,        "MEDIASTOP",                false,
	'-',          DIK_MINUS,            "MINUS",                    true ,
	'*',          DIK_MULTIPLY,         "MULTIPLY",                 true ,
	0  ,          DIK_MUTE,             "MUTE",                     false,
	0  ,          DIK_MYCOMPUTER,       "MYCOMPUTER",               false,
	'n',          DIK_N,                "N",                        true ,
	0  ,          DIK_NEXT,             "PGDOWN",                   true ,
	0  ,          DIK_NEXTTRACK,        "NEXTTRACK",                false,
	0  ,          DIK_NOCONVERT,        "NOCONVERT",                false,
	0  ,          DIK_NUMLOCK,          "NUMLOCK",                  false,
	0  ,          DIK_NUMPAD0,          "NUMPAD0",                  true ,
	0  ,          DIK_NUMPAD1,          "NUMPAD1",                  true ,
	0  ,          DIK_NUMPAD2,          "NUMPAD2",                  true ,
	0  ,          DIK_NUMPAD3,          "NUMPAD3",                  true ,
	0  ,          DIK_NUMPAD4,          "NUMPAD4",                  true ,
	0  ,          DIK_NUMPAD5,          "NUMPAD5",                  true ,
	0  ,          DIK_NUMPAD6,          "NUMPAD6",                  true ,
	0  ,          DIK_NUMPAD7,          "NUMPAD7",                  true ,
	0  ,          DIK_NUMPAD8,          "NUMPAD8",                  true ,
	0  ,          DIK_NUMPAD9,          "NUMPAD9",                  true ,
	0  ,          DIK_NUMPADCOMMA,      "NUMPADCOMMA",              true ,
	0  ,          DIK_NUMPADENTER,      "NUMPADENTER",              true ,
	0  ,          DIK_NUMPADEQUALS,     "NUMPADEQUALS",             true ,
	'o',          DIK_O,                "O",                        true ,
	0  ,          DIK_OEM_102,          "OEM_102",                  true ,
	'p',          DIK_P,                "P",                        true ,
	0  ,          DIK_PAUSE,            "PAUSE",                    false,
	'.',          DIK_PERIOD,           "PERIOD",                   true ,
	0  ,          DIK_PLAYPAUSE,        "PLAYPAUSE",                false,
	0  ,          DIK_POWER,            "POWER",                    false,
	0  ,          DIK_PREVTRACK,        "PREVTRACK",                false,
	0  ,          DIK_PRIOR,            "PGUP",                     true ,
	'q',          DIK_Q,                "Q",                        true ,
	'r',          DIK_R,                "R",                        true ,
	']',          DIK_RBRACKET,         "RBRACKET",                 true ,
	0  ,          DIK_RCONTROL,         "RCONTROL",                 false,
	0  ,          DIK_RETURN,           "RETURN",                   true ,
	0  ,          DIK_RIGHT,            "RIGHT",                    true ,
	0  ,          DIK_RMENU,            "RMENU",                    true ,
	0  ,          DIK_RSHIFT,           "RSHIFT",                   false,
	0  ,          DIK_RWIN,             "RWIN",                     false,
	's',          DIK_S,                "S",                        true ,
	0  ,          DIK_SCROLL,           "SCROLL",                   true ,
	';',          DIK_SEMICOLON,        "SEMICOLON",                true ,
	'/',          DIK_SLASH,            "SLASH",                    true ,
	0  ,          DIK_SLEEP,            "SLEEP",                    false,
	' ',          DIK_SPACE,            "SPACE",                    true ,
	0  ,          DIK_STOP,             "STOP",                     false,
	'-',          DIK_SUBTRACT,         "SUBTRACT",                 true ,
	0  ,          DIK_SYSRQ,            "SYSRQ",                    false,
	't',          DIK_T,                "T",                        true ,
	0  ,          DIK_TAB,              "TAB",                      true ,
	'u',          DIK_U,                "U",                        true ,
	'_',          DIK_UNDERLINE,        "UNDERLINE",                true ,
	0  ,          DIK_UNLABELED,        "UNLABELED",                true ,
	0  ,          DIK_UP,               "UP",                       true ,
	'v',          DIK_V,                "V",                        true ,
	0  ,          DIK_VOLUMEDOWN,       "VOLUMEDOWN",               false,
	0  ,          DIK_VOLUMEUP,         "VOLUMEUP",                 false,
	'w',          DIK_W,                "W",                        true ,
	0  ,          DIK_WAKE,             "WAKE",                     false,
	0  ,          DIK_WEBBACK,          "WEBBACK",                  false,
	0  ,          DIK_WEBFAVORITES,     "WEBFAVORITES",             false,
	0  ,          DIK_WEBFORWARD,       "WEBFORWARD",               false,
	0  ,          DIK_WEBHOME,          "WEBHOME",                  false,
	0  ,          DIK_WEBREFRESH,       "WEBREFRESH",               false,
	0  ,          DIK_WEBSEARCH,        "WEBSEARCH",                false,
	0  ,          DIK_WEBSTOP,          "WEBSTOP",                  false,
	'x',          DIK_X,                "X",                        true ,
	'y',          DIK_Y,                "Y",                        true ,
	0  ,          DIK_YEN,              "YEN",                      true ,
	'z',          DIK_Z,                "Z",                        true ,
	
	0,            255,                  "------",                   false,  //...space to fill the LT_NUM_KEYS_KEYBOARD spot
																																	
	// Mouse buttons
	0  ,          DIMOFS_BUTTON0,       "BUTTON_1",                 true ,
	0  ,          DIMOFS_BUTTON1,       "BUTTON_2",                 true ,
	0  ,          DIMOFS_BUTTON2,       "BUTTON_3",                 true ,
	0  ,          DIMOFS_BUTTON3,       "BUTTON_4",                 true ,
	0  ,          DIMOFS_BUTTON4,       "BUTTON_5",                 true ,
	0  ,          DIMOFS_BUTTON5,       "BUTTON_6",                 true ,
	0  ,          DIMOFS_BUTTON6,       "BUTTON_7",                 true ,
	0  ,          DIMOFS_BUTTON7,       "BUTTON_8",                 true ,
};    

//...used to translate from windows's VirtualKeys to EEditKey
struct TVKeyToEditKey
{
	int         m_VirtKey;
	EEditKey    m_eEditKey;
};

TVKeyToEditKey   st_KeyToEditKey[]=
{
	{ VK_RIGHT,     EK_RIGHT    },
	{ VK_LEFT,      EK_LEFT     },
	{ VK_BACK,      EK_BACK     },
	{ VK_END,       EK_END      },
	{ VK_HOME,      EK_HOME     },
	{ VK_INSERT,    EK_INS      },
	{ VK_DELETE,    EK_DEL      },
	{ VK_RETURN,    EK_RETURN   },
	{ VK_ESCAPE,    EK_CANCEL   },
};


//////////////////////////////////////////////////////////////////////////

void CKeysMgr::Init()
{
	// initialices the array used to translate DX codes into LT codes
	for (int i=0; i<NUM_DX_KEYBOARD_CODES; i++)
			m_aDXKeyboardToKey[i] = EKey(NONE);

	for (int i=0; i<NUM_DX_KEYBOARD_CODES; i++)
			m_aDXMouseToKey[i] = EKey(NONE);

	for (int k=0; k<LT_NUM_KEYS_KEYBOARD; k++)
			m_aDXKeyboardToKey[ m_aInfoKeys[k].uDXCode ] = EKey(k);
		
	for (int b=LT_FIRST_MOUSE_BUTTON; b<=LT_LAST_MOUSE_BUTTON; b++)
			m_aDXMouseToKey[ m_aInfoKeys[b].uDXCode ] = EKey(b);
	
};


//////////////////////////////////////////////////////////////////////////

EKey CKeysMgr::NameToKey( const char* _pszName ) const
{
	EKey eKey = LT_ERROR;
		
	if (_pszName)
	{
		for (uint c=0; c<LT_NUM_KEYS && eKey==LT_ERROR; c++)
		{
			if (IsEqualString( _pszName, m_aInfoKeys[c].pszDesc ))
				eKey = EKey(c);
		}
	}
		
	if (eKey==LT_ERROR)
	{
		LOG(("ERR: cant find the key: %s", _pszName ));
	}
	return eKey;
}


//////////////////////////////////////////////////////////////////////////

const char* CKeysMgr::GetModifKeyName ( EModsKey _eModifKey ) const
{
	switch ( _eModifKey )
	{
		case MO_NOTHING:
			return "";
						
		case MO_SHIFT:
			return "SHIFT";
						
		case MO_CTRL:
			return "CTRL";
						
		case MO_ALT:
			return "ALT";
						
		case MO_SHIFT_ALT:
			return "SHIFT+ALT";
						
		case MO_SHIFT_CTRL:
			return "SHIFT+CTRL";
						
		case MO_ALT_CTRL:
			return "CTRL+ALT";
						
		default:
			return "UNKNOWN";
	}
}


//////////////////////////////////////////////////////////////////////////

EEditKey VKeyToEditKey( int _VirtKey )
{
	EEditKey eEdit = EK_NONE;
		
	for (int i=0; i<SIZE_ARRAY(st_KeyToEditKey) && eEdit==EK_NONE; i++)
	{
		if (st_KeyToEditKey[i].m_VirtKey==_VirtKey)
			eEdit = st_KeyToEditKey[i].m_eEditKey;
	}

	return eEdit;
}
