//----------------------------------------------------------------------------
// ErroresDX
//
// functions to visualize any DX error
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "DXErrors.h"
#include "Log.h"

#include <Dinput.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Mmsystem.h>
#include <DSound.h>



static struct
{
	HRESULT nErr;
	const char *pszError;
} stb_Err[] = 
{
	{ D3DERR_INVALIDCALL,             "D3DERR_INVALIDCALL"             }, 
	{ D3DERR_NOTAVAILABLE,            "D3DERR_NOTAVAILABLE"            },
	{ D3DERR_OUTOFVIDEOMEMORY,        "D3DERR_OUTOFVIDEOMEMORY"        },
	{ D3DERR_INVALIDDEVICE,           "D3DERR_INVALIDDEVICE"           },
	{ D3DERR_DEVICELOST,              "D3DERR_DEVICELOST"              },
	{ D3DERR_DRIVERINTERNALERROR,     "D3DERR_DRIVERINTERNALERROR"     },

	{ D3DXERR_INVALIDDATA,            "D3DXERR_INVALIDDATA"            },
	{ D3DXERR_CANNOTMODIFYINDEXBUFFER, "D3DXERR_CANNOTMODIFYINDEXBUFFER" },
	{ D3DXERR_INVALIDMESH,            "D3DXERR_INVALIDMESH"            },
	{ D3DXERR_CANNOTATTRSORT,         "D3DXERR_CANNOTATTRSORT"         },
	{ D3DXERR_SKINNINGNOTSUPPORTED,   "D3DXERR_SKINNINGNOTSUPPORTED"   },
	{ D3DXERR_TOOMANYINFLUENCES,      "D3DXERR_TOOMANYINFLUENCES"      },
	{ D3DXERR_INVALIDDATA,            "D3DXERR_INVALIDDATA"            },
	{ D3DXERR_LOADEDMESHASNODATA,     "D3DXERR_LOADEDMESHASNODATA"     },

	{ DIERR_BETADIRECTINPUTVERSION,   "DIERR_BETADIRECTINPUTVERSION"   }, 
	{ DIERR_INVALIDPARAM,             "DIERR_INVALIDPARAM"             },
	{ DIERR_OLDDIRECTINPUTVERSION,    "DIERR_OLDDIRECTINPUTVERSION"    },
	{ DIERR_OUTOFMEMORY,              "DIERR_OUTOFMEMORY"              },
	{ DIERR_DEVICENOTREG,             "DIERR_DEVICENOTREG"             },
	{ DIERR_NOINTERFACE,              "DIERR_NOINTERFACE"              },
	{ DIERR_NOTINITIALIZED,           "DIERR_NOTINITIALIZED"           },
	{ DIERR_ACQUIRED,                 "DIERR_ACQUIRED"                 },
	{ DIERR_NOTACQUIRED,              "DIERR_NOTACQUIRED"              },
	{ DIERR_NOTEXCLUSIVEACQUIRED,     "DIERR_NOTEXCLUSIVEACQUIRED"     },
	{ DIERR_OBJECTNOTFOUND,           "DIERR_OBJECTNOTFOUND"           },
	{ DIERR_UNSUPPORTED,              "DIERR_UNSUPPORTED"              },
	{ DIERR_NOTBUFFERED,              "DIERR_NOTBUFFERED"              },
	{ DIERR_INPUTLOST,                "DIERR_INPUTLOST"                },

	{ E_HANDLE,                       "E_HANDLE"                       },
	{ E_OUTOFMEMORY,                  "E_OUTOFMEMORY"                  },
	
	{ DSERR_ALLOCATED,                "DSERR_ALLOCATED"                },
	{ DSERR_BADFORMAT,                "DSERR_BADFORMAT"                   },
	{ DSERR_BUFFERTOOSMALL,           "DSERR_BUFFERTOOSMALL"              },
	{ DSERR_CONTROLUNAVAIL,           "DSERR_CONTROLUNAVAIL"              },
	{ DSERR_DS8_REQUIRED,             "DSERR_DS8_REQUIRED"                },
	{ DSERR_INVALIDCALL,              "DSERR_INVALIDCALL"                 },
	{ DSERR_INVALIDPARAM,             "DSERR_INVALIDPARAM"                },
	{ DSERR_NOAGGREGATION,            "DSERR_NOAGGREGATION"               },
	{ DSERR_OUTOFMEMORY,              "DSERR_OUTOFMEMORY"                 },
	{ DSERR_UNINITIALIZED,            "DSERR_UNINITIALIZED"               },
	{ DSERR_UNSUPPORTED,              "DSERR_UNSUPPORTED"                 },
	
	{ DI_BUFFEROVERFLOW,              "DI_BUFFEROVERFLOW"              },
	
};

//////////////////////////////////////////////////////////////////////////

ERetVal CheckDXError( int hr, const char* pszDXFunction, const char* pszFunction, const char* pszFile, bool bAssert )
{
	ERetVal RetVal;

	if (hr==D3D_OK) 
		RetVal = RET_OK;
	else
	{
		RetVal = RET_ERR;

		const char *pszError   = "UNKNOWN ERROR";

		for (uint i=0; i<sizeof(stb_Err)/sizeof(stb_Err[0]); i++)
		{
			if (hr==stb_Err[i].nErr)
				pszError = stb_Err[i].pszError;
		}
		const char* pszFormat = "ERR: DX ERROR: %s. (%d) \n   - DX func: %s\n   - file: %s\n   - func: %s";

		LOG(( pszFormat, pszError, hr, pszDXFunction, pszFile, pszFunction));
				
		ASSERTM( !bAssert, (pszFormat, pszError, hr, pszDXFunction, pszFile, pszFunction));
				
		#ifndef _ASSERTS_
		exit(0);
		#endif 
	}
		
	return RetVal;
}
