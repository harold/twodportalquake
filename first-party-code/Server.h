#pragma once
#include "Socket.h"
#include "LuaIncludes.h"

class CGame;

class CServer
{
	// Members
		private:
			CSocket*       m_Socket;
			lua_State*     m_LuaState;

	// Ctor
		public:
			CServer( );
			~CServer();

	// Methods
		private:
		public:
			void CServer::Update();
			void CServer::StartServer();
};