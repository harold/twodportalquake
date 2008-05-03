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

		char m_HostName[128];
		char m_Port[16];

		bool      m_SocketInitialized;

		addrinfo* m_AddrInfo;
		sockaddr* m_Sockaddr;
		int       m_SockaddrSize;

	// Ctor
	public:
		CClientSocket();
		~CClientSocket();

	// Methods
		void SetHostNameAndPort( char* inHostName, char* inPort );
		char* Read();
		void Write( char* inString );
};