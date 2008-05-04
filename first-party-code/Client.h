#pragma once
#include "Socket.h"
#include "Timer.h"

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
			void Update( TTimeUnit inTime );
			void Write( char* inString );

			void ConnectToServer( char* inHost, char* inPort );
};