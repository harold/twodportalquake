#include <stdio.h>
#include "ServerSocket.h"
#include "Log.h"

CServerSocket::CServerSocket( int inPort )
{
	m_IncomingBufferSize = sizeof(m_IncomingBuffer);
	m_SockaddrSize = sizeof(sockaddr);
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

	sockaddr_in theServerSockaddr;
	theServerSockaddr.sin_family = AF_INET;
	theServerSockaddr.sin_addr.s_addr = INADDR_ANY;
	theServerSockaddr.sin_port = htons( inPort );

	theResult = bind( m_Socket, (sockaddr*)&theServerSockaddr, sizeof(sockaddr) );
    if (theResult == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket( m_Socket );
        WSACleanup();
    }
}

CServerSocket::~CServerSocket()
{
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

char* CServerSocket::Read()
{
	int theResult = 0;
	theResult = recvfrom( m_Socket, m_IncomingBuffer, m_IncomingBufferSize, 0, &m_Sockaddr, &m_SockaddrSize );
	if (theResult > 0)
	{
		m_SocketInitialized = true;
		m_IncomingBuffer[ theResult ] = 0;
		printf("Server: Bytes received: %d\n", theResult);
		CLog::Print( "Server Socket received: " );
		CLog::Print( m_IncomingBuffer );
		CLog::Print( "\n" );
	}
	else if (theResult == 0)
	{
		sprintf( m_IncomingBuffer, "" );
		printf("Server: Bytes received: %d\n", theResult);
	}
	else
	{
		sprintf( m_IncomingBuffer, "" );
		printf("Server: recv failed: %d\n", WSAGetLastError());
	}

	return m_IncomingBuffer;
}

void CServerSocket::Write( char* inString )
{
	if( m_SocketInitialized )
	{
		int theSendResult = 0;
		theSendResult = sendto( m_Socket, inString, (int)strlen(inString), 0, &m_Sockaddr, m_SockaddrSize );
        if (theSendResult == SOCKET_ERROR) {
            printf("Server: send failed: %d\n", WSAGetLastError());
        }
        printf("Server: Bytes sent: %d\n", theSendResult);
	}
	else
	{
		CLog::Print( "." );
		//CLog::Print( "Socket was not initialized and we tried to write to it.\n" );
	}
}