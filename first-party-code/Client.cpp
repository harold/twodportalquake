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
		if( !strcmp( theString, "SetPlayer0" ) )
		{
			m_PlayerNumber = 0;
		}
		else if( !strcmp( theString, "SetPlayer1" ) )
		{
			m_PlayerNumber = 1;
		}
		else
		{
			int theLeft = 0;
			int theRight = 0;
			char* theStringCopy = new char[ strlen(theString)+1 ];
			strcpy( theStringCopy, theString );
			char* theToken = strtok( theStringCopy, " " );
			theLeft = atoi( theToken );
			theToken = strtok( 0, " " );
			theRight = atoi( theToken );
			delete[] theStringCopy;

			m_GameState.SetLeftPlayerY( theLeft );
			m_GameState.SetRightPlayerY( theRight );
		}
	}

	POINT theCursor;
    GetCursorPos( &theCursor );
    ScreenToClient( inHWND, &theCursor );
	char theBuffer[128];
	if( m_UpdateDelta > 60 )
	{
		if ( 0 == m_PlayerNumber )
		{
			sprintf( theBuffer, "L%d", 225-theCursor.y );
			m_Socket->Write( theBuffer, &m_ServerSockaddr );
		}
		if ( 1 == m_PlayerNumber )
		{
			sprintf( theBuffer, "R%d", 225-theCursor.y );
			m_Socket->Write( theBuffer, &m_ServerSockaddr );
		}
		m_UpdateDelta %= 60;
	}

	if ( 0 == m_PlayerNumber )
	{
		m_GameState.SetLeftPlayerY( 225-theCursor.y );
	}
	if ( 1 == m_PlayerNumber )
	{
		m_GameState.SetRightPlayerY( 225-theCursor.y );
	}

	m_LastTime = inTime;
}

void CClient::Render()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	glLoadIdentity();
/*
	glBegin( GL_LINE_STRIP );
	glColor3f( 0.0f, 0.0f, 0.8f );
	for( float i=-10; i<=10; i+=2 )
	{
		glVertex3f( i*25, 25*sin((i+((float)m_CurrentTime*0.01f))/2.0f), -10.0f );
	}
	glEnd();
*/
	glBegin( GL_TRIANGLES );
		glColor3f( 1, 1, 1 );
		// Left player
		glVertex3f( -395, m_GameState.GetLeftPlayerY()+50, -10.f );
		glVertex3f( -385, m_GameState.GetLeftPlayerY()+50, -10.f );
		glVertex3f( -395, m_GameState.GetLeftPlayerY()-50, -10.f );
		glVertex3f( -395, m_GameState.GetLeftPlayerY()-50, -10.f );
		glVertex3f( -385, m_GameState.GetLeftPlayerY()+50, -10.f );
		glVertex3f( -385, m_GameState.GetLeftPlayerY()-50, -10.f );
		// Right player
		glVertex3f( 395, m_GameState.GetRightPlayerY()+50, -10.f );
		glVertex3f( 385, m_GameState.GetRightPlayerY()+50, -10.f );
		glVertex3f( 395, m_GameState.GetRightPlayerY()-50, -10.f );
		glVertex3f( 395, m_GameState.GetRightPlayerY()-50, -10.f );
		glVertex3f( 385, m_GameState.GetRightPlayerY()+50, -10.f );
		glVertex3f( 385, m_GameState.GetRightPlayerY()-50, -10.f );
		// Ball
		glColor3f( 0.5f, 0.5f, 1 );
		glVertex3f( m_GameState.GetBallX()-3, m_GameState.GetBallY()+3, -10.f );
		glVertex3f( m_GameState.GetBallX()+3, m_GameState.GetBallY()+3, -10.f );
		glVertex3f( m_GameState.GetBallX()-3, m_GameState.GetBallY()-3, -10.f );
		glVertex3f( m_GameState.GetBallX()-3, m_GameState.GetBallY()-3, -10.f );
		glVertex3f( m_GameState.GetBallX()+3, m_GameState.GetBallY()+3, -10.f );
		glVertex3f( m_GameState.GetBallX()+3, m_GameState.GetBallY()-3, -10.f );
	glEnd();
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

