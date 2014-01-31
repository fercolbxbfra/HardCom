//----------------------------------------------------------------------------
// an string name (of limited size) used that can be used as identifier because is very efficiently managed
//----------------------------------------------------------------------------

#pragma once


class CNameID
{
	public:
			
																CNameID                 ();
																CNameID                 ( const char* _pszName );
																	 
		void                        Set                     ( const char* _pszName );
		void                        Set                     ( const char* _pszStr1, const char* _pszStr2 );
		void                        SetFmt                  ( const char* _pszFmt, ... );
		void                        SetNull                 () { Clear(); }
		bool                        IsNull                  () const { return m_szName[0]==0; }
		void                        SetFromRoot             ( const char* _pszRaiz, int _iCantNumbers, int _iNumber, const char* _pszSeparator = NULL );
		void                        SetFromRootFmt          ( int _iNumNumbers, int _iNumber, const char* _pszFmt, ... );
		const char*                 GetStr                  () const { return m_szName; }
		char*                       GetPointer              () { return m_szName; }
		void                        StrCat                  ( const char* _psz );
		int                         operator==              ( const CNameID& _NameID ) const { return IsEqual( _NameID ); }
		int                         operator==              ( const char* _pszName ) const { return IsEqual( _pszName ); }
		int                         operator!=              ( const CNameID& _NameID ) const { return !IsEqual( _NameID ); }
		int                         operator!=              ( const char* _pszName ) const { return !IsEqual( _pszName ); }
		bool                        IsRootEqual             ( const char* _pszRoot ) const;
		void                        RemoveFileExt           ();
		void                        SetUpperCase            ();
				
		//...not optimized, so careful with those
		int                         operator<               ( const CNameID& _NameID ) const { return strcmp( m_szName, _NameID.GetStr() )<0; }
		int                         operator<               ( const char* _pszName ) const { return strcmp( m_szName, _pszName )<0; }
																	 

		enum { NAMEID_SIZE = 32, NAMEID_USABLESIZE = NAMEID_SIZE - 1 };
				
				
	private:
		
		void                        Clear                   ();
		bool                        IsEqual                 ( const char* _pszName ) const;
		bool                        IsEqual                 ( const CNameID& _NameID ) const;
		
												
	private:
		
		union
		{
			char                m_szName[ NAMEID_SIZE ];
			struct 
			{
				__int64         m_i64Part0;
				__int64         m_i64Part1;
				__int64         m_i64Part2;
				__int64         m_i64Part3;
			};
		};
}; 

extern const CNameID    cNameID_Null;


//////////////////////////////////////////////////////////////////////////

inline bool CNameID::IsEqual ( const CNameID& _NameID ) const
{
	ASSERT( NAMEID_SIZE==32 );
		
	return ( _NameID.m_i64Part0==m_i64Part0 && _NameID.m_i64Part1==m_i64Part1 && _NameID.m_i64Part2==m_i64Part2 &&
						_NameID.m_i64Part3==m_i64Part3 );
}
