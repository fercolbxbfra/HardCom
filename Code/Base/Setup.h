//----------------------------------------------------------------------------
//  setup files
//----------------------------------------------------------------------------

#pragma once

class CASTFile;

//#include "ConstFiles.h"
//#include "Mode.h"
//#include "Vector.h"
//#include "NameID.h"
//#include "Factions.h"
//#include "TimeZoomMgr.h"
//#include "Box.h"
//#include "GameDate.h"
//#include "Polygon.h"
//#include "Languages.h"

class   CDataTextBlock;
typedef CDataTextBlock CDTB;
class   CFile;

/*
class CSetup
{
		public:

				 // this goes to the settings.dat
				struct TInfo
				{    
						bool                        m_bFullScreen;
						bool                        m_bVertSync;
						char*                       m_pszMultiSampling;
						bool                        m_bParticles;
						bool                        m_bShadows;
						float                       m_fMusicVolume;
						float                       m_fSoundFXVolume;  
						V3                          m_vPosStart;
						float                       m_fMouseSpeed;
				};


				struct TInfoDev
				{
						//.........misc.................................
						EMode                       m_eInitialMode;
						bool                        m_bTestModel;
						CNameID                     m_TestModelName;
						char*                       m_pszLoadScreen;
						int                         m_iMaxTimePerFrame;
						bool                        m_bAsserts;
						ELang                       m_eLang;
						char                        m_szGameVersion[ SIZE_GAME_VERSION ];
						char                        m_szSerialKeyNumber[ SIZE_SERIAL_KEY_NUMBER ];
						
						//................sound....................
						bool                        m_bMusic;
						float                       m_fMusicVolumeDev;
						bool                        m_bSound;    // when false, there is no sound at all, not just fxsounds.
						float                       m_fSoundFXVolumeDev;
						float                       m_fMinSoundDistance;
						float                       m_fMaxSoundDistance;
						int                         m_iMaxSimultaneousSounds;
						
						
						//......camera.................................
						V3                          m_vPosStartDev;
						bool                        m_bPosStart;
						V2                          m_vAnglesStart;
						V2                          m_vZoomRange;
						bool                        m_bZoomLimited;
						bool                        m_bCamPitchLimited;       // Limits camera pitch angle
						V2                          m_vCamPitchRange;   // Min/max pitch angle for the camera
																														// (internally in radians, in the file in degrees) (normally between -0.0 and -90.0)
						V2                          m_vCamStartAngle;
						float                       m_fCamCenterDistY;
						bool                        m_bFollowTerrain;
						bool                        m_bXYLimited;
						
						//.....nivel de detalle...................
						V2I                         m_vScreenSize;
						int                         m_iTerrainLODOffset;
						int                         m_iTerrainMinLOD;
						bool                        m_bCustomTerrainDetail;  // when false, the two other terrain detail fields here are not used, and the value in the settings.dat (Info) is used instead
						bool                        m_bSortParticles;
						char*                       m_pszMultiSamplingDev;
						bool                        m_bParticlesDev;
						bool                        m_bShadowsDev;
						bool                        m_bRoadsDev;
						bool                        m_bFogDev;
						bool                        m_bSimpleCitiesDev;
						bool                        m_bCityNames;
						bool                        m_bScreenMarkers;
						bool                        m_bTableBorderDev;
						float                       m_fForestsDensityDev;
						bool                        m_bShowSupplyRoads;
						bool                        m_bHQTerrainShaders;  // HQ = high quality
						
						//...logs....
						bool                        m_bLogsEnFichero;
						char                        m_szLogFileName[ MAX_FILENAME_SIZE ];
						bool                        m_bLogsToExternal;
						bool                        m_bDateEnLogs;
						bool                        m_bDetailedLogFileDump;
						
						//.........traces..........
						char**                      m_papTracesStart;
						int                         m_iNumTracesStart;
						bool                        m_bShowKeysTraces;
						bool                        m_bPerfMeasure;
						V2I                         m_vRangeTicksPerfMeasure;
						bool                        m_bMassiveSubPerfsFromStart;
						
				};
						
		
		public:
		
																		CSetup                  () {}
																	 ~CSetup                  ();
				ERetVal                     Init                    ();
				
				TInfo&                      GetInfo                 () { return m_Info; }
				const TInfoDev&             GetInfoDev              () { return m_InfoDev; }
				TInfoBattle&                GetInfoBattle           () { return m_InfoBattle; }
				ERetVal                     LeerBattleFile          ( const char* _pzBattleFile, bool _bReadOnlyBasicData = false );
				void                        SaveSettings            ();
				
				void                        SaveInfoToOrdersFile    ( CFile* _pFile );
				void                        ReadInfoFromOrdersFile  ( CFile* _pFile );
				void                        ReadRegisterValues      ();

		private:
		
				ERetVal                     LeerSetupFile           ( const CDTB* _pDTB );
				ERetVal                     LeerSetupFileDev        ( const CDTB* _pDTB );
				void                        CargarValoresDefecto        ();
				void                        CargarValoresDefecto_Battle ();
				void                        SetDevValuesAsDefault   ();
				void                        LoadSettings            ();
				
		private:
		
				TInfo                       m_Info;
				TInfoDev                    m_InfoDev;
				TInfoBattle                 m_InfoBattle;
				bool                        m_bUseInstallLang;
};                                           
		

ETerrainDetail              Str2TerrainDetail           ( const char* _psz );
ECreateTerrainAttrBitmap    Str2CreateTerrainAttrBitmap ( const char* _psz );
ECheckSync                  Str2CheckSync               ( const char* _psz );
ERecorderMode               Str2RecorderMode            ( const char* _psz );

*/