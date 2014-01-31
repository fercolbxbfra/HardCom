//----------------------------------------------------------------------------
// language version management
//----------------------------------------------------------------------------

#pragma once

enum ELang
{
	LA_ENGLISH,
	LA_SPANISH,
	LA_GERMAN,
	LA_FRENCH,
	LA_ITALIAN,
		
	LA_NUM_LANGUAGES,
	LA_UNKNOWN  = INVALID_INT
};

const char*         GetLangFileSuffix           ( ELang _eLang );
const char*         GetLangFileSuffix           ();
ELang               GetLang                     ( const char* _pszLang );
ELang               GetLangFromRegisterString   ( const char* _pszLang );