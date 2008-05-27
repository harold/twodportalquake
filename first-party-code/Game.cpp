#include "Game.h"
#include "Log.h"
#include "2dpq.h"

CGame::CGame( C2dpq* in2dpq )
{
	m_2dpq = in2dpq;
	m_Console.SetGame( this );
	m_Client.SetGame( this );
}

CGame::~CGame()
{
}

void CGame::Update( HWND inHWND )
{
	TTimeUnit theTime = m_Timer.GetTimeMilliSecs();
	m_Server.Update( theTime );
	m_Client.Update( theTime, inHWND );

	m_Console.Update( theTime );

	m_InputSyncPrimitive.Grab();
		char* theString = 0;
		while( theString = m_InputCommandQueue.TakeFromFront( ) )
		{
			CLog::Print( "Game processing input: %s\n", theString );
			ParseCommand( theString );
			delete[] theString;
		}
	m_InputSyncPrimitive.Drop();
}

void CGame::Render()
{
	m_Client.Render();
	m_Console.Render();

	glFlush();
}

bool CGame::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	if( 192 == inMessage && inKeyDownFlag ) // '~'
	{
		m_Console.Toggle();
		return false;
	}

	return m_Client.Keyboard( inMessage, inKeyDownFlag ) && m_Console.Keyboard( inMessage, inKeyDownFlag );
}

void CGame::HandleChar( char inChar )
{
	m_Client.HandleChar( inChar );
	m_Console.HandleChar( inChar );
}

void CGame::ParseCommand( char* inString )
{
	int theInputLength = (int)strlen(inString);
	if( theInputLength == 0 )
	{
		// Empty input
		return;
	}

	// Copy string because tokenization apparently damages the original pointer.
	char* theString = new char[ theInputLength+1 ];
	strcpy( theString, inString );
	
	char* theToken = strtok( theString, " " );

	// Check for commands
	if( 0 == strcmp( theToken, "StartServer" ) ||
		0 == strcmp( theToken, "SS" ) )
	{
		m_Server.StartServer( );
	}
	else if( 0 == strcmp( theToken, "ConnectToServer" ) ||
			 0 == strcmp( theToken, "CTS" ) )
	{
		char* theHost;
		char* thePort;
		theHost = strtok( 0, " " );
		thePort = strtok( 0, " " );
		if( theHost == 0 )
		{
			theHost = "localhost";
		}

		if( thePort == 0 )
		{
			thePort = "42000";
		}

		CLog::Print( "Connecting to Server...\n - Host: " );
		CLog::Print( theHost );
		CLog::Print( "\n - Port: " );
		CLog::Print( thePort );
		CLog::Print( "\n" );

		m_Client.ConnectToServer( theHost, thePort );
	}
	else
	{
        m_Client.Write( inString );
	}

	delete[] theString;
}

void CGame::SendInput( char* inString )
{
	m_InputSyncPrimitive.Grab();
		m_InputCommandQueue.AddToBack( inString );
	m_InputSyncPrimitive.Drop();
}

int CGame::GetScreenWidth()
{
	return m_2dpq->m_Window.m_Width;
}

int CGame::GetScreenHeight()
{
	return m_2dpq->m_Window.m_Height;
}

void CGame::MouseWheel( int inDistance )
{
	m_Client.MouseWheel( inDistance );
}
