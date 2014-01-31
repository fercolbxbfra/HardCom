//-----------------------------------------------------------------------------
// TODO: size checks are not 100% safe, really big log messages could overdlow buffers in some situations
//-----------------------------------------------------------------------------

#pragma once

#ifdef _LOGS_
    #define LOG( s )        CLog::Logf s
    #define MSGLOG( s )     CLog::Logf_Msg s
    #define LOG_NODATE( s ) CLog::LogfNoDate s
    #define LOG_ONCE( s )               \
    {                                   \
        static bool bDone = false;      \
        if (!bDone)                     \
        {                               \
            bDone = true;               \
            LOG( s );                   \
            LOG(( "--- the previous log wont be shown again" ));    \
        }                               \
    }
    #define LOGFILE( exp )  LogFile exp
#else   
    #define LOG( s ) {}
    #define MSGLOG( s ) {}
    #define LOGFILE( exp ) {}
    #define LOG_NODATE( exp ) {}
    #define LOG_ONCE( exp ) {}
#endif

//...this class should not use any new, because it is initialized before everything else, even before the memory manager
class CLog
{
    public:
    
        static void                 Init_PostSetup          ();
        static void                 End                     ();
        static void                 Log                     ( const char* _pszMsg, bool bPutDate = true );
        static void                 Logf                    ( const char* _pszFmt, ... );
        static void                 LogfNoDate              ( const char* _pszFmt, ... );
        
        static void                 ShowTime                ( bool _bShow ) { m_bTimeInLogs = _bShow; }
        
    private:
    
        static void                 AddDateAndTime          ( char* _pszBuf, int _iSize );
        static void                 SendToExternal          ( const char* _pszMsg );
            

    private:
    
        static bool                 m_bLogInFile;
        static char                 m_szLogFile[ MAX_FILENAME_SIZE ];
        static FILE*                m_fp;

        static bool                 m_bDateInLogs;
        static bool                 m_bTimeInLogs;
        static bool                 m_bTickInLogs;

        static bool                 m_bLogExternal;
        static bool                 m_bReadyToSend;     // to know if the visor is correctly initialized

        static HANDLE               m_hReadPipe;
        static HANDLE               m_hWritePipe;
        static HANDLE               m_hChildProc;
};