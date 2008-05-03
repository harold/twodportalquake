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
			void Write( char* inString );

			CCommandQueue*  GetCommandQueue();
			CSyncPrimitive* GetSyncPrimitive();
			CClientSocket*  GetSocket();

			void ConnectToServer( char* inHost, char* inPort );

			static void ClientThreadMain( void* inClient );
};