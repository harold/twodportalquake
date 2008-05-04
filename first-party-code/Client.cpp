#include "Client.h"
#include "Log.h"

CClient::CClient( )
{
	m_Socket = new CSocket( 42001 );
}

CClient::~CClient()
{
}

void CClient::Update( TTimeUnit inTime )
{
	m_CurrentTime = inTime;
	sockaddr theSenderAddr;
	char* theString = m_Socket->Read( &theSenderAddr );
	int theInputLength = (int)strlen(theString);
	if( 0 != theInputLength )
	{
		CLog::Print( "Client hears: " );
		CLog::Print( theString );
		CLog::Print( "\n" );
	}

	m_Console.Update( inTime );
}

void CClient::Render()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glBegin( GL_LINE_STRIP );
	glColor3f( 0.0f, 0.0f, 0.2f );
	for( float i=-10; i<=10; i+=2 )
	{
		glVertex3f( i, 2*sin((i+((float)m_CurrentTime*0.01f))/2.0f), -10.0f );
	}
	glEnd();

	m_Console.Render();

	glFlush();
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

void CClient::ToggleConsole()
{
	m_Console.Toggle();
}
