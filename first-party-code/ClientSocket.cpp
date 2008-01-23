#include <stdio.h>
#include "ClientSocket.h"

CClientSocket::CClientSocket()
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

	SetHostNameAndPort( "qa0104", "27017" );
}

CClientSocket::~CClientSocket()
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

void CClientSocket::SetHostNameAndPort( char* inHostName, char* inPort )
{
	sprintf( m_HostName, inHostName );
	sprintf( m_Port,     inPort );
}

char* CClientSocket::Read()
{
	return 0;
}

void CClientSocket::Write( char* inString )
{
	addrinfo* theAddrInfo = 0;
	getaddrinfo( m_HostName, m_Port, 0, &theAddrInfo );
	sendto( m_Socket, inString, (int)strlen( inString ), 0, theAddrInfo->ai_addr, (int)theAddrInfo->ai_addrlen );
}