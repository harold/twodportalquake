#include <stdio.h>
#include "Socket.h"
#include "Log.h"

CSocket::CSocket( int inPort )
{
	m_IncomingBufferSize = sizeof(m_IncomingBuffer);
	m_SockaddrSize = sizeof(sockaddr);
	int theResult = 0;

    if (0!=(theResult = WSAStartup(MAKEWORD(2,2), &m_WsaData))) {
        printf("WSAStartup failed: %d\n", theResult);
    }

	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_Socket == INVALID_SOCKET) {
        printf("socket failed: %ld\n", WSAGetLastError());
        WSACleanup();
    }

	// Non-blocking, pls
	unsigned long theYesPlease = 1;
	if (-1 == ioctlsocket(m_Socket, FIONBIO, &theYesPlease))
	{
		printf("WARNING: UDP_OpenSocket: ioctl FIONBIO: %s\n", WSAGetLastError());
	}

	sockaddr_in theSockaddrIn;
	theSockaddrIn.sin_family = AF_INET;
	theSockaddrIn.sin_addr.s_addr = INADDR_ANY;
	theSockaddrIn.sin_port = htons( inPort );

    if (SOCKET_ERROR == bind( m_Socket, (sockaddr*)&theSockaddrIn, sizeof(sockaddr) )) {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket( m_Socket );
        WSACleanup();
    }
}

CSocket::~CSocket()
{
	// shutdown the connection since we're done
    if (SOCKET_ERROR == shutdown(m_Socket, SD_SEND)) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(m_Socket);
        WSACleanup();
    }

    // cleanup
    closesocket(m_Socket);
    WSACleanup();
}

char* CSocket::Read()
{
	int theIncomingBufferSize = 0;
	sockaddr theSender;
	theIncomingBufferSize = recvfrom( m_Socket, m_IncomingBuffer, m_IncomingBufferSize, 0, &theSender, &m_SockaddrSize );
	if (theIncomingBufferSize > 0)
	{
		printf("Socket: Bytes received: %d\n", theIncomingBufferSize);
		m_IncomingBuffer[ theIncomingBufferSize ] = 0;
		CLog::Print( "Data: " );
		CLog::Print( m_IncomingBuffer );
		CLog::Print( "\n" );
	}
	else if (theIncomingBufferSize == 0)
	{
		printf("Socket: Bytes received: %d\n", theIncomingBufferSize);
		sprintf( m_IncomingBuffer, "" );
	}
	else
	{
		sprintf( m_IncomingBuffer, "" );
		// Most likely just WSAEWOULDBLOCK
		//printf("Socket: recv failed: %d\n", WSAGetLastError());
	}

	return m_IncomingBuffer;
}

void CSocket::Write( char* inString, sockaddr* theRecipient )
{
	int theSendResult = 0;
	theSendResult = sendto( m_Socket, inString, (int)strlen(inString), 0, theRecipient, m_SockaddrSize );
    if (theSendResult == SOCKET_ERROR) {
        printf("Socket: send failed: %d\n", WSAGetLastError());
    }
    printf("Socket: Bytes sent: %d\n", theSendResult);
}
