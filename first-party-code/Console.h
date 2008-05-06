#pragma once
#include "Timer.h"
#include "Image.h"
#include "uGL.h"

class CConsole
{
	// Members
		private:
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
			void Update( TTimeUnit inTime );
			void Render();
			void RenderString( int inY, char* inString );
			void Keyboard( unsigned int inMessage, bool inKeyDownFlag );

			void Toggle();

			void Print( char* inString );
}; 
