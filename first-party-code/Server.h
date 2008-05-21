#pragma once
#include "GameState.h"
#include "Socket.h"
#include "LuaIncludes.h"
#include "Timer.h"

class CGame;

class CServer
{
	// Members
		private:
			CSocket*   m_Socket;
			lua_State* m_LuaState;

			TTimeUnit  m_LastTime;
			TTimeUnit  m_UpdateDelta;

			int        m_ConnectedClientCount;
			sockaddr   m_ClientAddrs[2]; // MAX_PLAYERS

			CGameState m_GameState;


	// Ctor
		public:
			CServer();
			~CServer();

	// Methods
		private:
		public:
			void CServer::Update( TTimeUnit inTime );
			void CServer::StartServer();
};