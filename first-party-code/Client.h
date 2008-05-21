#pragma once
#include "GameState.h"
#include "Socket.h"
#include "Timer.h"
#include "uGL.h"
#include <math.h>
#include "Board.h"

class CGame;

class CClient
{
	// Members
		private:
			CSocket*  m_Socket;
			sockaddr  m_ServerSockaddr;
			TTimeUnit m_CurrentTime;

			TTimeUnit  m_LastTime;
			TTimeUnit  m_UpdateDelta;

			int        m_PlayerNumber;
			CGameState m_GameState;
			CGame*     m_Game;
			CBoard     m_Board;

	// Ctor
		public:
			CClient();
			~CClient();

	// Methods
		private:
		public:
			void SetGame( CGame* inGame );
			void Update( TTimeUnit inTime, HWND inHWND );
			void Render();
			bool Keyboard( unsigned int inMessage, bool inKeyDownFlag );
			void HandleChar( char inChar );

			void ConnectToServer( char* inHost, char* inPort );
			void Write( char* inString );
};