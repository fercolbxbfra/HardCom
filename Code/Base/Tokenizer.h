//////////////////////////////////////////////////////////////////////////
// separates a text in its basic components (tokens). Used as tool from other modules to parse setup files, scripts and stuff

#pragma once

class CTokenizer
{
	public:
		
		struct TToken
		{
			const char* pszToken;
			int         iLineNum;
		};
				
		
	public:
			
																	CTokenizer              () { m_bOk = false; }
																	~CTokenizer              ();

			ERetVal                     Init                    ( const char* _pszAtomicTokens = NULL, const char* _pszSeparadores = NULL, bool _bSpaceIsSeparator = true );

			ERetVal                     DoParseFile             ( const char* _pszFileName, bool _bNoPack = false, bool _bLookInAndOutPack = false );
			ERetVal                     DoParseFile             ( const char* _pszDir, const char* _pszFileName, bool _bNoPack = false, bool _bLookInAndOutPack = false );
			ERetVal                     DoParseBuffer           ( const char* _pszBuffer, uint _uTam );
				
			uint                        GetNumTokens            () const { return m_uNumTokens; }
			const TToken*               GetToken                ( uint _uToken ) const;
			bool                        GetTokenValueBool       ( uint _uToken ) const;
			int                         GetTokenValueInt        ( uint _uToken ) const;
			float                       GetTokenValueFloat      ( uint _uToken ) const;
			const char*                 GetTokenStr             ( uint _uToken ) const;
			char                        GetTokenChar            ( uint _uToken ) const;
			int                         GetTokenLineNum         ( uint _uToken ) const;
			const char*                 GetFileName             () const { return m_pszFileName; }
				
				
	private:
		
			void                        ProcessBuffer           ( bool _bSoloContar );
			ERetVal                     ReadFile                ( const char* _pszNombreFile, bool _bNoPack = false, bool _bLookInAndOutPack = false );
				
			bool                        IsFinal                 ( uint uPunt ) { return uPunt>=m_uSizeBuffer; }
			bool                        IsSeparator             ( uint _uPunt );
			bool                        IsCharAtomicToken       ( uint _uPunt );
			bool                        IsCharNormalToken		    ( uint _uPunt );
			bool                        IsCharStringDelimiter   ( uint _uPunt );
			bool                        IsCharCR                ( uint _uPunt );
			bool                        IsRemLine               ( uint _uPunt );
			bool                        IsRemBlockStart         ( uint _uPunt );
			bool                        IsRemBlockEnd           ( uint _uPunt );
			bool                        IsDoubleChar            ( const char* _psz, uint _uPunt );
			bool                        IsEndOfLine             ( uint _uPunt );
						

	private:
				
			char*                       m_pBuffer;
			char*                       m_pBufferTokens;  // shared memory for all the tokens.
			uint                        m_uSizeBufferTokens;
			uint                        m_uSizeBuffer;
			uint                        m_uNumTokens;
			TToken*                     m_paTokens;
			char*                       m_pszFileName; //...only used to show filename in case of error
			bool                        m_bOk;
			bool                        m_bDataParsed;
				
			char*                       m_pszAtomicTokens;
			char*                       m_pszSeparators;
			int                         m_iLowAsciiSeparator;
};