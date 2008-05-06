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
	glColor3f( 0.0f, 0.0f, 0.8f );
	for( float i=-10; i<=10; i+=2 )
	{
		glVertex3f( i*25, 25*sin((i+((float)m_CurrentTime*0.01f))/2.0f), -10.0f );
	}
	glEnd();

	m_Console.Render();

	glFlush();
}

void CClient::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	if( 192 == inMessage && inKeyDownFlag ) // '~'
	{
		m_Console.Toggle();
	}

	m_Console.Keyboard( inMessage, inKeyDownFlag );
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

void CClient::Write( char* inString )
{
	m_Socket->Write( inString, &m_ServerSockaddr  );
}

