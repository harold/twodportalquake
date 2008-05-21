#pragma once

class CGameState
{
	// Members
		private:
			int m_LeftPlayerY;
			int m_RightPlayerY;
			int m_BallX;
			int m_BallY;

	// Ctor
		public:
			CGameState();
			~CGameState();

	// Methods
		private:
		public:
			int GetLeftPlayerY();
			int GetRightPlayerY();
			int GetBallX();
			int GetBallY();

			void SetLeftPlayerY( int inY );
			void SetRightPlayerY( int inY );
			void SetBallX( int inX );
			void SetBallY( int inY );
};