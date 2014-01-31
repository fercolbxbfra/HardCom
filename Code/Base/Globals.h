//----------------------------------------------------------------------------
// globals
//----------------------------------------------------------------------------

#pragma once

class   CD3DMgr;
class   CGraphics;
class   C2DEngine;
class   CGRWorld;

class   CLowInput;
class   CUserInput;
class   CItfMgr;

class   CSoundMgr;
class   CMusicMgr;
class   CMsgWindowMgr;

class   CSetup;
class   CStringsMgr;
class   CFilePack;
class   CSysHRTimer;

class   CNodeMgr;
class   CMsgMgr;
class   CNetMgr;
class   CModesMgr;
class   CGameMgr;
class   CGameWorld;
class   CTerrain;
class   CClient;

class   CDebugInfoMgr;
class   CPerfMeterMgr;
class   CTraces;

//...only globals that are relaly global objects, created right after program starts in launcher.cpp and destroyed when leaving the program
//extern CD3DMgr*         g_pD3DMgr;
//extern CLowInput*       g_pLowInput;
//extern CModesMgr*       g_pModesMgr;
//extern CGraphics*       g_pGraphics;
//extern CSetup*          g_pSetup;
//extern CTraces*         g_pTraces;
//extern CUserInput*      g_pUserInput;
//extern CStringsMgr*     g_pStringsMgr;
//extern CMsgMgr*         g_pMsgMgr;
//extern CSoundMgr*       g_pSoundMgr;
//extern CMusicMgr*       g_pMusicMgr;
//extern C2DEngine*       g_p2DEngine;
//extern CDebugInfoMgr*   g_pDebugInfoMgr;
//extern CSysHRTimer*     g_pSysHRTimer;
//extern CPerfMeterMgr*   g_pPerfMeterMgr;
extern CFilePack*       g_pFilePack;
//extern CNetMgr*         g_pNetMgr;
//extern CGameMgr*        g_pGameMgr;
//extern CItfMgr*         g_pItfMgr;
//extern CNodeMgr*        g_pNodeMgr;
//extern CMsgWindowMgr*   g_pMsgWindowMgr;

//...false globals. they are property of some module, and their propetary has to set them to NULL when they are not valid anymore
//...y esos propietarios se encargan de ponerlos a null o no segun estan inicializados o no
//extern CGameWorld*      g_pGameWorld;      // reflection of CGameMgr::m_pGameWorld
//extern CGRWorld*        g_pGRWorld;        // reflection of CGameMgr::m_pGRWorld
//extern CTerrain*        g_pTerrain;        // reflection of CGameMgr::m_pTerrain
//extern CClient*         g_pClient;         // reflection of CNetMgr::m_pClient
