#pragma once
#include "Timer.h"
#include "Image.h"

class CGame;

class CBoard
{
	// Members
		private:
			CGame* m_Game;
			CImage m_Tiles[4];
			int m_Layout[4][4];
			int m_CameraZ;

	// Ctor
		public:
			CBoard();
			~CBoard();

	// Methods
		private:
		public:
			void SetGame( CGame* m_Game );
			void Update( TTimeUnit inTime );
			void Render();

			void MouseWheel( int inDistance );
}; 
