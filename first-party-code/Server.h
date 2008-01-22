#pragma once
#include "ServerSocket.h"
#include "SyncPrimitive.h"
#include "CommandQueue.h"
#include "LuaIncludes.h"

class CGame;

class CServer
{
	// Members
		private:
			CGame*  m_Game;
			CServerSocket m_Socket;

			CSyncPrimitive m_ServerSyncPrimitive;
			CCommandQueue  m_ServerCommandQueue;

			lua_State* m_LuaState;

	// Ctor
		public:
			CServer( );
			~CServer();

	// Methods
		private:
		public:
			void CServer::Update();
			void CServer::SetGame( CGame* inGame );
			void CServer::StartServer();

			CServerSocket* CServer::GetSocket();
			CSyncPrimitive* CServer::GetSyncPrimitive();
			CCommandQueue* CServer::GetCommandQueue();

			static void CServer::ServerThreadMain( void* inGame );
};