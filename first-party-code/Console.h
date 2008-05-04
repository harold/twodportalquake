#pragma once
#include "Timer.h"
#include "uGL.h"

class CConsole
{
	// Members
		private:
			bool  m_Active;
			float m_TargetY;
			float m_CurrentY;

	// Ctor
		public:
			CConsole();
			~CConsole();

	// Methods
		private:
		public:
			void Update( TTimeUnit inTime );
			void Render();

			void Toggle();
};