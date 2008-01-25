#include "Game.h"
#include "Log.h"

CGame::CGame()
{
	m_Server.SetGame( this );
}

CGame::~CGame()
{
}

void CGame::Update()
{
	m_Server.Update();

	m_InputSyncPrimitive.Grab();
		char* theString = 0;
		while( theString = m_InputCommandQueue.TakeFromFront( ) )
		{
			CLog::Print( "Game processing input: " );
			CLog::Print( theString );
			CLog::Print( "\n" );
			ParseCommand( theString );
			delete[] theString;
		}
	m_InputSyncPrimitive.Drop();

	Sleep( 8 );
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
	if( 0 == strcmp( theToken, "StartServer" ) )
	{
		m_Server.StartServer( );
	}
	else if( 0 == strcmp( theToken, "ConnectToServer" ) )
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

		CLog::Print( "Connecting to Server..." );
		CLog::Print( "\n - Host: " );
		CLog::Print( theHost );
		CLog::Print( "\n - Port: " );
		CLog::Print( thePort );
		CLog::Print( "\n" );
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

CServer* CGame::GetServer( )
{
	return &m_Server;
}

void CGame::ClientWrite( char* inString )
{
	m_Client.Write( inString );
}