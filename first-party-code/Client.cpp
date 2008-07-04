#include "Client.h"
#include "Log.h"

CClient::CClient( )
{
	m_PlayerNumber = -1;
	m_Socket = new CSocket( 42001 );
}

CClient::~CClient()
{
}

void CClient::SetGame( CGame* inGame )
{
	m_Game = inGame;
	m_World.SetGame( m_Game );
}

void CClient::Update( TTimeUnit inTime, HWND inHWND )
{
	m_UpdateDelta += inTime - m_LastTime;
	m_CurrentTime = inTime;

	sockaddr theSenderAddr;
	char* theString = m_Socket->Read( &theSenderAddr );
	int theInputLength = (int)strlen(theString);
	if( 0 != theInputLength )
	{
		CLog::Print( "Client hears: %s\n", theString );
		if( !strcmp( theString, "SomeString" ) )
		{
		}
		else if( !strcmp( theString, "SomeOtherString" ) )
		{
		}
		else
		{
		}
	}

	m_World.Update( inTime );

	m_LastTime = inTime;
}

void CClient::Render()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	m_World.Render();
}

bool CClient::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	return true;
}

void CClient::HandleChar( char inChar )
{
}

void CClient::ConnectToServer( char* inHost, char* inPort )
{
	addrinfo* theAddrInfo;
	getaddrinfo( inHost, inPort, 0, &theAddrInfo );
	if ( theAddrInfo )
	{
		m_ServerSockaddr.sa_family = theAddrInfo->ai_addr->sa_family;
		memcpy( m_ServerSockaddr.sa_data, theAddrInfo->ai_addr->sa_data, 14 );
		freeaddrinfo( theAddrInfo );
		m_Socket->Write( "RequestConnection", &m_ServerSockaddr );
	}
	else
	{
		CLog::Print( "%s:%s - Server not found :(", inHost, inPort );
	}
}

void CClient::Write( char* inString )
{
	m_Socket->Write( inString, &m_ServerSockaddr  );
}

void CClient::MouseWheel( int inDistance )
{
	m_World.MouseWheel( inDistance );
}
