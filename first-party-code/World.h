#pragma once
#include "Types.h"

class CGame;
class CMoonMan;

class CWorld
{
	// Members
		private:
			CGame*    m_Game;
			CMoonMan* m_MoonMan;

	// Ctor
		public:
			CWorld();
			~CWorld();

	// Methods
		private:
		public:
			void SetGame( CGame* m_Game );
			void Update( TTimeUnit inTime );
			void Render();

			void MouseWheel( int inDistance );
}; 
