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
			void RenderString( char* inString );

			void Toggle();
}; 
