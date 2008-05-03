#pragma once
#include "Socket.h"

class CClient
{
	// Members
		private:
			CSocket* m_Socket;
			sockaddr m_ServerSockaddr;

	// Ctor
		public:
			CClient( );
			~CClient();

	// Methods
		private:
		public:
			void Update();
			void Write( char* inString );

			void ConnectToServer( char* inHost, char* inPort );
};