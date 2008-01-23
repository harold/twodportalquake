#pragma once
#include "WindowsIncludes.h"

class CClientSocket
{
	// Members
	private:
		WSADATA m_WsaData;
		SOCKET  m_Socket;

		char m_IncomingBuffer[512];
		int  m_IncomingBufferSize;

		bool     m_SocketInitialized;
		sockaddr m_Sockaddr;
		int      m_SockaddrSize;

	// Ctor
	public:
		CClientSocket();
		~CClientSocket();

	// Methods
		char* Read();
		void Write( char* inString );
};