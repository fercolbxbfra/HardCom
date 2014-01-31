//----------------------------------------------------------------------------
// manages a memory file, which is a buffer in memory where is possible to read and write sequentially in the same way we do with a normal file
//----------------------------------------------------------------------------

#pragma once

#include "NameID.h"

class CFile;

class CMemFile
{
	public:
																CMemFile                () { m_bOk = false; }
																~CMemFile                ();

		void                        operator=               ( const CMemFile& _MemFile );
																	 
		void                        Init                    ( int _iInitsize = 5*1024 );        
		void                        InitRaw                 ( int _iSize, byte* _pData );
		void                        InitFromFile            ( CFile* _pFile );
		void                        SetGrowth               ( int _iGrowth ) { m_iGrowth = _iGrowth; }
		void                        End                     ();                                   
		ERetVal                     Read                    ( void* _pBuffer, int _iBytes );
		ERetVal                     Read_Int                ( int* _pVal );
		ERetVal                     Read_NameID             ( CNameID* _pNameID );
				
		void                        Write                   ( void* _pBuffer, int _iBytes );
		void                        Write_Str               ( const char* _pszBuffer );
		void                        Write_Int               ( int _iVal );
				
		void                        GoStart                 () { m_iCursorPos = 0; }
		int                         GetSize                 () { return m_iDataUsed; }
		byte*                       GetData                 () { return m_pData; }
		ERetVal                     GetErrorState           () { return m_bHadError ? RET_ERR : RET_OK; }
		int                         GetCursorPos            () { return m_iCursorPos; }
				
	private:
		
		void                        InitVars                ();        
				
	private:

		bool                        m_bOk;
		byte*                       m_pData;
		int                         m_iDataUsed;    //..how many bytes are really in use in the buffer
		int                         m_iBufferSize;  //...buffer total size, including the not used part
		int                         m_iGrowth;      //..when the file needs to grow, it always grow in this amount
		int                         m_iCursorPos; 
		bool                        m_bHadError;   // set true when there is any kind of error with the operations in this file. Used to not need to check on every call
}; 
