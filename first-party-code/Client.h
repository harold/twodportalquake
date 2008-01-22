#pragma once
#include "ClientSocket.h"

class CClient
{
	// Members
		private:
			CClientSocket m_Socket;

	// Ctor
		public:
			CClient( );
			~CClient();

	// Methods
		private:
		public:
			void CClient::Write( char* inString );
};