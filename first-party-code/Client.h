#pragma once
#include "ClientSocket.h"
#include "SyncPrimitive.h"
#include "CommandQueue.h"

class CClient
{
	// Members
		private:
			CClientSocket  m_Socket;
			CSyncPrimitive m_ClientSyncPrimitive;
			CCommandQueue  m_ClientCommandQueue;

	// Ctor
		public:
			CClient( );
			~CClient();

	// Methods
		private:
		public:
			void CClient::Write( char* inString );

			CCommandQueue* GetCommandQueue();
			CSyncPrimitive* GetSyncPrimitive();

			CClientSocket* GetSocket();
			static void ClientThreadMain( void* inClient );
};