#pragma once
#include "Server.h"
#include "Client.h"

class CGame
{
	// Members
		private:
			CServer m_Server;
			CClient m_Client;

			CSyncPrimitive m_InputSyncPrimitive;
			CCommandQueue  m_InputCommandQueue;

	// Ctor
		public:
			CGame();
			~CGame();

	// Methods
		private:
		public:
			void CGame::Update();
			void CGame::ParseCommand( char* inString );
			void CGame::SendInput( char* inString );
};