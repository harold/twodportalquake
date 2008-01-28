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
			int            m_CurrentPort;
			CServerSocket* m_Socket;

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
			void CServer::StartServer();

			int GetNextPort();

			CServerSocket*  CServer::GetSocket();
			CSyncPrimitive* CServer::GetSyncPrimitive();
			CCommandQueue*  CServer::GetCommandQueue();

			static void CServer::ServerThreadMain( void* inServer );
};