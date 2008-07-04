#pragma once
#include "Types.h"
#include "Image.h"
#include "uGL.h"

class CGame;

class CConsole
{
	// Members
		private:
			CGame* m_Game;

			bool   m_Active;
			float  m_TargetY;
			float  m_CurrentY;

			char*  m_Lines[8];
			int    m_LineCursorIndex;

			char   m_InputBuffer[128];

			CImage m_Font;

	// Ctor
		public:
			CConsole();
			~CConsole();

	// Methods
		private:
		public:
			void SetGame( CGame* inGame );
			void Update( TTimeUnit inTime );
			void Render();
			void RenderString( int inScreenWidth, int inY, char* inString );
			bool Keyboard( unsigned int inMessage, bool inKeyDownFlag );
			void HandleChar( char inChar );

			void Toggle();

			void Print( char* inString );
}; 
