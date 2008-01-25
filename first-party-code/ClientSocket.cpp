#include <stdio.h>
#include "ClientSocket.h"
#include "Log.h"

CClientSocket::CClientSocket()
{
	m_IncomingBufferSize = sizeof(m_IncomingBuffer);
	m_SocketInitialized = false;
	int theResult = 0;

    theResult = WSAStartup(MAKEWORD(2,2), &m_WsaData);
    if (theResult != 0) {
        printf("WSAStartup failed: %d\n", theResult);
    }

	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_Socket == INVALID_SOCKET) {
        printf("socket failed: %ld\n", WSAGetLastError());
        WSACleanup();
    }

	SetHostNameAndPort( "localhost", "42000" );
}

CClientSocket::~CClientSocket()
{
	freeaddrinfo( m_AddrInfo );

	int theResult = 0;

	// shutdown the connection since we're done
    theResult = shutdown(m_Socket, SD_SEND);
    if (theResult == SOCKET_ERROR) {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(m_Socket);
        WSACleanup();
    }

    // cleanup
    closesocket(m_Socket);
    WSACleanup();
}

void CClientSocket::SetHostNameAndPort( char* inHostName, char* inPort )
{
	strcpy( m_HostName, inHostName );
	strcpy( m_Port,     inPort );

	getaddrinfo( m_HostName, m_Port, 0, &m_AddrInfo );
	m_Sockaddr = m_AddrInfo->ai_addr;
	m_SockaddrSize = sizeof(sockaddr);
}

char* CClientSocket::Read()
{
	if( !m_SocketInitialized )
	{
		return 0;
	}

	int theResult = 0;
	theResult = recvfrom( m_Socket, m_IncomingBuffer, m_IncomingBufferSize, 0, m_Sockaddr, &m_SockaddrSize );
	if (theResult > 0)
	{
		m_SocketInitialized = true;
		m_IncomingBuffer[ theResult ] = '\n';
		m_IncomingBuffer[ theResult+1 ] = 0;
		printf("Client: Bytes received: %d\n", theResult);
		CLog::Print( "Client Socket received: " );
		CLog::Print( m_IncomingBuffer );
	}
	else if (theResult == 0)
	{
		sprintf( m_IncomingBuffer, "" );
		printf("Client: Bytes received: %d\n", theResult);
	}
	else
	{
		sprintf( m_IncomingBuffer, "" );
		printf("Client: recv failed: %d\n", WSAGetLastError());
	}

	return m_IncomingBuffer;
}

void CClientSocket::Write( char* inString )
{
	int theSendResult = 0;
	theSendResult = sendto( m_Socket, inString, (int)strlen( inString ), 0, m_Sockaddr, m_SockaddrSize );
	if (theSendResult == SOCKET_ERROR) {
		printf("Client: send failed: %d\n", WSAGetLastError());
	}
	printf("Client: Bytes sent: %d\n", theSendResult);

	m_SocketInitialized = true;
}