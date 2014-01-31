//----------------------------------------------------------------------------
// constant valus used for the filesystem
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "ConstFiles.h"

//..used to convert directory defines into strings
#define MACLINE( Dir, eDir ) #Dir, eDir, Dir,

struct 
{
	const char*     m_pszNameDir;  
	EDir            m_eDir;
	const char*     m_pszDir;
} st_aDir[NUM_EDIRS] = 
{
	MACLINE( DIR_DATA,                  EDIR_DATA )
	MACLINE( DIR_LOGS,                  EDIR_LOGS )
	MACLINE( DIR_FONTS,                 EDIR_FONTS )
	MACLINE( DIR_GRAPHICS,              EDIR_GRAPHICS )
	MACLINE( DIR_INTERFACE,             EDIR_INTERFACE )
	MACLINE( DIR_INTERFACE_GRAPHICS,    EDIR_INTERFACE_GRAPHICS )
	MACLINE( DIR_3DMODELS,              EDIR_3DMODELS )
	MACLINE( DIR_MUSIC,                 EDIR_MUSIC )
	MACLINE( DIR_OUTPUT,                EDIR_OUTPUT )
	MACLINE( DIR_PARTICLES,             EDIR_PARTICLES )
	MACLINE( DIR_SOUNDFX,               EDIR_SOUNDFX )
	MACLINE( DIR_SHADERS,               EDIR_SHADERS )
	MACLINE( DIR_SPRITES,               EDIR_SPRITES )
	MACLINE( DIR_VIDEOS,                EDIR_VIDEOS )
	MACLINE( DIR_WORLD,                 EDIR_WORLD )
	MACLINE( DIR_TEXT,                  EDIR_TEXT )
	MACLINE( DIR_CURSORS,               EDIR_CURSORS )
		
	//...
		
	MACLINE( DIR_DATAWORK,              EDIR_DATAWORK )
	MACLINE( DIR_DW_INTERFACE,          EDIR_DW_INTERFACE )
	MACLINE( DIR_DW_PARTICLES,          EDIR_DW_PARTICLES )
	MACLINE( DIR_DW_SPRITES,            EDIR_DW_SPRITES )
};
		
		
//////////////////////////////////////////////////////////////////////////
// from a directory name (ie "DIR_DATA", "DIR_SETUP", etc), returns the real directory path (ie "DATA/SETUP/" )
//----------------------------------------------------------------------
		
const char* GetDirFromName( const char* _pszName )
{
	const char* _pszDir = NULL;
		
	for (int i=0; i<NUM_EDIRS; i++)
	{
		if (IsEqualStringNoCase( _pszName, st_aDir[i].m_pszNameDir ))
			_pszDir = st_aDir[i].m_pszDir;
	}

	if (!_pszDir)
	{
		LOG(("Cant find directory with the internal name: '%s'", _pszName ));
	}
						
	return _pszDir;
}
		