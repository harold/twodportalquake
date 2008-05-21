#pragma once
#include "GameState.h"
#include "Socket.h"
#include "Timer.h"
#include "uGL.h"
#include <math.h>

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

	// Ctor
		public:
			CClient();
			~CClient();

	// Methods
		private:
		public:
			void Update( TTimeUnit inTime, HWND inHWND );
			void Render();
			bool Keyboard( unsigned int inMessage, bool inKeyDownFlag );
			void HandleChar( char inChar );

			void ConnectToServer( char* inHost, char* inPort );
			void Write( char* inString );
};