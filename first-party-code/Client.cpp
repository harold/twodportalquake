#include "Client.h"
#include "Log.h"

CClient::CClient( )
{
	m_Socket = new CSocket( 42001 );
}

CClient::~CClient()
{
}

void CClient::Update()
{
	sockaddr theSenderAddr;
	char* theString = m_Socket->Read( &theSenderAddr );
	int theInputLength = (int)strlen(theString);
	if( 0 != theInputLength )
	{
		CLog::Print( "Client hears: " );
		CLog::Print( theString );
		CLog::Print( "\n" );
	}
}

void CClient::Write( char* inString )
{
	m_Socket->Write( inString, &m_ServerSockaddr  );
}

void CClient::ConnectToServer( char* inHost, char* inPort )
{
	addrinfo* theAddrInfo;
	getaddrinfo( inHost, inPort, 0, &theAddrInfo );
	m_ServerSockaddr.sa_family = theAddrInfo->ai_addr->sa_family;
	memcpy( m_ServerSockaddr.sa_data, theAddrInfo->ai_addr->sa_data, 14 );
	freeaddrinfo( theAddrInfo );
	m_Socket->Write( "RequestConnection", &m_ServerSockaddr );
}
