//----------------------------------------------------------------------------
// all basic typedefs, very basic functions, defines, pragmas, etc. used everywhere
//----------------------------------------------------------------------------

#pragma once

//#define D3D_DEBUG_INFO  // uncomment for extra directx debug info

//...this define make windows.h to not include some not needed things, like winsock.h and many others.
#define WIN32_LEAN_AND_MEAN

#define DIRECTINPUT_VERSION 0x0800
#pragma warning( disable : 4267 )  // remove the type conversion warning
#pragma warning( disable : 4311 )  // 
#pragma warning( disable : 4312 )  // 

//...removes the warning about old CRT functions like strcpi and so being deprecated
#define _CRT_SECURE_NO_DEPRECATE

template <bool b>
struct COMPILE_TIME_ASSERT_FAIL;
template <>
struct COMPILE_TIME_ASSERT_FAIL<true>{};
template <int i>
struct COMPILE_TIME_ASSERT_TEST
{	enum { dummy = i }; };
#define COMPILE_TIME_ASSERT(expr) \
	COMPILE_TIME_ASSERT_TEST<sizeof(COMPILE_TIME_ASSERT_FAIL<(bool)(expr)>)>

//----------------------------------------------------------------------------
typedef unsigned char		uchar;
typedef unsigned int		uint;
typedef unsigned short	ushort;
typedef unsigned long		ulong;
typedef unsigned char		byte;
typedef unsigned int		dword;
typedef unsigned short	word;
typedef unsigned int		uint32;

COMPILE_TIME_ASSERT(sizeof(uint32) == 4);

#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG  
#include "Version_Debug.h"
#endif

#ifdef _PROFILE
#include "Version_Profile.h"
#endif 

#ifdef _RELEASE_ 
#include "Version_Release.h"
#endif


enum ERetVal { RET_OK=0, RET_ERR };

#define SIZE_ARRAY(a)           (sizeof(a)/sizeof(*(a)))


//----------------------------------------------------------------------------
// NEWS / DELETES
#define CREATEOBJ( obj, function, par ) obj::function( par, __FILE__, __LINE__ )
#ifdef _MEM_MANAGER_
	void* __cdecl operator new( size_t size,const char *,int);
	void __cdecl operator delete( void * pMem, const char* pszFile, int iLine );
	#define NEW new(__FILE__, __LINE__) 
	#define NEW_MOVED( file, line ) new( file, line )
#else
	#define NEW new
	#define NEW_MOVED( file, line ) new
#endif
#define SAFE_DELETE(p) if (p) {delete p; p = NULL; }
#define SAFE_DELETE_ARRAY(p) {if (p) {delete[] p; p = NULL; }}


#define PI 3.1415926535897932384626433832795f
#define VAL_DELTA 0.00001f
#define INVALID_INT 0xffffffff
#define NOTHING INVALID_INT
#define NONE INVALID_INT
#define TIME_INFINITE INVALID_INT
#define CRLF "\r\n"
#define CR '\r'
#define SIZE_STR_32 32    // this is for strings where a size of 32 is more or less right, not just strings that are exactly size 32.


#include "../targetver.h"
#include <windows.h>
#include "ConstFiles.h"  
#include "Assert.h"
#include "Strings.h"

#include <vector>
using namespace std;


/*
#define FUNCION_NO_DEFINIDA                                             \
		static bool bAvisado = false;                                       \
		if (!bAvisado)                                                      \
		{                                                                   \
				bAvisado = true;                                                \
				LOG(("Funcion no definida en %s line: %d", __FILE__, __LINE__));       \
		}
*/    
		


//...helper to get comprehensible errores without much coding
struct TInfoErr
{
	const char* m_pszLit1;
	const char* m_pszLit2;
	const char* m_pszLit3;
	ERetVal*    m_peRetVal;
	bool        m_bShowError;
	bool        m_bOptional;  //...true when we dont want to show the error
		
							TInfoErr() { Reset(); }
							TInfoErr( const char* _pszLit1, ERetVal* _peRetVal );
							TInfoErr( const char* _pszLit1, const char* _pszLit2, ERetVal* _peRetVal );
							TInfoErr( const char* _pszLit1, const char* _pszLit2, const char* _pszLit3, ERetVal* _peRetVal );
	void        Reset  ();
};


//////////////////////////////////////////////////////////////////////////
inline TInfoErr::TInfoErr( const char* _pszLit1, ERetVal* _peRetVal )
{
	Reset();
	m_pszLit1 = _pszLit1;
	m_peRetVal = _peRetVal;
}

inline TInfoErr::TInfoErr( const char* _pszLit1, const char* _pszLit2, ERetVal* _peRetVal )
{
	Reset();
	m_pszLit1   = _pszLit1;
	m_pszLit2   = _pszLit2;
	m_peRetVal  = _peRetVal;
}

inline TInfoErr::TInfoErr( const char* _pszLit1, const char* _pszLit2, const char* _pszLit3, ERetVal* _peRetVal )
{
	Reset();
	m_pszLit1   = _pszLit1;
	m_pszLit2   = _pszLit2;
	m_pszLit3   = _pszLit3;
	m_peRetVal  = _peRetVal;
}

inline void TInfoErr::Reset()  
{
	m_pszLit1       = "";
	m_pszLit2       = "";
	m_pszLit3       = "";
	m_peRetVal      = NULL; 
	m_bShowError    = true;
	m_bOptional     = false; 
}

#define CREATE_INFOERR( eRetVal ) TInfoErr oInfoErr( __FILE__, __FUNCTION__, &eRetVal );
