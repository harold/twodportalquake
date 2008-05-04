#pragma once
#include "Socket.h"
#include "Timer.h"
#include "Console.h"
#include "uGL.h"
#include <math.h>

class CClient
{
	// Members
		private:
			CSocket*  m_Socket;
			sockaddr  m_ServerSockaddr;
			TTimeUnit m_CurrentTime;
			CConsole  m_Console;

	// Ctor
		public:
			CClient();
			~CClient();

	// Methods
		private:
		public:
			void Update( TTimeUnit inTime );
			void Render();
			void Write( char* inString );

			void ConnectToServer( char* inHost, char* inPort );

			void ToggleConsole();
};