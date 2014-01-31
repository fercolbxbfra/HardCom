//----------------------------------------------------------------------------
// language version management
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "Languages.h"
#include "Setup.h"
#include "Globals.h"

const char* st_apszFileSuffixes[ LA_NUM_LANGUAGES ]=
{
	"_EN",
	"_SP",
	"_GE",
	"_FR",
	"_IT",
};

const char* st_apszLang[ LA_NUM_LANGUAGES ]=
{
	"ENGLISH",
	"SPANISH",
	"GERMAN",
	"FRENCH",
	"ITALIAN"
};

const char* st_apszRegisterLang[ LA_NUM_LANGUAGES ]=
{
	"1033", //ENGLISH,
	"1034", //SPANISH,
	"1031", //GERMAN,
	"1036", //FRENCH,
	"1040", //ITALIAN
};



//////////////////////////////////////////////////////////////////////////

const char* GetLangFileSuffix( ELang _eLang )
{
	ASSERT( _eLang<LA_NUM_LANGUAGES );
		
	return st_apszFileSuffixes[ _eLang ];
}


//////////////////////////////////////////////////////////////////////////

const char* GetLangFileSuffix()
{
//	return GetLangFileSuffix( g_pSetup->GetInfoDev().m_eLang );
	return "EN";
}



//////////////////////////////////////////////////////////////////////////

ELang GetLang( const char* _pszLang )
{
	ELang eLang = LA_ENGLISH;
		
	for (int i=0; i<LA_NUM_LANGUAGES; i++)
	{
		if (IsEqualStringNoCase( _pszLang, st_apszLang[i] ))
		{
			eLang = ELang( i );
			break;
		}
	}
		
	return eLang;
}


//////////////////////////////////////////////////////////////////////////

ELang GetLangFromRegisterString( const char* _pszLang )
{
	ELang eLang = LA_ENGLISH;
		
	for (int i=0; i<LA_NUM_LANGUAGES; i++)
	{
		if (IsEqualStringNoCase( _pszLang, st_apszRegisterLang[i] ))
		{
			eLang = ELang( i );
			break;
		}
	}
		
	return eLang;
}
