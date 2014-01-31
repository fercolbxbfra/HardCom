//----------------------------------------------------------------------------
// constant valus used for the filesystem
//----------------------------------------------------------------------------

#pragma once

#define MAX_FILENAME_SIZE 256

#define PACK_FILENAME       "DATA.PACK"

// Directories
#define DIR_ROOT                    "./"
#define DIR_DATA                    "DATA/"
#define DIR_SAVED_GAMES             "SAVED_GAMES/"
#define DIR_LOGS                    "LOGS/"
#define DIR_OUTPUT                  "OUTPUT/"

#define DIR_GRAPHICS                DIR_DATA "GRAPHICS/"
#define DIR_INTERFACE               DIR_DATA "INTERFACE/"
#define DIR_SOUND                   DIR_DATA "SOUND/"
#define DIR_SCRIPTS                 DIR_DATA "SCRIPTS/"
#define DIR_SHADERS                 DIR_DATA "SHADERS/"
#define DIR_WORLD                   DIR_DATA "WORLD/"
#define DIR_VIDEOS                  DIR_DATA "VIDEOS/"
#define DIR_TEXT                    DIR_DATA "TEXT/"
#define DIR_SETUP                   DIR_DATA "SETUP/"   

#define DIR_TERRAIN                 DIR_WORLD "TERRAIN/"
#define DIR_MUSIC                   DIR_SOUND "MUSIC/"
#define DIR_SOUNDFX                 DIR_SOUND "FX/"
#define DIR_SCRIPTS_PARTICLES       DIR_SCRIPTS "PARTICLES/"

#define DIR_TERRAIN_GRAPHICS        DIR_GRAPHICS "TERRAIN/"
#define DIR_CURSORS                 DIR_GRAPHICS "CURSORS/"
#define DIR_FONTS                   DIR_GRAPHICS "FONTS/"
#define DIR_INTERFACE_GRAPHICS      DIR_GRAPHICS "INTERFACE/"
#define DIR_3DMODELS                DIR_GRAPHICS "3DMODELS/"
#define DIR_PARTICLES               DIR_GRAPHICS "PARTICLES/"
#define DIR_SPRITES                 DIR_GRAPHICS "SPRITES/"
#define DIR_TEXBLOCKS               DIR_GRAPHICS "TEXBLOCKS/"
#define DIR_3DMODELS                DIR_GRAPHICS "3DMODELS/"
#define DIR_DECALS                  DIR_GRAPHICS "DECALS/"


// Extra directories (not used in the game)
// only for stuff that is used from the game for developping reasons
#define DIR_DATAWORK                "../DATA WORK/"
#define DIR_DW_GRAPHICS             DIR_DATAWORK    "GRAPHICS/"
#define DIR_DW_INTERFACE            DIR_DW_GRAPHICS "INTERFACE/"
#define DIR_DW_PARTICLES            DIR_DW_GRAPHICS "PARTICLES/"
#define DIR_DW_SPRITES              DIR_DW_GRAPHICS "SPRITES/"
#define DIR_DW_GRTERRAIN            DIR_DW_GRAPHICS "TERRAIN/"
#define DIR_DW_GRTERRAIN_TEX        DIR_DW_GRTERRAIN "TEX/"
#define DIR_DW_TERRAIN              DIR_DATAWORK    "WORLD/TERRAIN/"


// Extensions
#define EXT_ANIM_FILE               ".ANIM"
#define EXT_DAT_FILE                ".DAT"
#define EXT_DTB_FILE                ".DTB"
#define EXT_MODEL_FILE              ".MODEL"
#define EXT_TERRAIN_FILE            ".TRN"
#define EXT_TERRAIN_FINAL_FILE      ".TRNF"
#define EXT_TEXBLOCK_FILE           ".TBK"   // binart file with the extra information needed for each TexBlock
#define EXT_DDS_FILE                ".DDS"   //..DirectX DDS
#define EXT_BATTLE_FILE             ".BAT"
#define EXT_CSV_FILE                ".CSV"  // exported from Excel
#define EXT_BACKUP_FILE              ".BAK"


// File names
#define EXTERNAL_LOG_PROGRAM        "LogViewer.exe"
#define LOADINGSCREEN_FILE          "LoadingScreen" EXT_DAT_FILE
#define PINKY_BITMAP                DIR_GRAPHICS "PINKY.BMP"
#define STRINGS_FILE                "Strings"       EXT_DTB_FILE
#define TRANSLATED_STRINGS_FILE     "TranslatedStrings" EXT_CSV_FILE
#define CURSORS_FILE                "Cursors"       EXT_DTB_FILE
#define TESTMODEL_DIR               "_TestModel"
#define CLIPBOARD_FILE              "Clipboard"     ".txt"
#define SETTINGS_FILE               "Settings"      EXT_DAT_FILE
#define DETAILED_LOG_FILE           "DetailedLog"  ".txt"
#define SETUPDEV_FILE               "SetupDev"          EXT_DTB_FILE
#define SETUP_FILE                  "Setup"             EXT_DTB_FILE

// Templates
#define GRAPHICSITF_TEMPLATE        "ITF_%s"        EXT_DTB_FILE
#define TEXBLOCK_LTX_TEMPLATE       "LTX_%s"        EXT_DTB_FILE     // file listing all the textures used in a texblock
#define PARTICLESYS_TEMPLATE        "PSYS_%s"       EXT_DTB_FILE


// Usable directory names from scripts and similar
// NOTE: The order can be different and is not needed to include all directories
enum EDir
{
		EDIR_CURSORS,
		EDIR_DATA,   
		EDIR_LOGS,
		EDIR_FONTS,
		EDIR_GRAPHICS,
		EDIR_INTERFACE,
		EDIR_INTERFACE_GRAPHICS,
		EDIR_MAPS,
		EDIR_3DMODELS,
		EDIR_MUSIC,
		EDIR_OUTPUT,
		EDIR_PARTICLES,
		EDIR_SOUNDFX,
		EDIR_SHADERS,
		EDIR_SPRITES,
		EDIR_VIDEOS,
		EDIR_WORLD,
		EDIR_TEXT,
		
		// Data work
		EDIR_DATAWORK,
		EDIR_DW_INTERFACE,
		EDIR_DW_PARTICLES,
		EDIR_DW_SPRITES,
		
		NUM_EDIRS
};

const char* GetDirFromName( const char* _pszName );


// Macro to create a filename from a dir + filename
#define MAKE_FILENAME( Dir, FileName )                                  \
				char szFullFileName[ MAX_FILENAME_SIZE ];                       \
				CopyString( szFullFileName, sizeof(szFullFileName), Dir );      \
				CatString( szFullFileName, sizeof(szFullFileName), FileName );

// Macro to create a filename from dir + subdir + filename
#define MAKE_FILENAME_SD( Dir, SubDir, FileName )                       \
				char szFullFileName[ MAX_FILENAME_SIZE ];                       \
				CopyString( szFullFileName, sizeof(szFullFileName), Dir );      \
				if (SubDir)                                                     \
				{                                                               \
						CatString( szFullFileName, sizeof(szFullFileName), SubDir );\
						CatString( szFullFileName, sizeof(szFullFileName), "/" );   \
				}                                                               \
				CatString( szFullFileName, sizeof(szFullFileName), FileName );

// Macro to create a filename from dir + subdir + subdir + filename
#define MAKE_FILENAME_SDD( Dir, SubDir, SubSubDir, FileName )           \
				char szFullFileName[ MAX_FILENAME_SIZE ];                       \
				CopyString( szFullFileName, sizeof(szFullFileName), Dir );      \
				if (SubDir)                                                     \
				{                                                               \
						CatString( szFullFileName, sizeof(szFullFileName), SubDir );\
						CatString( szFullFileName, sizeof(szFullFileName), "/" );   \
				}                                                               \
				if (SubSubDir)                                                  \
				{                                                               \
						CatString( szFullFileName, sizeof(szFullFileName), SubSubDir );\
						CatString( szFullFileName, sizeof(szFullFileName), "/" );   \
				}                                                               \
				CatString( szFullFileName, sizeof(szFullFileName), FileName );

// Macro to create a filename from dir + filename + ext  (ext need to start with a dot)
#define MAKE_FILENAME_EXT( Dir, FileName, Ext )                         \
				char szFullFileName[ MAX_FILENAME_SIZE ];                       \
				CopyString( szFullFileName, sizeof(szFullFileName), Dir );      \
				CatString( szFullFileName, sizeof(szFullFileName), FileName );  \
				CatString( szFullFileName, sizeof(szFullFileName), Ext );
				
// Macro to create a filename from dir + template + a name introduced in the template with a sprintf
#define MAKE_FILENAME_TEMPLATE( Dir, Template, FileName )               \
				char szFullFileName[ MAX_FILENAME_SIZE ];                       \
				SprintfSafe( szFullFileName, sizeof(szFullFileName), "%s" Template, Dir, FileName );
						
