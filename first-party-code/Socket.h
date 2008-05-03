#pragma once
#include "WindowsIncludes.h"

class CSocket
{
	// Members
	private:
		WSADATA m_WsaData;
		SOCKET  m_Socket;
		int     m_SockaddrSize;

		char    m_IncomingBuffer[512];
		int     m_IncomingBufferSize;

	// Ctor
	public:
		CSocket( int inPort );
		~CSocket();

	// Methods
		char* Read( sockaddr* theSenderAddr );
		void Write( char* inString, sockaddr* theRecipient );
};