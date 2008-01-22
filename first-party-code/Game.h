#pragma once
#include "Server.h"
#include "Client.h"

class CGame
{
	// Members
		private:
			CServer m_Server;
			CClient m_Client;

	// Ctor
		public:
			CGame();
			~CGame();

	// Methods
		private:
		public:
			void CGame::Update();
			void CGame::StartServer();

			CServer* CGame::GetServer();

			void CGame::ClientWrite( char* inString );
};