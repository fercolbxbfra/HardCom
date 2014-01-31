//----------------------------------------------------------------------------
// TODO: size checks here are not 100% safe. Really big logs messages could overflow buffers
//----------------------------------------------------------------------------

#pragma once

#include "log.h"

const char* MBT_FormatText( const char *fmt, ... );

//..................
#ifdef _ASSERTS_  
    void NotifyAssertFailure(const char* pszTextExp, const char* pszTextInfo, const char* pszFile, unsigned Line);
  
    #define ASSERT(exp) ( (exp) || (NotifyAssertFailure(#exp, NULL, __FILE__, __LINE__), 0) )
    #define ASSERTM(exp, msg) { if (!(exp)) NotifyAssertFailure(#exp, MBT_FormatText msg, __FILE__, __LINE__); }
    #define ASSERT_ONCE(exp) { static bool bDone = false; if (!(exp) && !bDone) { bDone = true;  NotifyAssertFailure(#exp, NULL, __FILE__, __LINE__); } }
    #define ASSERTM_ONCE(exp, msg) { static bool bDone = false; if (!(exp) && !bDone) { bDone = true; NotifyAssertFailure(#exp, MBT_FormatText msg, __FILE__, __LINE__); } }
  
    extern bool st_bShowAsserts;
#else
    #define ASSERT(exp) {}
    #define ASSERTM(exp, msg) {}
    #define ASSERT_ONCE(exp) {}
    #define ASSERTM_ONCE(exp, msg) {}
#endif


//...............................
#ifdef _WARNINGS_
    void Warning(const char *psz );
    #define WARNING(msg) Warning( MBT_FormatText msg )
#else
    #define WARNING(msg) 
#endif
  

//.......................
void ErrorUberCritical( const char* pszMsg );
#define ERROR_UBER_CRITICAL( msg ) ErrorUberCritical( MBT_FormatText msg );


//....................
#if defined _LOGS_ || defined _ASSERTS_
    #ifndef _ASSERTS_
        #define NotifyAssertFailure(a, b, c, d) {}
        #define ASSERTLOG(exp, msg) if (!(exp)) { LOG( msg ); }
        #define ASSERTLOG_ONCE(exp, msg) { static bool bDone = false; if (!(exp)&&!bDone) { LOG( msg ); bDone = true; } }
                
    #else
        #define ASSERTLOG(exp, msg) if (!(exp)) {                                       \
                    LOG( msg ); \
                    NotifyAssertFailure(#exp, MBT_FormatText msg, __FILE__, __LINE__);  }
        #define ASSERTLOG_ONCE(exp, msg) { static bool bDone = false; if (!(exp) && !bDone) { \
                    LOG( msg ); \
                    NotifyAssertFailure(#exp, MBT_FormatText msg, __FILE__, __LINE__);  bDone = true; } }
    #endif
#else
    #define ASSERTLOG(exp, msg)
    #define ASSERTLOG_ONCE( exp, msg )
#endif
