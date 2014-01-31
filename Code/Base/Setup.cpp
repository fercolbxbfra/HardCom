//----------------------------------------------------------------------------
//  Nombre:  Setup
//
//  Contenido: Maneja el tema del ficherito de configuracion
//----------------------------------------------------------------------------
#include "stdafx.h"
/*
#include "Setup.h"
#include "Globals.h"
#include "ConstFiles.h"
#include "DataTextBlockParser.h"
#include "Camera.h"
#include "File.h"
#include "DTB_Defines.h"
#include "Terrain.h"
#include "Random.h"
#include "StringsMgr.h"

// constants for to read install data from the register
#define REGKEY_BASE                         HKEY_LOCAL_MACHINE
#define REGKEY_NAME                         "SOFTWARE\\GamesGI\\WW2GeneralCommander"
#define REGKEY_DATANAME_SERIAL_KEY_NUMBER   "Serial Key Number"
#define REGKEY_DATANAME_LANGUAGE            "Installer Language"
#define REGKEY_DATANAME_VERSION             "Version"


#define DTB_FULLSCREEN                  "FULLSCREEN"
#define DTB_VERTSYNC                    "VERTSYNC"

#define DTB_SCREEN_SIZE                 "SCREEN_SIZE"
#define DTB_MODO_INICIAL                "MODO_INICIAL"

//.......camera...............
#define DTB_TERRENO_START               "TERRENO_START"
#define DTB_XY_LIMITED                  "XY_LIMITED"
#define DTB_ZOOM_RANGE                  "ZOOM_RANGE"
#define DTB_ZOOM_LIMITED                "ZOOM_LIMITED"
#define DTB_PITCH_RANGE                 "PITCH_RANGE"
#define DTB_PITCH_LIMITED               "PITCH_LIMITED"
#define DTB_FOLLOW_TERRAIN              "FOLLOW_TERRAIN"
#define DTB_CAM_STARTANGLE              "CAM_STARTANGLE"
#define DTB_CAM_CENTERDIST_Y            "CAM_CENTERDIST_Y"

//......detail................
#define DTB_DETAIL                      "DETAIL"
#define DTB_SHADERS                     "SHADERS"
#define DTB_TERRAIN_LOD_OFFSET          "TERRAIN_LOD_OFFSET"
#define DTB_TERRAIN_MIN_LOD             "TERRAIN_MIN_LOD"
#define DTB_CUSTOM_TERRAIN_DETAIL       "CUSTOM_TERRAIN_DETAIL"
#define DTB_SORT_PARTICLES              "SORT_PARTICLES"
#define DTB_MULTISAMPLING               "MULTISAMPLING"
#define DTB_PARTICLES                   "PARTICLES"
#define DTB_SHADOWS                     "SHADOWS"
#define DTB_FORESTS                     "FORESTS"
#define DTB_ROADS                       "ROADS"
#define DTB_CITYNAMES                   "CITYNAMES"
#define DTB_FOG                         "FOG"
#define DTB_SIMPLE_CITIES               "SIMPLE_CITIES"
#define DTB_SCREEN_MARKERS              "SCREEN_MARKERS"
#define DTB_FORESTS_DENSITY             "FORESTS_DENSITY"
#define DTB_SUPPLYROADS                 "SUPPLYROADS"
#define DTB_HQ_TERRAIN_SHADERS          "HQ_TERRAIN_SHADERS"
#define DTB_PERMANENT_CORPSES           "PERMANENT_CORPSES"

//....logs...............
#define DTB_LOGS                        "LOGS"
#define DTB_LOGS_EN_FILE                "LOGS_EN_FILE"
#define DTB_LOGFILE                     "LOGFILE"
#define DTB_MSGLOG_EN_OUTPUT            "MSGLOG_EN_OUTPUT"
#define DTB_LOGS_EXTERNAL               "LOGS_EXTERNAL"
#define DTB_DATE_EN_LOGS                "DATE_EN_LOGS"
#define DTB_LOG_KILL_RELATIONS          "LOG_KILL_RELATIONS"
#define DTB_DETAILED_LOGFILE_DUMP       "DETAILED_LOGFILE_DUMP"
#define DTB_LOG_GAME_ORDERS             "LOG_GAME_ORDERS"
#define DTB_MOTOR_FILELOG               "MOTOR_FILELOG"
#define DTB_BRAIN_FILELOG               "BRAIN_FILELOG"
#define DTB_UNIT_POSITIONS              "UNIT_POSITIONS"
#define DTB_SHOTS                       "SHOTS"
#define DTB_LOGS_ONLY_IN_MULTIPLAYER    "LOGS_ONLY_IN_MULTIPLAYER"

//.......traces.................
#define DTB_TRACES                      "TRACES"
#define DTB_TRACES_START                "TRACES_START"     
#define DTB_SHOW_KEYS_TRACES            "SHOW_KEYS_TRACES"
#define DTB_RANGE_TICKS_PERF_MEASURE    "RANGE_TICKS_PERF_MEASURE"
#define DTB_MASSIVE_SUBPERFS_FROM_START "MASSIVE_SUBPERFS_FROM_START"

//.......net.................
#define DTB_NET                         "NET"
#define DTB_LAUNCH_SERVER               "LAUNCH_SERVER"
#define DTB_CREATE_GAME                 "CREATE_GAME"
#define DTB_SERVER_IP                   "SERVER_IP"
#define DTB_NUM_PLAYERS                 "NUM_PLAYERS"
#define DTB_PLAYER_NAME                 "PLAYER_NAME"
#define DTB_PLAYER_PASSWORD             "PLAYER_PASSWORD"
#define DTB_CHECK_SYNC                  "CHECK_SYNC"
#define DTB_RECORDER_MODE               "RECORDER_MODE"
#define DTB_ORDERS_FILE                 "ORDERS_FILE"
#define DTB_CHECK_VERSION               "CHECK_VERSION"
#define DTB_ADDED_PING_LAG              "ADDED_PING_LAG"
#define DTB_EXCLUDE_EXE_FROM_CHECK_VERSION "EXCLUDE_EXE_FROM_CHECK_VERSION"

//.........sound...............
#define DTB_MUSIC                       "MUSIC"
#define DTB_MUSIC_VOLUME                "MUSIC_VOLUME"
#define DTB_SOUND                       "SOUND"
#define DTB_SOUNDFX_VOLUME              "SOUNDFX_VOLUME"
#define DTB_MIN_SOUND_DISTANCE          "MIN_SOUND_DISTANCE"
#define DTB_MAX_SOUND_DISTANCE          "MAX_SOUND_DISTANCE"
#define DTB_MAX_SIMULTANEOUS_SOUNDS     "MAX_SIMULTANEOUS_SOUNDS"

//......pre calcs..............
#define DTB_PRECALCS                    "PRECALCS"
#define DTB_SAVE_MISSING_TBK            "SAVE_MISSING_TBK"
#define DTB_RECREATE_ALL_TBK            "RECREATE_ALL_TBK"
#define DTB_CREATE_TERRAINATTR_FILE     "CREATE_TERRAINATTR_FILE"
#define DTB_CREATE_TERRAINATTR_BITMAP   "CREATE_TERRAINATTR_BITMAP"
#define DTB_CREATE_TERRAIN_TEX_GROUPS   "CREATE_TERRAIN_TEX_GROUPS"
#define DTB_CREATE_FINAL_TERRAIN_FILES  "CREATE_FINAL_TERRAIN_FILES"
#define DTB_CREATE_FORESTS_FILE         "CREATE_FORESTS_FILE"
#define DTB_CREATE_GRTERRAIN_VERTS_FILE "CREATE_GRTERRAIN_VERTS_FILE"
#define DTB_CREATE_ROADSEX_FILE         "CREATE_ROADSEX_FILE"
#define DTB_CREATE_ROADSMASK_BITMAP     "CREATE_ROADSMASK_BITMAP"

//........misc.....
#define DTB_LOADING_SCREEN              "LOADING_SCREEN"
#define DTB_MAX_TIME_PER_FRAME          "MAX_TIME_PER_FRAME"
#define DTB_TEST_MODEL                  "TEST_MODEL"
#define DTB_TEST_MODEL_NAME             "TEST_MODEL_NAME"
#define DTB_ASSERTS                     "ASSERTS"
#define DTB_PLAYER_FACTION              "PLAYER_FACTION"
#define DTB_CAN_CONTROL_ENEMIES         "CAN_CONTROL_ENEMIES"
#define DTB_START_PAUSED                "START_PAUSED"
#define DTB_ENEMYFOG                    "ENEMYFOG"
#define DTB_DIFFICULTY                  "DIFFICULTY"
#define DTB_FACTION_FRONTIER            "FACTION_FRONTIER"
#define DTB_DEFAULT_SUPPLIES            "DEFAULT_SUPPLIES"
#define DTB_LIMIT_TIME_ZOOM             "LIMIT_TIME_ZOOM"
#define DTB_CAN_ADD_BRIDGE_GUARDIANS    "CAN_ADD_BRIDGE_GUARDIANS"
#define DTB_TIME_ZOOM_MODE              "TIME_ZOOM_MODE"
#define DTB_TABLE_BORDER                "TABLE_BORDER"
#define DTB_ALLOW_TIMEOUTS              "ALLOW_TIMEOUTS"
#define DTB_PAUSE_TIMES                 "PAUSE_TIMES"
#define DTB_ALLOW_VICTORY               "ALLOW_VICTORY"
#define DTB_USE_SUPPLIES                "USE_SUPPLIES"
#define DTB_SHOW_PAUSEIMAGE             "SHOW_PAUSEIMAGE"
#define DTB_ALL_DESYNC_OPTIONS          "ALL_DESYNC_OPTIONS"
#define DTB_LANGUAGE                    "LANGUAGE"
#define DTB_USE_MINEFIELDS              "USE_MINEFIELDS"

#define DTB_BATTLE_FILE                 "BATTLE_FILE"
#define DTB_ADD_BRIDGE_GUARDIANS        "ADD_BRIDGE_GUARDIANS"
#define DTB_EXCLUDED_MAPENTS            "EXCLUDED_MAPENTS"

#define NOMBRE_FILE_SETUP               "Setup.dtb"

#define DEFAULT_CAMERA_ANGLE            V2(-90, -65)

//..same order than EDetail
const char* st_apszTerrainDetail[]=
{
    "HIGH",
    "MEDIUM",
    "LOW"
};

//..same order than ECreateTerrainAttrBitmap
const char* st_apszCreateTerrainAttrBitmap[]=
{
    "NO",
    "ALL",
    "RIVERS",
    "HILLS",
    "NOTRANS",
    "FOREST",
    "CITIES"
};

//...same order than ECheckSync
const char* st_apszCheckSync[]=
{
    "FULL",
    "CHECKSUM",
    "NO"
};

//...same order than ERecorderMode
const char* st_apszRecorderMode[]=
{
    "RECORDING",
    "REPLAYING",
    "INACTIVE"
};

#define DEFAULT_AUTHOR          "GamesGI"
#define DEFAULT_BATTLE_SIZE     1


//----------------------------------------------------------------------
// Name:    ~CSetup
// Desc:    Destructor
//----------------------------------------------------------------------

CSetup::~CSetup()
{
    SaveSettings();
    if (m_InfoDev.m_papTracesStart)
    {
        for (int i=0; i<m_InfoDev.m_iNumTracesStart; i++)
            SAFE_DELETE_ARRAY( m_InfoDev.m_papTracesStart[i] );
        SAFE_DELETE_ARRAY( m_InfoDev.m_papTracesStart );
    }
    SAFE_DELETE_ARRAY( m_InfoDev.m_pszMultiSamplingDev );
    SAFE_DELETE_ARRAY( m_InfoDev.m_pszLoadScreen );
    SAFE_DELETE_ARRAY( m_InfoDev.m_pszServerIP );
    SAFE_DELETE_ARRAY( m_InfoDev.m_pszPlayerNameDev );
    SAFE_DELETE_ARRAY( m_InfoDev.m_pszPlayerPasswordDev );
    SAFE_DELETE_ARRAY( m_InfoBattle.m_pzRoadsFile );
    SAFE_DELETE_ARRAY( m_InfoBattle.m_pzTimeStartStr );
    SAFE_DELETE_ARRAY( m_InfoBattle.m_pzTimeEndStr );
    SAFE_DELETE_ARRAY( m_InfoBattle.m_pzIntroText );
    SAFE_DELETE_ARRAY( m_InfoBattle.m_pzAuthor );
    SAFE_DELETE_ARRAY( m_InfoBattle.m_pzBattleName );

    for (uint p=0; p<m_InfoBattle.m_aDeployFrontier.size(); p++)
    {
        TPolyV2* pPoly = m_InfoBattle.m_aDeployFrontier[p];
        DISPOSE( pPoly );
    }

    SAFE_DELETE_ARRAY( m_Info.m_pszMultiSampling );

    for( int i=0; i<m_InfoBattle.m_iNumExcludedEntNames; i++ )
        DISPOSE( m_InfoBattle.m_paExcludedEntNames[i] );
    DISPOSEIF( m_InfoBattle.m_paExcludedEntNames );

    for ( uint i = 0; i < m_InfoBattle.m_apBaseInfo.size(); ++i )
        DISPOSE( m_InfoBattle.m_apBaseInfo[ i ] );

    for( uint i=0; i<m_InfoBattle.m_vEntCustomData.size(); i++ )
        DISPOSE( m_InfoBattle.m_vEntCustomData[i] );
}


//----------------------------------------------------------------------
// Name:    Init
// Desc:    Carga el fichero de configuracion
//----------------------------------------------------------------------

ERetVal CSetup::Init()
{
    ERetVal eRetVal = RET_OK;

    CargarValoresDefecto();
    CargarValoresDefecto_Battle();
    
    //....setup normal
    {    
        CDataTextBlockParser vParser;
        
        //...try to read it from outside the pack
        if (CFile::Exists( DIR_SETUP SETUP_FILE, false ))
            eRetVal = vParser.Init_File( DIR_SETUP SETUP_FILE, true );  // read from outside pack
        else
            eRetVal = vParser.Init_File( DIR_SETUP SETUP_FILE ); // read from the pack
        
        const CDTB* pDTB = vParser.GetRoot();
        if (eRetVal==RET_OK && pDTB)
            eRetVal = LeerSetupFile( pDTB );
    }

    //...setup developper
    {
        CDataTextBlockParser vParser;
        
        //...try to read it from outside the pack
        if (CFile::Exists( DIR_SETUP SETUPDEV_FILE, false ))
            eRetVal = vParser.Init_File( DIR_SETUP SETUPDEV_FILE, true );  // read from outside pack
        else
            eRetVal = vParser.Init_File( DIR_SETUP SETUPDEV_FILE ); // read from the pack
        
        const CDTB* pDTB = vParser.GetRoot();
        if (eRetVal==RET_OK && pDTB)
            eRetVal = LeerSetupFileDev( pDTB );
    }

    ASSERTM( eRetVal==RET_OK, ("Error al leer el fichero de setup. Mirar log para mas info"));
    SetDevValuesAsDefault();
    LoadSettings();
    ReadRegisterValues();

    return eRetVal;
}


//----------------------------------------------------------------------
// LeerSetupFile
// 
//----------------------------------------------------------------------

ERetVal CSetup::LeerSetupFile( const CDTB* _pDTB )
{

    ERetVal eRetVal = RET_OK;
    TInfoErr vInfoErr( __FILE__, __FUNCTION__, &eRetVal);
    
    m_Info.m_bFullScreen    = _pDTB->GetDatoBool_SubEle( DTB_FULLSCREEN, &vInfoErr );
    m_Info.m_bVertSync      = _pDTB->GetDatoBool_SubEle( DTB_VERTSYNC, &vInfoErr );
    m_Info.m_szBattleFile[0]= 0;
    m_Info.m_szBattleName[0]= 0;
    
    return eRetVal;
}


//----------------------------------------------------------------------
// LeerSetupFileDev
//
// Dev = developer 
//----------------------------------------------------------------------

ERetVal CSetup::LeerSetupFileDev( const CDTB* _pDTB )
{
    ERetVal eRetVal = RET_OK;
    TInfoErr vInfoErr( __FILE__, __FUNCTION__, &eRetVal);

    const char* pszLit;

    //...........................................LOGS................................................    
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_LOGS, &vInfoErr );
        if (pDTB)
        {
            //....Logs
            m_InfoDev.m_bLogsEnFichero  = pDTB->GetDatoBool_SubEleD( DTB_LOGS_EN_FILE, &vInfoErr, m_InfoDev.m_bLogsEnFichero );
            CopyString( m_InfoDev.m_szLogFileName, sizeof(m_InfoDev.m_szLogFileName), pDTB->GetDatoStr_SubEleD( DTB_LOGFILE, &vInfoErr, m_InfoDev.m_szLogFileName ));

            //....Logs de mensajes
            m_InfoDev.m_bVerMsgLogEnOutput = pDTB->GetDatoBool_SubEleD( DTB_MSGLOG_EN_OUTPUT, &vInfoErr, m_InfoDev.m_bVerMsgLogEnOutput );

            //....date en logs...
            m_InfoDev.m_bDateEnLogs = pDTB->GetDatoBool_SubEleD( DTB_DATE_EN_LOGS, &vInfoErr, m_InfoDev.m_bDateEnLogs );

            //....Logs a visor externo
            m_InfoDev.m_bLogsToExternal = pDTB->GetDatoBool_SubEleD( DTB_LOGS_EXTERNAL, &vInfoErr, m_InfoDev.m_bLogsToExternal );
            
            //...if want to show in the log a relation of damage and kills between arms
            m_InfoDev.m_bLogKillRelations = pDTB->GetDatoBool_SubEleD( DTB_LOG_KILL_RELATIONS, &vInfoErr, m_InfoDev.m_bLogKillRelations );

            //...if want to log detailed debug info on a file (used mostly for net synchronization problems )
            m_InfoDev.m_bDetailedLogFileDump = pDTB->GetDatoBool_SubEleD( DTB_DETAILED_LOGFILE_DUMP, &vInfoErr, m_InfoDev.m_bDetailedLogFileDump );
            
            //...log the game orders
            m_InfoDev.m_bLogGameOrders = pDTB->GetDatoBool_SubEleD( DTB_LOG_GAME_ORDERS, &vInfoErr, m_InfoDev.m_bLogGameOrders );

            //...log brain calls
            m_InfoDev.m_bMotorFileLog = pDTB->GetDatoBool_SubEleD( DTB_MOTOR_FILELOG, &vInfoErr, m_InfoDev.m_bMotorFileLog );

            //...log motor calls
            m_InfoDev.m_bBrainFileLog = pDTB->GetDatoBool_SubEleD( DTB_BRAIN_FILELOG, &vInfoErr, m_InfoDev.m_bBrainFileLog );

            //...if store 
            m_InfoDev.m_bStoreUnitPositions = pDTB->GetDatoBool_SubEleD( DTB_UNIT_POSITIONS, &vInfoErr, m_InfoDev.m_bStoreUnitPositions );

            //...shots log 
            m_InfoDev.m_bStoreShots = pDTB->GetDatoBool_SubEleD( DTB_SHOTS, &vInfoErr, m_InfoDev.m_bStoreShots );

            //...m_bLogsOnlyInMultiplayer 
            m_InfoDev.m_bLogsOnlyInMultiplayer = pDTB->GetDatoBool_SubEleD( DTB_LOGS_ONLY_IN_MULTIPLAYER, &vInfoErr, m_InfoDev.m_bLogsOnlyInMultiplayer );
        }
    }

    //.....................................TRACES................................................................
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_TRACES, &vInfoErr );
        if (pDTB)
        {
            //....traces start
            const CDTB* pDTBStart = pDTB->GetSubEle( DTB_TRACES_START, &vInfoErr );
            if (pDTBStart)
            {
                m_InfoDev.m_iNumTracesStart = pDTBStart->GetNumSubEle();
                if (m_InfoDev.m_iNumTracesStart>0)
                {
                    m_InfoDev.m_papTracesStart = NEW char*[m_InfoDev.m_iNumTracesStart];
                    for (int i=0; i<m_InfoDev.m_iNumTracesStart; i++)
                    {
                        m_InfoDev.m_papTracesStart[i] = pDTBStart->GetDatoStrAlloc_SubEle( i, &vInfoErr );
                    }
                }
            }
            
            //....si ver o no teclas de ayuda en las traces...
            m_InfoDev.m_bShowKeysTraces = pDTB->GetDatoBool_SubEleD( DTB_SHOW_KEYS_TRACES, &vInfoErr, m_InfoDev.m_bShowKeysTraces );
            
            if (pDTB->ExistSubEle( DTB_RANGE_TICKS_PERF_MEASURE ))
            {
                m_InfoDev.m_bPerfMeasure = true;
                pDTB->GetDatoV2I_SubEle( DTB_RANGE_TICKS_PERF_MEASURE, &m_InfoDev.m_vRangeTicksPerfMeasure, &vInfoErr );
            }
            
            m_InfoDev.m_bMassiveSubPerfsFromStart = pDTB->GetDatoBool_SubEleD( DTB_MASSIVE_SUBPERFS_FROM_START, &vInfoErr, m_InfoDev.m_bMassiveSubPerfsFromStart );
        }
    }

    //.......................................CAMERA..................................................
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_CAMERA, &vInfoErr );
        if (pDTB)
        {
            //....si hacer control o no de limites 
            m_InfoDev.m_bXYLimited          = pDTB->GetDatoBool_SubEleD( DTB_XY_LIMITED, &vInfoErr, m_InfoDev.m_bXYLimited );

            //...si la camara sigue el terreno o no
            m_InfoDev.m_bFollowTerrain      = pDTB->GetDatoBool_SubEleD( DTB_FOLLOW_TERRAIN, &vInfoErr, m_InfoDev.m_bFollowTerrain );
    
            //...limitar zoom máximo de la cámara, en realidad se refiere a alturas
            m_InfoDev.m_bZoomLimited        = pDTB->GetDatoBool_SubEleD( DTB_ZOOM_LIMITED, &vInfoErr, m_InfoDev.m_bZoomLimited );
            m_InfoDev.m_vZoomRange          = pDTB->GetDatoV2_SubEleD( DTB_ZOOM_RANGE, &vInfoErr, m_InfoDev.m_vZoomRange );

            //...si se limita el giro en pitch de la cámara
            m_InfoDev.m_bCamPitchLimited    = pDTB->GetDatoBool_SubEleD( DTB_PITCH_LIMITED, &vInfoErr, m_InfoDev.m_bCamPitchLimited );
            m_InfoDev.m_vCamPitchRange      = pDTB->GetDatoV2_SubEleD( DTB_PITCH_RANGE, &vInfoErr, m_InfoDev.m_vCamPitchRange );

            // ... initial angle and distance from the center of the playing area (towards south)
            m_InfoDev.m_vCamStartAngle      = pDTB->GetDatoV2_SubEleD( DTB_CAM_STARTANGLE, &vInfoErr, m_InfoDev.m_vCamStartAngle );
            m_InfoDev.m_fCamCenterDistY     = pDTB->GetDatoFloat_SubEleD( DTB_CAM_CENTERDIST_Y, &vInfoErr, m_InfoDev.m_fCamCenterDistY );
                
            // Convert to radians
            m_InfoDev.m_vCamPitchRange.x    = Grad2Rad( m_InfoDev.m_vCamPitchRange.x ); // Minimun
            m_InfoDev.m_vCamPitchRange.y    = Grad2Rad( m_InfoDev.m_vCamPitchRange.y ); // Maximun
            
            //....terreno start
            m_InfoDev.m_vTerrenoStart       = pDTB->GetDatoV2I_SubEleD( DTB_TERRENO_START, &vInfoErr, m_InfoDev.m_vTerrenoStart );
            m_InfoDev.m_vPosStartDev        = pDTB->GetDatoV3_SubEleD( DTB_POS_START, &vInfoErr, m_Info.m_vPosStart );
            if ( pDTB->ExistSubEle( DTB_POS_START ) )
                m_InfoDev.m_bPosStart = true;

            // Start camera angles (Z angle and elevation)
            m_InfoDev.m_vAnglesStart        = pDTB->GetDatoV2_SubEleD( DTB_ANGLES_START, &vInfoErr, m_InfoDev.m_vAnglesStart );
        }
    }

    //..................................DETAIL........................................................
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_DETAIL, &vInfoErr );
        if (pDTB)
        {
            //....screen size
            m_InfoDev.m_vScreenSize = pDTB->GetDatoV2I_SubEleD( DTB_SCREEN_SIZE, &vInfoErr, m_InfoDev.m_vScreenSize );
        
            //....offset applied to the theoretical LOD that should be active at any time
            m_InfoDev.m_iTerrainLODOffset      = pDTB->GetDatoInt_SubEleD( DTB_TERRAIN_LOD_OFFSET, &vInfoErr, m_InfoDev.m_iTerrainLODOffset );

            //....minimun LOD for the terrain
            m_InfoDev.m_iTerrainMinLOD      = pDTB->GetDatoInt_SubEleD( DTB_TERRAIN_MIN_LOD, &vInfoErr, m_InfoDev.m_iTerrainMinLOD );

            //....custom terrain detail
            m_InfoDev.m_bCustomTerrainDetail    = pDTB->GetDatoBool_SubEleD( DTB_CUSTOM_TERRAIN_DETAIL, &vInfoErr, m_InfoDev.m_bCustomTerrainDetail );

            //....LOD for the forests
            m_InfoDev.m_fForestsDensityDev    = pDTB->GetDatoFloat_SubEleD( DTB_FORESTS_DENSITY, &vInfoErr, m_InfoDev.m_fForestsDensityDev );

            //....visual indicators for dominated roads
            m_InfoDev.m_bShowSupplyRoads   = pDTB->GetDatoBool_SubEleD( DTB_SUPPLYROADS, &vInfoErr, m_InfoDev.m_bShowSupplyRoads );
            
            //....si sortea o no las paticulas de los sistemas de idems
            m_InfoDev.m_bSortParticles  = pDTB->GetDatoBool_SubEleD( DTB_SORT_PARTICLES, &vInfoErr, m_InfoDev.m_bSortParticles );
            
            //...tipo de multisampling
            m_InfoDev.m_pszMultiSamplingDev = pDTB->GetDatoStrAlloc_SubEleD( DTB_MULTISAMPLING, &vInfoErr, NULL );

            //...si se usan particulas o no
            m_InfoDev.m_bParticlesDev = pDTB->GetDatoBool_SubEleD( DTB_PARTICLES, &vInfoErr, m_InfoDev.m_bParticlesDev );

            //...si se usan shadows o no
            m_InfoDev.m_bShadowsDev = pDTB->GetDatoBool_SubEleD( DTB_SHADOWS, &vInfoErr, m_InfoDev.m_bShadowsDev );

            //...si se pintan los roads o no
            m_InfoDev.m_bRoadsDev = pDTB->GetDatoBool_SubEleD( DTB_ROADS, &vInfoErr, m_InfoDev.m_bRoadsDev );
            
            //...if use fog or not
            m_InfoDev.m_bFogDev = pDTB->GetDatoBool_SubEleD( DTB_FOG, &vInfoErr, m_InfoDev.m_bFogDev );
            
            //...if display city names or not
            m_InfoDev.m_bCityNames = pDTB->GetDatoBool_SubEleD( DTB_CITYNAMES, &vInfoErr, m_InfoDev.m_bCityNames );
            
            //...if make citys visuals simple or normal
            m_InfoDev.m_bSimpleCitiesDev = pDTB->GetDatoBool_SubEleD( DTB_SIMPLE_CITIES, &vInfoErr, m_InfoDev.m_bSimpleCitiesDev );

            //...if the markers on the screen are used or not
            m_InfoDev.m_bScreenMarkers = pDTB->GetDatoBool_SubEleD( DTB_SCREEN_MARKERS, &vInfoErr, m_InfoDev.m_bScreenMarkers );

            //...if the table border is loaded and drawn or not
            m_InfoDev.m_bTableBorderDev = pDTB->GetDatoBool_SubEleD( DTB_TABLE_BORDER, &vInfoErr, m_InfoDev.m_bTableBorderDev );

            //...if the terrain uses high quality shaders or not
            m_InfoDev.m_bHQTerrainShaders = pDTB->GetDatoBool_SubEleD( DTB_HQ_TERRAIN_SHADERS, &vInfoErr, m_InfoDev.m_bHQTerrainShaders );
        }
    }       
    

    //........................................net........................................    
    //...si es el server o no
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_NET, &vInfoErr );
        if (pDTB)
        {
            //..
            m_InfoDev.m_bLaunchServer   = pDTB->GetDatoBool_SubEleD( DTB_LAUNCH_SERVER, &vInfoErr, m_InfoDev.m_bLaunchServer );

            //..
            m_InfoDev.m_bCreateGame     = pDTB->GetDatoBool_SubEleD( DTB_CREATE_GAME, &vInfoErr, m_InfoDev.m_bCreateGame );

            //..
            m_InfoDev.m_bCheckVersion   = pDTB->GetDatoBool_SubEleD( DTB_CHECK_VERSION, &vInfoErr, m_InfoDev.m_bCheckVersion );

            //..
            m_InfoDev.m_bExcludeExeFromCheckVersion   = pDTB->GetDatoBool_SubEleD( DTB_EXCLUDE_EXE_FROM_CHECK_VERSION, &vInfoErr, m_InfoDev.m_bExcludeExeFromCheckVersion );
            
            //...server IP
            m_InfoDev.m_pszServerIP     = pDTB->GetDatoStrAlloc_SubEleD( DTB_SERVER_IP, &vInfoErr, NULL );

            //...numero de players
            m_InfoDev.m_iNumPlayers     = pDTB->GetDatoInt_SubEleD( DTB_NUM_PLAYERS, &vInfoErr, m_InfoDev.m_iNumPlayers );

            //...added ping lag
            m_InfoDev.m_iAddedPingLag   = pDTB->GetDatoInt_SubEleD( DTB_ADDED_PING_LAG, &vInfoErr, m_InfoDev.m_iAddedPingLag );
            
            //...player name...
            m_InfoDev.m_pszPlayerNameDev  = pDTB->GetDatoStrAlloc_SubEleD( DTB_PLAYER_NAME, &vInfoErr, "<PLAYER_NAME>" );

            //...player password...
            m_InfoDev.m_pszPlayerPasswordDev = pDTB->GetDatoStrAlloc_SubEleD( DTB_PLAYER_PASSWORD, &vInfoErr, "<PLAYER_PASSWORD>" );
            
            //...checksync type....
            if ( pDTB->ExistSubEle( DTB_CHECK_SYNC ) )
                m_InfoDev.m_eCheckSync = Str2CheckSync( pDTB->GetDatoStr_SubEle( DTB_CHECK_SYNC, &vInfoErr) );
                
            //....recorder mode......
            if (pDTB->ExistSubEle( DTB_RECORDER_MODE ))
                m_InfoDev.m_eRecorderMode = Str2RecorderMode( pDTB->GetDatoStr_SubEle( DTB_RECORDER_MODE, &vInfoErr ));
            
            if (pDTB->ExistSubEle( DTB_ORDERS_FILE ) )
            {
                COPY_STRING( m_InfoDev.m_szOrdersFile, pDTB->GetDatoStr_SubEle( DTB_ORDERS_FILE, &vInfoErr ) );
            }
            else 
            {
                if (m_InfoDev.m_eRecorderMode==RM_REPLAYING)
                {
                    ASSERTM( false, ( "When replaying a recorded game, need to specify the file with " DTB_ORDERS_FILE ));
                    eRetVal = RET_ERR;
                }
            }
        }
        m_InfoDev.m_bSinglePlayer   = (m_InfoDev.m_bCreateGame==true && m_InfoDev.m_iNumPlayers==1);
    }
    
    
    
    //........................................precalcs........................................    
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_PRECALCS, &vInfoErr );
        if (pDTB)
        {
            //...si se recrean y graban los TBK que no existan
            m_InfoDev.m_bCreateMissingTBK = pDTB->GetDatoBool_SubEleD( DTB_SAVE_MISSING_TBK, &vInfoErr, m_InfoDev.m_bCreateMissingTBK );

            //...si se recrean todos los TBKs o no
            m_InfoDev.m_bRecreateAllTBK = pDTB->GetDatoBool_SubEleD( DTB_RECREATE_ALL_TBK, &vInfoErr, m_InfoDev.m_bRecreateAllTBK );

            //...if want to recreate the TerrainAttr file
            m_InfoDev.m_bCreateTerrainAttrFile = pDTB->GetDatoBool_SubEleD( DTB_CREATE_TERRAINATTR_FILE, &vInfoErr, m_InfoDev.m_bCreateTerrainAttrFile );

            //...if want to create the bitmap mask that represents roads
            m_InfoDev.m_bCreateRoadsBitmap = pDTB->GetDatoBool_SubEleD( DTB_CREATE_ROADSMASK_BITMAP, &vInfoErr, m_InfoDev.m_bCreateRoadsBitmap );

            //...if want to create a bitmap representing the TerrainAttr file
            if (pDTB->ExistSubEle( DTB_CREATE_TERRAINATTR_BITMAP ))
                m_InfoDev.m_eCreateTerrainAttrBitmap = Str2CreateTerrainAttrBitmap( pDTB->GetDatoStr_SubEle( DTB_CREATE_TERRAINATTR_BITMAP, &vInfoErr ) );

            // if need to create the groups of terrain textures (used for texture LOD )
            m_InfoDev.m_bCreateTerrainTexGroups = pDTB->GetDatoBool_SubEleD( DTB_CREATE_TERRAIN_TEX_GROUPS, &vInfoErr, m_InfoDev.m_bCreateTerrainTexGroups );

            //...create the final terrain files
            m_InfoDev.m_bCreateFinalTerrainFiles  = pDTB->GetDatoBool_SubEleD( DTB_CREATE_FINAL_TERRAIN_FILES, &vInfoErr, m_InfoDev.m_bCreateFinalTerrainFiles );

            //...create Forests file..
            m_InfoDev.m_bCreateForestsFile    = pDTB->GetDatoBool_SubEleD( DTB_CREATE_FORESTS_FILE, &vInfoErr, m_InfoDev.m_bCreateForestsFile );
            
            //...create GRTerrainVerts file..
            m_InfoDev.m_bCreateGRTerrainVertsFile    = pDTB->GetDatoBool_SubEleD( DTB_CREATE_GRTERRAIN_VERTS_FILE, &vInfoErr, m_InfoDev.m_bCreateGRTerrainVertsFile );

            //...create Roads file..
            m_InfoDev.m_bCreateRoadsExFile    = pDTB->GetDatoBool_SubEleD( DTB_CREATE_ROADSEX_FILE, &vInfoErr, m_InfoDev.m_bCreateRoadsExFile );
        }
    }


    //.........................................SOUND...................................................
    {
        const CDTB* pDTB = _pDTB->GetSubEle( DTB_SOUND, &vInfoErr );
        if (pDTB)
        {
            //...si suena musica o no
            m_InfoDev.m_bMusic = pDTB->GetDatoBool_SubEleD( DTB_MUSIC, &vInfoErr, m_InfoDev.m_bMusic );

            //...volumen de la musica
            m_InfoDev.m_fMusicVolumeDev = pDTB->GetDatoFloat_SubEleD( DTB_MUSIC_VOLUME, &vInfoErr, m_InfoDev.m_fMusicVolumeDev );

            //...si hay sonido o no
            m_InfoDev.m_bSound = pDTB->GetDatoBool_SubEleD( DTB_SOUND, &vInfoErr, m_InfoDev.m_bSound );

            //...volumen de los fx de sonido
            m_InfoDev.m_fSoundFXVolumeDev = pDTB->GetDatoFloat_SubEleD( DTB_SOUNDFX_VOLUME, &vInfoErr, m_InfoDev.m_fSoundFXVolumeDev );

            //...min sound distance....    
            m_InfoDev.m_fMinSoundDistance = pDTB->GetDatoFloat_SubEleD( DTB_MIN_SOUND_DISTANCE, &vInfoErr, m_InfoDev.m_fMinSoundDistance );

            //...max sound distance....    
            m_InfoDev.m_fMaxSoundDistance = pDTB->GetDatoFloat_SubEleD( DTB_MAX_SOUND_DISTANCE, &vInfoErr, m_InfoDev.m_fMaxSoundDistance );

            //...max simultaneous sounds....
            m_InfoDev.m_iMaxSimultaneousSounds = pDTB->GetDatoInt_SubEleD( DTB_MAX_SIMULTANEOUS_SOUNDS, &vInfoErr, m_InfoDev.m_iMaxSimultaneousSounds );
        }
    }
    
        
    //......................................MISC.............................................................
    //...modo inicial
    pszLit = _pDTB->GetDatoStr_SubEle( DTB_MODO_INICIAL, &vInfoErr );
    m_InfoDev.m_eInitialMode = GetModeByName( pszLit );
    if (m_InfoDev.m_eInitialMode==MODE_INVALID)
        m_InfoDev.m_eInitialMode = MODE_INIT_SCREEN;
    if (m_InfoDev.m_eRecorderMode==RM_REPLAYING)
        m_InfoDev.m_eInitialMode    = MODE_SKIP_MENUS;        
    
    //...max time per frame
    m_InfoDev.m_iMaxTimePerFrame = int( _pDTB->GetDatoFloat_SubEle( DTB_MAX_TIME_PER_FRAME, &vInfoErr ) * 1000 );
    
    //...si se sacan asserts o no
    #ifdef _ASSERTS_
    m_InfoDev.m_bAsserts = _pDTB->GetDatoBool_SubEleD( DTB_ASSERTS, &vInfoErr, m_InfoDev.m_bAsserts );
    st_bShowAsserts = m_InfoDev.m_bAsserts;
    #endif

    //...si se empieza en modo test model o no
    m_InfoDev.m_bTestModel = _pDTB->GetDatoBool_SubEleD( DTB_TEST_MODEL, &vInfoErr, m_InfoDev.m_bTestModel );

    //...el nombre del test model
    m_InfoDev.m_TestModelName = _pDTB->GetDatoStr_SubEleD( DTB_TEST_MODEL_NAME, &vInfoErr, m_InfoDev.m_TestModelName.GetStr() );

    //...pantalla de carga
    m_InfoDev.m_pszLoadScreen   = _pDTB->GetDatoStrAlloc_SubEleD( DTB_LOADING_SCREEN, &vInfoErr, NULL );

    //..faction del player
    if (_pDTB->ExistSubEle( DTB_PLAYER_FACTION ) )
    {
        m_InfoDev.m_ePlayerFaction  = GetFactionFromName( _pDTB->GetDatoStr_SubEle( DTB_PLAYER_FACTION, &vInfoErr ) );
        if ( m_InfoDev.m_ePlayerFaction == FACTION_INVALID )
            m_InfoDev.m_ePlayerFaction  = FACTION_NEUTRAL;
    }

    m_InfoDev.m_bCanControlEnemies = _pDTB->GetDatoBool_SubEleD( DTB_CAN_CONTROL_ENEMIES, &vInfoErr, m_InfoDev.m_bCanControlEnemies );

    //..time zoom mode
    if (_pDTB->ExistSubEle( DTB_TIME_ZOOM_MODE ) )
    {
        m_InfoDev.m_eTimeZoomMode = GetTimeZoomTypeByName( _pDTB->GetDatoStr_SubEle( DTB_TIME_ZOOM_MODE, &vInfoErr ) );
    }
    else
        ASSERTM( false, ("Parameter .TIME_ZOOM_MODE not found in SetupDev.dtb") );
    
    //...flag to start game paused...
    m_InfoDev.m_bStartPaused    = _pDTB->GetDatoBool_SubEleD( DTB_START_PAUSED, &vInfoErr, m_InfoDev.m_bStartPaused );
    
    //...if enemies will start hidden and will need to be discovered or not
    m_InfoDev.m_bEnemyFogDev = _pDTB->GetDatoBool_SubEleD( DTB_ENEMYFOG, &vInfoErr, m_InfoDev.m_bEnemyFogDev );

    m_InfoDev.m_iDifficultyDev = _pDTB->GetDatoInt_SubEleD( DTB_DIFFICULTY, &vInfoErr, m_InfoDev.m_iDifficultyDev );

    //...if faction frontier should be drawn or not
    m_InfoDev.m_bFactionFrontier = _pDTB->GetDatoBool_SubEleD( DTB_FACTION_FRONTIER, &vInfoErr, m_InfoDev.m_bFactionFrontier );
            
    //...if supplies won't be calculated and substituted by default values
    m_InfoDev.m_bDefaultSupplies = _pDTB->GetDatoBool_SubEleD( DTB_DEFAULT_SUPPLIES, &vInfoErr, m_InfoDev.m_bDefaultSupplies );

    //...if want to limit the time zoom values
    m_InfoDev.m_bLimitTimeZoom = _pDTB->GetDatoBool_SubEleD( DTB_LIMIT_TIME_ZOOM, &vInfoErr, m_InfoDev.m_bLimitTimeZoom );

    m_InfoDev.m_bAllowTimeoutsDev = _pDTB->GetDatoBool_SubEleD( DTB_ALLOW_TIMEOUTS, &vInfoErr, m_InfoDev.m_bAllowTimeoutsDev );

    m_InfoDev.m_bAllowVictory = _pDTB->GetDatoBool_SubEleD( DTB_ALLOW_VICTORY, &vInfoErr, m_InfoDev.m_bAllowVictory );

    m_InfoDev.m_bUseSuppliesDev = _pDTB->GetDatoBool_SubEleD( DTB_USE_SUPPLIES, &vInfoErr, m_InfoDev.m_bUseSuppliesDev );

    m_InfoDev.m_bShowPauseImage = _pDTB->GetDatoBool_SubEleD( DTB_SHOW_PAUSEIMAGE, &vInfoErr, m_InfoDev.m_bShowPauseImage );

    m_InfoDev.m_iDifficultyDev = _pDTB->GetDatoInt_SubEleD( DTB_DIFFICULTY, &vInfoErr, m_InfoDev.m_iDifficultyDev );

    m_InfoDev.m_bUseMinefields = _pDTB->GetDatoBool_SubEleD( DTB_USE_MINEFIELDS, &vInfoErr, m_InfoDev.m_bUseMinefields );

    // Battle info file
    if( _pDTB->ExistSubEle( DTB_BATTLE_FILE ) )
    {
        COPY_STRING( m_InfoDev.m_szBattleFileDev, _pDTB->GetDatoStr_SubEle( DTB_BATTLE_FILE, &vInfoErr ));
    }
    else
    {
        ASSERTLOG( false, ("Parámetro BATTLE_FILE en Setup no encontrado.") );
        eRetVal = RET_ERR;
    }
    
    if (_pDTB->ExistSubEle( DTB_LANGUAGE ))
    {
        m_InfoDev.m_eLang   = GetLang( _pDTB->GetDatoStr_SubEle( DTB_LANGUAGE, &vInfoErr ) );
        m_bUseInstallLang   = false;
    }
    else
        m_bUseInstallLang   = true;

    //...if true, then the .BAT defines if the guardians are created or not. If false, they are not created dont matter what the .BAT says
    m_InfoDev.m_bCanAddBridgeGuardians = _pDTB->GetDatoBool_SubEleD( DTB_CAN_ADD_BRIDGE_GUARDIANS, &vInfoErr, m_InfoDev.m_bCanAddBridgeGuardians );

    // Game will be paused in these date & time's
    // They are expected to be ordered from sooner to later
    const char *zDateTimeStr;
    if( _pDTB->ExistSubEle( DTB_PAUSE_TIMES ) )
    {
        const CDTB* pDTBGameTimes = _pDTB->GetSubEle( DTB_PAUSE_TIMES, &vInfoErr );
        int iNumValues = pDTBGameTimes->GetNumSubEle();
        
        for( int i=0; i<iNumValues; i++ )
        {
            zDateTimeStr = pDTBGameTimes->GetDatoStr_SubEle( i, &vInfoErr );
            m_InfoDev.m_vPauseTimes.push_back( CGameDate() );
            m_InfoDev.m_vPauseTimes.back().Init( zDateTimeStr );
        }
    }
    
    //
    bool bAllDesyncOptions = _pDTB->GetDatoBool_SubEleD( DTB_ALL_DESYNC_OPTIONS, &vInfoErr );
    if (bAllDesyncOptions)
    {
        m_InfoDev.m_eCheckSync                  = CS_CHECKSUM;
        m_InfoDev.m_eRecorderMode               = RM_RECORDING;
        m_InfoDev.m_bCheckVersion               = true;
        m_InfoDev.m_bLogsEnFichero              = true;
        m_InfoDev.m_bDetailedLogFileDump        = true;
        m_InfoDev.m_bLogGameOrders              = true;
        m_InfoDev.m_bMotorFileLog               = true;
        m_InfoDev.m_bBrainFileLog               = true;
        m_InfoDev.m_bStoreUnitPositions         = true;
        m_InfoDev.m_bStoreShots                 = true;
    }

    return eRetVal;
}



//----------------------------------------------------------------------
// LeerBattleFile
//----------------------------------------------------------------------

ERetVal CSetup::LeerBattleFile( const char* _pzBattleFile, bool _bReadOnlyBasicData )
{
    ERetVal eRetVal = RET_OK;
    TInfoErr vInfoErr( __FILE__, __FUNCTION__, &eRetVal);

    CDataTextBlockParser vParser;
    eRetVal = vParser.Init_FileInAndOutPack( DIR_WORLD, _pzBattleFile );
    const CDTB* pDTB = NULL;
    if ( eRetVal==RET_OK )
        pDTB = vParser.GetRoot();
    else
    {
        LOG( ("ERR: CSetup::LeerBattleFile-> Error initializing parser with file '%s'", _pzBattleFile ) );
        return RET_ERR;
    }

    if ( eRetVal==RET_OK )
    {
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzRoadsFile );
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzTimeStartStr );
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzTimeEndStr );
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzIntroText );
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzAuthor );
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzBattleName );
        for( int i=0; i<m_InfoBattle.m_iNumExcludedEntNames; i++ )
            DISPOSEIF( m_InfoBattle.m_paExcludedEntNames[i] );
        SAFE_DELETE_ARRAY( m_InfoBattle.m_paExcludedEntNames );

        CargarValoresDefecto_Battle();

        // Battle name
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzBattleName );
        if ( pDTB->ExistSubEle( DTB_NAME ) )
            m_InfoBattle.m_pzBattleName = pDTB->GetDatoStrAlloc_SubEle( DTB_NAME, &vInfoErr );
        else
            ASSERTM( false, ("CSetup::LeerBattleFile-> Battle file %s has no .NAME", g_pSetup->GetInfo().m_szBattleFile) );

        // Author
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzAuthor );
        if ( pDTB->ExistSubEle( DTB_AUTHOR ) )
        {
            m_InfoBattle.m_pzAuthor = pDTB->GetDatoStrAlloc_SubEle( DTB_AUTHOR, &vInfoErr );
        }
        else
            m_InfoBattle.m_pzAuthor = ALLOC_COPY_STRING( DEFAULT_AUTHOR );

        // Size (orientative, shown on battle selection)
        m_InfoBattle.m_iSize = pDTB->GetDatoInt_SubEleD( DTB_SIZE, &vInfoErr, m_InfoBattle.m_iSize );

        // Online-ness
        m_InfoBattle.m_bOnline = pDTB->GetDatoBool_SubEleD( DTB_ONLINE, &vInfoErr, m_InfoBattle.m_bOnline );

        // Battle intro text
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzIntroText );
        if ( pDTB->ExistSubEle( DTB_INTRO_TEXT ) )
            m_InfoBattle.m_pzIntroText = pDTB->GetDatoStrAlloc_SubEle( DTB_INTRO_TEXT, &vInfoErr );
            
        // Start date and time
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzTimeStartStr );
        m_InfoBattle.m_pzTimeStartStr = pDTB->GetDatoStrAlloc_SubEle( DTB_TIME_START, &vInfoErr );
        // End date and time
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzTimeEndStr );
        m_InfoBattle.m_pzTimeEndStr = pDTB->GetDatoStrAlloc_SubEle( DTB_END_GAME_DATE, &vInfoErr );

        // Objetive scores
        m_InfoBattle.m_fScoreObjetive          = pDTB->GetDatoFloat_SubEle( DTB_OBJETIVE_POINTS, &vInfoErr );
        m_InfoBattle.m_fScoreObjetiveOffensive = pDTB->GetDatoFloat_SubEle( DTB_OBJETIVE_POINTS_OFFENSIVE, &vInfoErr );
        m_InfoBattle.m_fScoreObjetiveDefensive = pDTB->GetDatoFloat_SubEle( DTB_OBJETIVE_POINTS_DEFENSIVE, &vInfoErr );
        ASSERTM( m_InfoBattle.m_fScoreObjetiveDefensive < m_InfoBattle.m_fScoreObjetive &&
                 m_InfoBattle.m_fScoreObjetive < m_InfoBattle.m_fScoreObjetiveOffensive,
                 ("CSetup::LeerBattleFile-> Objetive scores in file '%s' are incorrect", pDTB->GetFileName()) );

        // Offensive faction
        m_InfoBattle.m_eOffensiveFaction = GetFactionFromName( pDTB->GetDatoStr_SubEle( DTB_OFFENSIVE_FACTION, &vInfoErr ) );
        ASSERT( m_InfoBattle.m_eOffensiveFaction != FACTION_INVALID );

        // Roads file
        SAFE_DELETE_ARRAY( m_InfoBattle.m_pzRoadsFile );
        m_InfoBattle.m_pzRoadsFile = pDTB->GetDatoStrAlloc_SubEle( DTB_ROADS_FILE, &vInfoErr );

        // Bridge guardians
        if ( pDTB->ExistSubEle( DTB_ADD_BRIDGE_GUARDIANS ) )
            m_InfoBattle.m_bBridgeGuardians = pDTB->GetDatoBool_SubEle( DTB_ADD_BRIDGE_GUARDIANS, &vInfoErr );
            
        // Playing area
        m_InfoBattle.m_bPlayingArea = pDTB->ExistSubEle( DTB_PLAYING_AREA );
        ASSERTM( m_InfoBattle.m_bPlayingArea, ("No PLAYING_AREA defined in file %s", _pzBattleFile ));
        if (m_InfoBattle.m_bPlayingArea)
        {
            const CDTB* pDTBs = pDTB->GetSubEle( DTB_PLAYING_AREA, &vInfoErr );
            if (pDTBs)
            {
                pDTBs->GetDatoV2_SubEle( DTB_POS, &m_InfoBattle.m_PlayingArea.m_vPos, &vInfoErr );
                pDTBs->GetDatoV2_SubEle( DTB_SIZE, &m_InfoBattle.m_PlayingArea.m_vSize, &vInfoErr );
            }
        }

        // Read base cities info
        for ( uint i = 0; i < m_InfoBattle.m_apBaseInfo.size(); ++i )
            DISPOSE( m_InfoBattle.m_apBaseInfo[ i ] );
        m_InfoBattle.m_apBaseInfo.clear();
        const CDTB* pDTBBases = pDTB->GetSubEle( DTB_BASE_CITIES, &vInfoErr );
        ASSERTM( pDTBBases, ("CSetup::LeerBattleFile-> BASE_CITIES definition not found in battle file %s", m_Info.m_szBattleFile) );

        int iNumBases = pDTBBases->GetNumSubEle();
        for ( int i=0; i<iNumBases; i++ )
        {
            const CDTB* pDTBBase    = pDTBBases->GetSubEle( i );
            ASSERT( pDTBBase );

            TBaseInfo* pBase = NEW TBaseInfo();
            pBase->m_pszName        = ALLOC_COPY_STRING( pDTBBase->GetDatoStr_SubEle( DTB_NAME ) );
            pBase->m_iProduction    = pDTBBase->GetDatoInt_SubEle( DTB_PRODUCTION );
            pBase->m_eCountry       = GetCountryFromAcronym( pDTBBase->GetDatoStr_SubEle( DTB_COUNTRY ) );
            m_InfoBattle.m_apBaseInfo.push_back( pBase );
        }
        ASSERTM( eRetVal == RET_OK, ("CSetup::LeerBattleFile-> Error reading base info in battle file %s", m_Info.m_szBattleFile) );

        // Excluded map ent names list
        // Reset list
        for( int i=0; i<m_InfoBattle.m_iNumExcludedEntNames; i++ )
            DISPOSEIF( m_InfoBattle.m_paExcludedEntNames[i] );
        DISPOSEIF( m_InfoBattle.m_paExcludedEntNames );
        m_InfoBattle.m_iNumExcludedEntNames = 0;
        const char* pzExcludedEntName;
        if ( pDTB->ExistSubEle( DTB_EXCLUDED_MAPENTS ) )
        {
            // Read list
            const CDTB* pListDTB = pDTB->GetSubEle( DTB_EXCLUDED_MAPENTS, &vInfoErr );
            m_InfoBattle.m_iNumExcludedEntNames = pListDTB->GetNumSubEle();
            m_InfoBattle.m_paExcludedEntNames = NEW CNameID*[m_InfoBattle.m_iNumExcludedEntNames];
            for( int i=0; i<m_InfoBattle.m_iNumExcludedEntNames; i++ )
            {
                pzExcludedEntName = pListDTB->GetDatoStr_SubEle( i, &vInfoErr );
                m_InfoBattle.m_paExcludedEntNames[i] = NEW CNameID( pzExcludedEntName );
            }
        }

        m_InfoBattle.m_iMaxGarrisons_Allies = pDTB->GetDatoInt_SubEleD( DTB_MAXGARRISONS_ALLIES, &vInfoErr, m_InfoBattle.m_iMaxGarrisons_Allies );
        m_InfoBattle.m_iMaxGarrisons_Axis = pDTB->GetDatoInt_SubEleD( DTB_MAXGARRISONS_AXIS, &vInfoErr, m_InfoBattle.m_iMaxGarrisons_Axis );

        m_InfoBattle.m_iBattleTimeouts = pDTB->GetDatoInt_SubEleD( DTB_TIMEOUTS, &vInfoErr, m_InfoBattle.m_iBattleTimeouts );

        // Deployment deploy zones for deployment phase
        TPolyV2 tPoly;
        tPoly.Init( 3 );
        tPoly.SetVert( 0, V2( 0, 0 ) );
        tPoly.SetVert( 1, V2( 1, 0 ) );
        tPoly.SetVert( 2, V2( 0, 1 ) );
        m_InfoBattle.m_apDeployZones[0] = tPoly;
        m_InfoBattle.m_apDeployZones[1] = tPoly;
        m_InfoBattle.m_apDeployZones[2] = tPoly;

        if ( pDTB->ExistSubEle( DTB_DEPLOY_ZONES ) )
        {
            const CDTB* pDTB_DeployZones = pDTB->GetSubEle( DTB_DEPLOY_ZONES, &vInfoErr );
            
            for ( int i = 0; i < FACTION_NUM_TYPES; ++i )
            {
                if ( pDTB_DeployZones->ExistSubEle( GetFactionName( (EFaction)i ) ) )
                {
                    const CDTB* pDTBZone = pDTB_DeployZones->GetSubEle( GetFactionName( (EFaction)i ), &vInfoErr );
                    int iNumVerts = pDTBZone->GetNumSubEle();
                    if ( iNumVerts < 3 )
                    {
                        LOG( ("ERR: CSetup::LeerBattleFile-> A deployment zone polygon need at least 3 points") );
                        eRetVal = RET_ERR;
                    }
                    TPolyV2 tPoly;
                    tPoly.Init( iNumVerts );
                    for ( int v = 0; v < iNumVerts; ++v )
                    {
                        V2 vPos;
                        pDTBZone->GetDatoV2_SubEle( v, &vPos, &vInfoErr );
                        tPoly.SetVert( v, vPos );
                    }
                    m_InfoBattle.m_apDeployZones[ i ] = tPoly;
                    
                    ASSERTLOG( tPoly.CheckConvex(), ("CSetup::LeerBattleFile-> The deployment zone polygon for faction '%s' in the file '%s' is not convex", GetFactionName( (EFaction)i ), g_pSetup->GetInfo().m_szBattleFile ) );
                }
            }
        }
        else
        {
            for ( int i = 0; i < FACTION_NUM_TYPES; ++i )
                m_InfoBattle.m_apDeployZones[ i ].Init( 0 );
        }

        // Deploy frontier
        for ( uint p = 0; p < m_InfoBattle.m_aDeployFrontier.size(); ++p )
            DISPOSE( m_InfoBattle.m_aDeployFrontier[ p ] );
        m_InfoBattle.m_aDeployFrontier.clear();
        if ( pDTB->ExistSubEle( DTB_DEPLOY_FRONTIER ) )
        {
            const CDTB* pDTBF = pDTB->GetSubEle( DTB_DEPLOY_FRONTIER );
            int iNumPolys = pDTBF->GetNumSubEle();
            for (int p=0; p<iNumPolys; p++)
            {
                const CDTB* pDTBP = pDTBF->GetSubEle( p );
                int iNumVerts = pDTBP->GetNumSubEle();
                if (iNumVerts<3)
                {
                    LOG( ("ERR: CSetup::LeerBattleFile-> A deployment frontier polygon need at least 3 points") );
                    eRetVal = RET_ERR;
                }
                TPolyV2* pPoly = NEW TPolyV2;
                pPoly->Init( iNumVerts );
                for (int v=0; v<iNumVerts; v++)
                {
                    V2 vPos;
                    pDTBP->GetDatoV2_SubEle( v, &vPos, &vInfoErr );
                    pPoly->SetVert( v, vPos );
                }
                m_InfoBattle.m_aDeployFrontier.push_back( pPoly );
                
                ASSERTLOG( pPoly->CheckConvex(), ("CSetup::LeerBattleFile-> The frontier polygon: %d in the file: '%s' is not convex. ", p, g_pSetup->GetInfo().m_szBattleFile ) );
            }
        }

        // Objective lines for deployment phase
        m_InfoBattle.m_vDeployObjLineStart.clear();
        m_InfoBattle.m_vDeployObjLineEnd.clear();
        m_InfoBattle.m_vDeployObjLineFaction.clear();
        if ( pDTB->ExistSubEle( DTB_OBJECTIVE_LINES ) )
        {
            const CDTB* pDTB_NMZone = pDTB->GetSubEle( DTB_OBJECTIVE_LINES, &vInfoErr );
            int iNumObjLines = pDTB_NMZone->GetNumSubEle();
            V2 vPosStart;
            V2 vPosEnd;
            EFaction eZoneFaction;

            const CDTB* pDTBObjLine;
            for( int i=0; i<iNumObjLines; i++ )
            {
                pDTBObjLine = pDTB_NMZone->GetSubEle(i);

                // Ensure necessary parameters do exist
                if( !pDTBObjLine->ExistSubEle( DTB_POS_START ) )
                    ASSERTM( false, ("CSetup::LeerBattleFile-> OBJECTIVE_LINES %d has no .POS_START parameter in battle file %s", i, g_pSetup->GetInfo().m_szBattleFile) );
                if( !pDTBObjLine->ExistSubEle( DTB_POS_END ) )
                    ASSERTM( false, ("CSetup::LeerBattleFile-> OBJECTIVE_LINES %d has no .POS_END parameter in battle file %s", i, g_pSetup->GetInfo().m_szBattleFile) );
                if( !pDTBObjLine->ExistSubEle( DTB_FACTION ) )
                    ASSERTM( false, ("CSetup::LeerBattleFile-> OBJECTIVE_LINES %d has no .FACTION parameter in battle file %s", i, g_pSetup->GetInfo().m_szBattleFile) );
                
                pDTBObjLine->GetDatoV2_SubEle( DTB_POS_START, &vPosStart, &vInfoErr );
                pDTBObjLine->GetDatoV2_SubEle( DTB_POS_END, &vPosEnd, &vInfoErr );

                eZoneFaction = GetFactionFromName( pDTBObjLine->GetDatoStr_SubEle( DTB_FACTION, &vInfoErr ) );

                m_InfoBattle.m_vDeployObjLineStart.push_back( vPosStart );
                m_InfoBattle.m_vDeployObjLineEnd.push_back( vPosEnd );
                m_InfoBattle.m_vDeployObjLineFaction.push_back( eZoneFaction );
            }
        }

    }

    if ( eRetVal==RET_OK && !_bReadOnlyBasicData )
    {
        // Reset airfield data
        m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumFighters = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumBombers = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumTransporters = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumParatroopers = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iBombsCapacity = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iSuppliesCapacity = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumFighters = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumBombers = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumTransporters = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumParatroopers = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iBombsCapacity = 0;
        m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iSuppliesCapacity = 0;

        // Airfield data
        if ( pDTB->ExistSubEle( DTB_AIRFIELD_DATA ) )
        {
            const CDTB* pDTBroot = NULL;
            pDTBroot = vParser.GetRoot();
            ASSERTM( pDTBroot, ("CSetup::LeerBattleFile-> Parser root can not be retrieved") );

            const CDTB* pDTBAirfieldData = NULL;
            pDTBAirfieldData = pDTBroot->GetSubEle( DTB_AIRFIELD_DATA, &vInfoErr );
            ASSERTM( pDTBAirfieldData, ("CSetup::LeerBattleFile-> Parser root can not be retrieved") );

            const CDTB* pDTBFactionData;
            pDTBFactionData = pDTBAirfieldData->GetSubEle( DTB_ALLIES, &vInfoErr );
            if ( !pDTBFactionData ) 
            {
                LOG( ("CSetup::LeerBattleFile-> Section ALLIES not found in AIRFIELD_DATA in '%s'. Allied airfield won't be operative", g_pSetup->GetInfo().m_szBattleFile) );
            }
            else
            {
                m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumFighters     = pDTBFactionData->GetDatoInt_SubEle( DTB_NUM_FIGHTERS, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumBombers      = pDTBFactionData->GetDatoInt_SubEle( DTB_NUM_BOMBERS, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumTransporters = pDTBFactionData->GetDatoInt_SubEle( DTB_NUM_TRANSPORTERS, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumParatroopers = pDTBFactionData->GetDatoInt_SubEleD( DTB_NUM_PARATROOPERS, &vInfoErr,
                                                                                  m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iNumParatroopers );
                m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iBombsCapacity   = pDTBFactionData->GetDatoInt_SubEle( DTB_BOMBS_CAPACITY, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_ALLIES].m_iSuppliesCapacity = pDTBFactionData->GetDatoInt_SubEle( DTB_SUPPLIES_CAPACITY, &vInfoErr );
            }

            pDTBFactionData = pDTBAirfieldData->GetSubEle( DTB_AXIS, &vInfoErr );
            if ( !pDTBFactionData )
            {
                LOG( ("CSetup::LeerBattleFile-> Section AXIS not found in AIRFIELD_DATA in '%s'. Axis airfield won't be operative", g_pSetup->GetInfo().m_szBattleFile) );
            }
            else
            {
                m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumFighters       = pDTBFactionData->GetDatoInt_SubEle( DTB_NUM_FIGHTERS, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumBombers        = pDTBFactionData->GetDatoInt_SubEle( DTB_NUM_BOMBERS, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumTransporters   = pDTBFactionData->GetDatoInt_SubEle( DTB_NUM_TRANSPORTERS, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumParatroopers   = pDTBFactionData->GetDatoInt_SubEleD( DTB_NUM_PARATROOPERS, &vInfoErr,
                                                                                  m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iNumParatroopers );
                m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iBombsCapacity     = pDTBFactionData->GetDatoInt_SubEle( DTB_BOMBS_CAPACITY, &vInfoErr );
                m_InfoBattle.m_tAirfieldInfo[FACTION_AXIS].m_iSuppliesCapacity  = pDTBFactionData->GetDatoInt_SubEle( DTB_SUPPLIES_CAPACITY, &vInfoErr );
            }
        }
        else
            LOG( ("CSetup::LeerBattleFile-> File '%s' has no AIRFIELD_DATA field. Airfields in this batle (if any) won't be operative", g_pSetup->GetInfo().m_szBattleFile ) );
    }    
    
    return eRetVal;
}



//----------------------------------------------------------------------
// SetDevValuesAsDefault
//
//----------------------------------------------------------------------

void CSetup::SetDevValuesAsDefault()
{
    COPY_STRING( m_Info.m_szBattleFile, m_InfoDev.m_szBattleFileDev );
    m_Info.m_ePlayerFaction     = m_InfoDev.m_ePlayerFaction;
    m_Info.m_bParticles         = m_InfoDev.m_bParticlesDev;
    m_Info.m_bShadows           = m_InfoDev.m_bShadowsDev;
    m_Info.m_pszMultiSampling   = ALLOC_COPY_STRING( m_InfoDev.m_pszMultiSamplingDev );
    m_Info.m_bFog               = m_InfoDev.m_bFogDev;
    m_Info.m_fForestsDensity    = m_InfoDev.m_fForestsDensityDev;
    m_Info.m_bAllowTimeouts     = m_InfoDev.m_bAllowTimeoutsDev;
    m_Info.m_eTimeZoomMode      = m_InfoDev.m_eTimeZoomMode;
    m_Info.m_bUseSupplies       = m_InfoDev.m_bUseSuppliesDev;
    m_Info.m_bEnemyFog          = m_InfoDev.m_bEnemyFogDev;
    m_Info.m_iDifficulty        = m_InfoDev.m_iDifficultyDev;
    m_Info.m_bSimpleCities      = m_InfoDev.m_bSimpleCitiesDev;
    m_Info.m_bTableBorder       = m_InfoDev.m_bTableBorderDev;
    m_Info.m_fSoundFXVolume     = m_InfoDev.m_fSoundFXVolumeDev;
    m_Info.m_fMusicVolume       = m_InfoDev.m_fMusicVolumeDev;
    m_Info.m_eTerrainDetail     = TD_HIGH;
    m_Info.m_eGlobalQuality     = QLTY_HIGH;
    m_Info.m_bUse3DModels       = true;
    m_Info.m_bUseNATO           = false;
    m_Info.m_bUserNameEntered   = false;
    m_Info.m_bPermanentCorpses  = true;
    m_Info.m_fMouseSpeed        = 1.55f;
    COPY_STRING( m_Info.m_szUserName, m_InfoDev.m_pszPlayerNameDev );
    COPY_STRING( m_Info.m_szUserPassword, m_InfoDev.m_pszPlayerPasswordDev );
    COPY_STRING( m_Info.m_szUserNick, "DEFAULT" );
}


//----------------------------------------------------------------------
// ReadRegisterValues
//
//----------------------------------------------------------------------

void CSetup::ReadRegisterValues()
{
    //...read the game directory from the registry
    HKEY hKey;
    LONG err = RegOpenKeyEx( REGKEY_BASE, REGKEY_NAME, 0, KEY_ALL_ACCESS, &hKey );
    if (err!=ERROR_SUCCESS)
    {
        ERROR_UBER_CRITICAL(( "General Commander seems to be not properly installed" ));
    }

    //..read serial key number from register
    DWORD dwSize = sizeof(m_InfoDev.m_szSerialKeyNumber);
    RegQueryValueEx( hKey, REGKEY_DATANAME_SERIAL_KEY_NUMBER, 0, NULL, (BYTE*)m_InfoDev.m_szSerialKeyNumber, &dwSize );

    //...read language from register...
    if (m_bUseInstallLang)
    {
        char szLanguage[5];
        dwSize = sizeof(szLanguage);
        LONG Ret = RegQueryValueEx( hKey, REGKEY_DATANAME_LANGUAGE, 0, NULL, (BYTE*)szLanguage, &dwSize );
        if (Ret==ERROR_SUCCESS)
            m_InfoDev.m_eLang = GetLangFromRegisterString( szLanguage );
    }
    
    //...read version from register...
    dwSize = sizeof(m_InfoDev.m_szGameVersion);
    RegQueryValueEx( hKey, REGKEY_DATANAME_VERSION, 0, NULL, (BYTE*)m_InfoDev.m_szGameVersion, &dwSize );
    
    //...close key
    RegCloseKey( hKey );
}



//----------------------------------------------------------------------
// CargarValoresDefecto
// 
//----------------------------------------------------------------------

void CSetup::CargarValoresDefecto()
{
    m_Info.m_bFullScreen                        = false;
    m_Info.m_bVertSync                          = false;
    m_Info.m_ePlayerFaction                     = FACTION_INVALID;
    m_Info.m_szBattleFile[0]                    = 0;
    m_Info.m_szBattleName[0]                    = 0;
    m_Info.m_pszMultiSampling                   = NULL;
    m_Info.m_bParticles                         = true;
    m_Info.m_bFog                               = false;
    m_Info.m_bShadows                           = false;
    m_Info.m_bUseNATO                           = false;
    m_Info.m_bUse3DModels                       = false;
    m_Info.m_bFog                               = false;
    m_Info.m_bAffectWeather                     = true;
    m_Info.m_iDifficulty                        = 1;
    m_Info.m_bEnemyFog                          = true;
    m_Info.m_bUseSupplies                       = true;
    m_Info.m_iManualTimeStartIndex              = 7;
    m_Info.m_vPosStart                          = cV3_Zero;

    //.................logs..............................
    m_InfoDev.m_bLogsEnFichero                  = false;
    m_InfoDev.m_szLogFileName[0]                = '\0';    
    m_InfoDev.m_bVerMsgLogEnOutput              = false;
    m_InfoDev.m_bLogsToExternal                 = false;
    m_InfoDev.m_bDateEnLogs                     = true;
    m_InfoDev.m_bLogGameOrders                  = false;
    m_InfoDev.m_bDetailedLogFileDump            = false;
    m_InfoDev.m_bMotorFileLog                   = false;
    m_InfoDev.m_bBrainFileLog                   = false;
    m_InfoDev.m_bStoreUnitPositions             = false;
    m_InfoDev.m_bStoreShots                     = false;
    m_InfoDev.m_bLogsOnlyInMultiplayer          = false;
    
    //.................traces............................
    m_InfoDev.m_iNumTracesStart                 = 0;
    m_InfoDev.m_papTracesStart                  = NULL;
    m_InfoDev.m_bShowKeysTraces                 = true;
    m_InfoDev.m_bPerfMeasure                    = false;
    m_InfoDev.m_bMassiveSubPerfsFromStart       = false;
    
    //.................camera..............................
    m_InfoDev.m_vTerrenoStart                   = V2I(0, 0);
    m_InfoDev.m_vPosStartDev                    = cV3_Zero;
    m_InfoDev.m_bPosStart                       = false;
    m_InfoDev.m_vAnglesStart                    = DEFAULT_CAMERA_ANGLE;
    m_InfoDev.m_vZoomRange                      = cV2_Zero;
    m_InfoDev.m_bZoomLimited                    = false;
    m_InfoDev.m_bCamPitchLimited                = false;
    m_InfoDev.m_vCamPitchRange                  = cV2_Zero;
    m_InfoDev.m_bFollowTerrain                  = false;
    m_InfoDev.m_bXYLimited                      = false;
    m_InfoDev.m_vCamStartAngle                  = V2( -90.0f, -45.0f );
    m_InfoDev.m_fCamCenterDistY                 = 50000.0f;
    
    //.................detail.............................
    m_InfoDev.m_vScreenSize                     = V2I( 1024, 768 );
    m_InfoDev.m_bSortParticles                  = false;
    m_InfoDev.m_pszMultiSamplingDev             = NULL;
    m_InfoDev.m_bParticlesDev                   = true;
    m_InfoDev.m_bShadowsDev                     = false;
    m_InfoDev.m_bRoadsDev                       = false;
    m_InfoDev.m_bFogDev                         = false;
    m_InfoDev.m_bCityNames                      = false;
    m_InfoDev.m_bSimpleCitiesDev                = false;
    m_InfoDev.m_bScreenMarkers                  = true;
    m_InfoDev.m_bTableBorderDev                 = true;
    m_InfoDev.m_iTerrainLODOffset               = 0;
    m_InfoDev.m_iTerrainMinLOD                  = 0;
    m_InfoDev.m_bCustomTerrainDetail            = false;
    m_InfoDev.m_fForestsDensityDev              = 1;
    m_InfoDev.m_bShowSupplyRoads                = false;
    m_InfoDev.m_bHQTerrainShaders               = true;

    //............net..........................
    m_InfoDev.m_bLaunchServer                   = false;
    m_InfoDev.m_bCreateGame                     = true;
    m_InfoDev.m_pszServerIP                     = NULL;
    m_InfoDev.m_iNumPlayers                     = 1;
    m_InfoDev.m_bSinglePlayer                   = true;
    m_InfoDev.m_pszPlayerNameDev                = NULL;
    m_InfoDev.m_pszPlayerPasswordDev            = NULL;
    m_InfoDev.m_eCheckSync                      = CS_NO;
    m_InfoDev.m_eRecorderMode                   = RM_INACTIVE;
    m_InfoDev.m_szOrdersFile[0]                 = 0;
    m_InfoDev.m_bCheckVersion                   = true;
    m_InfoDev.m_iAddedPingLag                   = 0;
    m_InfoDev.m_bExcludeExeFromCheckVersion     = false;
    

    //........precalcs........................
    m_InfoDev.m_bCreateMissingTBK               = false;
    m_InfoDev.m_bRecreateAllTBK                 = false;
    m_InfoDev.m_bCreateTerrainAttrFile          = false;
    m_InfoDev.m_bCreateTerrainTexGroups         = false;
    m_InfoDev.m_bCreateFinalTerrainFiles        = false;
    m_InfoDev.m_bCreateForestsFile              = false;
    m_InfoDev.m_eCreateTerrainAttrBitmap        = CTAB_NO;  
    m_InfoDev.m_bCreateGRTerrainVertsFile       = false;
    m_InfoDev.m_bCreateRoadsExFile              = false;
    m_InfoDev.m_bCreateRoadsBitmap              = false;

    //.........sound...............
    m_InfoDev.m_bMusic                          = true;
    m_InfoDev.m_bSound                          = true;
    m_InfoDev.m_fMusicVolumeDev                 = 1;
    m_InfoDev.m_fSoundFXVolumeDev               = 1;
    m_InfoDev.m_fMinSoundDistance               = 500;
    m_InfoDev.m_fMaxSoundDistance               = 12000;
    m_InfoDev.m_iMaxSimultaneousSounds          = 40;
     
    //.................misc.................................
    m_InfoDev.m_eInitialMode                    = MODE_INIT_SCREEN;
    m_InfoDev.m_pszLoadScreen                   = NULL;
    m_InfoDev.m_iMaxTimePerFrame                = 1000;
    m_InfoDev.m_bTestModel                      = false;
    m_InfoDev.m_bAsserts                        = true;
    m_InfoDev.m_ePlayerFaction                  = FACTION_ALLIES;
    m_InfoDev.m_bCanControlEnemies              = false;
    m_InfoDev.m_bStartPaused                    = false;
    m_InfoDev.m_bEnemyFogDev                    = true;
    m_InfoDev.m_iDifficultyDev                  = true;
    m_InfoDev.m_bFactionFrontier                = false;
    m_InfoDev.m_bDefaultSupplies                = false;
    m_InfoDev.m_bLimitTimeZoom                  = true;
    m_InfoDev.m_bLogKillRelations               = false;
    m_InfoDev.m_bDetailedLogFileDump            = false;
    m_InfoDev.m_szBattleFileDev[0]              = 0;
    m_InfoDev.m_bCanAddBridgeGuardians          = true;
    m_InfoDev.m_eTimeZoomMode                   = TZM_AUTO;
    m_InfoDev.m_bAllowTimeoutsDev               = false;
    m_InfoDev.m_vPauseTimes.clear();
    m_InfoDev.m_bAllowVictory                   = true;
    m_InfoDev.m_bUseSuppliesDev                 = true;
    m_InfoDev.m_bShowPauseImage                 = true;
    m_InfoDev.m_eLang                           = LA_ENGLISH;
    m_InfoDev.m_bUseMinefields                  = true;
    COPY_STRING( m_InfoDev.m_szGameVersion, "-.-" );
    COPY_STRING( m_InfoDev.m_szSerialKeyNumber, "9999-9999-9999-9999" );

    m_InfoBattle.m_eOffensiveFaction            = FACTION_NEUTRAL;
    m_InfoBattle.m_pzTimeStartStr               = NULL;
    m_InfoBattle.m_pzTimeEndStr                 = NULL;
    m_InfoBattle.m_fScoreObjetive               = 0.0f;
    m_InfoBattle.m_fScoreObjetiveOffensive      = 200.0f;
    m_InfoBattle.m_fScoreObjetiveDefensive      = -200.0f;
    m_InfoBattle.m_pzRoadsFile                  = NULL;
    m_InfoBattle.m_pzIntroText                  = NULL;
    m_InfoBattle.m_pzBattleName                 = NULL;
    m_InfoBattle.m_paExcludedEntNames           = NULL;
    m_InfoBattle.m_pzAuthor                     = NULL;
}



//----------------------------------------------------------------------
// CargarValoresDefecto_Battle
//----------------------------------------------------------------------

void CSetup::CargarValoresDefecto_Battle()
{
    m_InfoBattle.m_bBridgeGuardians             = false;
    m_InfoBattle.m_iNumExcludedEntNames         = 0;
    m_InfoBattle.m_iBattleTimeouts              = 0;
    m_InfoBattle.m_iMaxGarrisons_Allies         = 0;
    m_InfoBattle.m_iMaxGarrisons_Axis           = 0;
    m_InfoBattle.m_bOnline                      = false;
    m_InfoBattle.m_iSize                        = DEFAULT_BATTLE_SIZE;

    m_InfoBattle.m_eOffensiveFaction            = FACTION_NEUTRAL;
    m_InfoBattle.m_pzTimeStartStr               = NULL;
    m_InfoBattle.m_pzTimeEndStr                 = NULL;
    m_InfoBattle.m_fScoreObjetive               = 0.0f;
    m_InfoBattle.m_fScoreObjetiveOffensive      = 200.0f;
    m_InfoBattle.m_fScoreObjetiveDefensive      = -200.0f;
    m_InfoBattle.m_pzRoadsFile                  = NULL;
    m_InfoBattle.m_pzIntroText                  = NULL;
    m_InfoBattle.m_pzBattleName                 = NULL;
    m_InfoBattle.m_paExcludedEntNames           = NULL;
    m_InfoBattle.m_pzAuthor                     = NULL;
}



//----------------------------------------------------------------------
// Str2TerrainDetail
// 
// convert an string representing a detail into a detail enum value
//----------------------------------------------------------------------

ETerrainDetail Str2TerrainDetail( const char* _psz )
{
    ETerrainDetail eDetail = TD_HIGH;
    bool bFound     = false;
    
    for (int i=0; i<SIZE_ARRAY( st_apszTerrainDetail ) && !bFound; i++)
    {
        if (IsEqualStringNoCase( st_apszTerrainDetail[i], _psz ) )
        {
            bFound  = true;
            eDetail = ETerrainDetail( i );
        }
    }
    
    if (!bFound)
    {
        LOG(("ERR: terrain detail: '%s' not found. Assuming: '%s'", _psz, st_apszTerrainDetail[ eDetail ] ));
    }
    
    return eDetail;
}



//----------------------------------------------------------------------
// Str2CheckSync
// 
// convert an string representing a detail into a checksync enum value
//----------------------------------------------------------------------

ECheckSync Str2CheckSync( const char* _psz )
{
    ECheckSync eCheckSync   = CS_NO;
    bool bFound             = false;
    
    for (int i=0; i<SIZE_ARRAY( st_apszCheckSync ) && !bFound; i++)
    {
        if (IsEqualStringNoCase( st_apszCheckSync[i], _psz ) )
        {
            bFound      = true;
            eCheckSync  = ECheckSync( i );
        }
    }
    
    if (!bFound)
    {
        LOG(("ERR: checksync: '%s' not found. Assuming: '%s'", _psz, st_apszCheckSync[ eCheckSync ] ));
    }
    
    return eCheckSync;
}



//----------------------------------------------------------------------
// Str2RecorderMode
// 
// convert an string representing a recorder mode into a recordermode enum value
//----------------------------------------------------------------------

ERecorderMode Str2RecorderMode( const char* _psz )
{
    ERecorderMode eRecorderMode = RM_INACTIVE;
    bool bFound                 = false;
    
    for (int i=0; i<SIZE_ARRAY( st_apszRecorderMode ) && !bFound; i++)
    {
        if (IsEqualStringNoCase( st_apszRecorderMode[i], _psz ) )
        {
            bFound          = true;
            eRecorderMode   = ERecorderMode( i );
        }
    }
    
    if (!bFound)
    {
        LOG(("ERR: recorder mode: '%s' not found. Assuming: '%s'", _psz, st_apszCheckSync[ eRecorderMode ] ));
    }
    
    return eRecorderMode;
}



//----------------------------------------------------------------------
// Str2CreateTerrainAttrBitmap
// 
// convert an string representing a terrainbitmap type generation into an enum value
//----------------------------------------------------------------------

ECreateTerrainAttrBitmap Str2CreateTerrainAttrBitmap( const char* _psz )
{
    ECreateTerrainAttrBitmap eType  = CTAB_NO;
    bool bFound                     = false;
    
    for (int i=0; i<SIZE_ARRAY( st_apszCreateTerrainAttrBitmap ) && !bFound; i++)
    {
        if (IsEqualStringNoCase( st_apszCreateTerrainAttrBitmap[i], _psz ) )
        {
            bFound  = true;
            eType   = ECreateTerrainAttrBitmap( i );
        }
    }
    
    if (!bFound)
    {
        LOG(("ERR: terrain generation bitmap style: '%s' not found. Assuming: '%s'", _psz, st_apszCreateTerrainAttrBitmap[ eType ] ));
    }
    
    return eType;
}



//----------------------------------------------------------------------
// SaveSettings
//----------------------------------------------------------------------

void CSetup::SaveSettings()
{
    CFile File;
    File.SetNoPack();
    int iStrSize;

    File.OpenWrite( DIR_ROOT, SETTINGS_FILE );
    if (File.HayError())
    {
        ASSERTM( false, ("Could not open file for saving settings: '%s' (maybe it's write protected?)", DIR_ROOT, SETTINGS_FILE) );
        return;
    }

    File.Write( &m_Info.m_fForestsDensity, sizeof(m_Info.m_fForestsDensity) );
    File.Write( &m_Info.m_bParticles, sizeof(m_Info.m_bParticles) );
    File.Write( &m_Info.m_bShadows, sizeof(m_Info.m_bShadows) );
    File.Write( &m_Info.m_bFog, sizeof(m_Info.m_bFog) );
    iStrSize = 1+strlen( m_Info.m_pszMultiSampling );
    File.Write( &iStrSize, sizeof(iStrSize) );
    File.Write( (void *)m_Info.m_pszMultiSampling, iStrSize );
    File.Write( &m_Info.m_bSimpleCities, sizeof(m_Info.m_bSimpleCities) );
    File.Write( &m_Info.m_bTableBorder, sizeof(m_Info.m_bTableBorder) );
    File.Write( &m_Info.m_bUserNameEntered, sizeof(m_Info.m_bUserNameEntered) );
    File.Write( &m_Info.m_szUserName, sizeof(m_Info.m_szUserName) );
    File.Write( &m_Info.m_szUserPassword, sizeof(m_Info.m_szUserPassword) );
    File.Write( &m_Info.m_szUserNick, sizeof(m_Info.m_szUserNick) );
    File.Write( &m_Info.m_fSoundFXVolume, sizeof(m_Info.m_fSoundFXVolume) );
    File.Write( &m_Info.m_fMusicVolume, sizeof(m_Info.m_fMusicVolume) );
    File.Write( &m_Info.m_eGlobalQuality, sizeof(m_Info.m_eGlobalQuality) );
    File.Write( &m_Info.m_bPermanentCorpses, sizeof(m_Info.m_bPermanentCorpses) );
    File.Write( &m_Info.m_eTerrainDetail, sizeof(m_Info.m_eTerrainDetail) );
    File.Write( &m_Info.m_bUse3DModels, sizeof(m_Info.m_bUse3DModels) );
    File.Write( &m_Info.m_fMouseSpeed, sizeof(m_Info.m_fMouseSpeed) );
    
    File.Close();
}



//----------------------------------------------------------------------
// LoadSettings
//----------------------------------------------------------------------

void CSetup::LoadSettings()
{
    CFile File;
    File.SetNoPack();
    int iStrSize;

    File.Open( DIR_ROOT, SETTINGS_FILE );
    if (File.HayError())
        return;

    File.Read( &m_Info.m_fForestsDensity, sizeof(m_Info.m_fForestsDensity) );
    File.Read( &m_Info.m_bParticles, sizeof(m_Info.m_bParticles) );
    File.Read( &m_Info.m_bShadows, sizeof(m_Info.m_bShadows) );
    File.Read( &m_Info.m_bFog, sizeof(m_Info.m_bFog) );
    File.Read( &iStrSize, sizeof(iStrSize) );
    SAFE_DELETE_ARRAY( m_Info.m_pszMultiSampling );
    m_Info.m_pszMultiSampling = NEW char[iStrSize];
    File.Read( (void *)m_Info.m_pszMultiSampling, iStrSize );
    File.Read( &m_Info.m_bSimpleCities, sizeof(m_Info.m_bSimpleCities) );
    File.Read( &m_Info.m_bTableBorder, sizeof(m_Info.m_bTableBorder) );
    File.Read( &m_Info.m_bUserNameEntered, sizeof(m_Info.m_bUserNameEntered) );
    File.Read( &m_Info.m_szUserName, sizeof(m_Info.m_szUserName) );
    File.Read( &m_Info.m_szUserPassword, sizeof(m_Info.m_szUserPassword) );
    File.Read( &m_Info.m_szUserNick, sizeof(m_Info.m_szUserNick) );
    File.Read( &m_Info.m_fSoundFXVolume, sizeof(m_Info.m_fSoundFXVolume) );
    File.Read( &m_Info.m_fMusicVolume, sizeof(m_Info.m_fMusicVolume) );
    File.Read( &m_Info.m_eGlobalQuality, sizeof(m_Info.m_eGlobalQuality) );
    File.Read( &m_Info.m_bPermanentCorpses, sizeof(m_Info.m_bPermanentCorpses) );
    File.Read( &m_Info.m_eTerrainDetail, sizeof(m_Info.m_eTerrainDetail) );
    File.Read( &m_Info.m_bUse3DModels, sizeof(m_Info.m_bUse3DModels) );
    File.Read( &m_Info.m_fMouseSpeed, sizeof(m_Info.m_fMouseSpeed) );

    File.Close();
}



//----------------------------------------------------------------------
// SaveInfoToOrdersFile
//
// stored the info needed for orders file (the files used to store game orders to replay them after )
//----------------------------------------------------------------------

void CSetup::SaveInfoToOrdersFile( CFile* _pFile )
{
    _pFile->Write( m_Info.m_szBattleFile, sizeof(m_Info.m_szBattleFile) );
    _pFile->Write( &m_Info.m_ePlayerFaction, sizeof(m_Info.m_ePlayerFaction) );
    
    _pFile->Write( (void*)&m_InfoDev.m_bCanAddBridgeGuardians, sizeof(m_InfoDev.m_bCanAddBridgeGuardians) );
    _pFile->Write( (void*)&m_InfoDev.m_eTimeZoomMode, sizeof(m_InfoDev.m_eTimeZoomMode) );
}


//----------------------------------------------------------------------
// ReadInfoFromOrdersFile
//
// read the stored info from an orders file (the files used to store game orders to replay them after )
//----------------------------------------------------------------------

void CSetup::ReadInfoFromOrdersFile( CFile* _pFile )
{
    _pFile->Read( m_Info.m_szBattleFile, sizeof(m_Info.m_szBattleFile) );
    _pFile->Read_Int( (int*)&m_Info.m_ePlayerFaction );
    
    _pFile->Read_Bool( &m_InfoDev.m_bCanAddBridgeGuardians );
    _pFile->Read_Int( (int*)&m_InfoDev.m_eTimeZoomMode );
}



//----------------------------------------------------------------------
// TEntCustomData constructor
//----------------------------------------------------------------------

TEntCustomData::TEntCustomData( int _iID, EEntCustomType _eEntCustomType, ECountry _eCountry, V2I _vWorldPos )
{
    m_iID = _iID;
    m_eEntCustomType = _eEntCustomType;
    m_eCountry = _eCountry;
    m_vWorldPos = _vWorldPos;
}



//----------------------------------------------------------------------
// TEntCustomData destructor
//----------------------------------------------------------------------

TEntCustomData::~TEntCustomData()
{
}



//----------------------------------------------------------------------
// TStrategicPointData constructor
//----------------------------------------------------------------------

CSetup::TStrategicPointData::TStrategicPointData( const char* _pzName, EFaction _eFaction, int _iScore )
{
    m_pzName = _pzName;
    m_eFaction = _eFaction;
    m_iScore = _iScore;
    m_vWorldPos = cV2I_Zero;
}



//----------------------------------------------------------------------
// TStrategicPointData destructor
//----------------------------------------------------------------------

CSetup::TStrategicPointData::~TStrategicPointData()
{
    DISPOSEIF( m_pzName );
}

*/