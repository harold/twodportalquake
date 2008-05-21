#include "WindowsIncludes.h"
#include "Server.h"
#include "Game.h"
#include "Log.h"

CServer::CServer( )
{
	m_ConnectedClientCount = 0;
	m_LastTime = 0;
	m_UpdateDelta = 0;
	m_Socket = NULL;
	m_LuaState = luaL_newstate();
	luaL_openlibs( m_LuaState );
	luaL_dostring( m_LuaState, "STATE = 42" );
}

CServer::~CServer()
{

}

void CServer::Update( TTimeUnit inTime )
{
	m_UpdateDelta += inTime - m_LastTime;
	if( !m_Socket )
	{
		// No server running!
		return;
	}

	sockaddr theSenderAddr;
	char* theString = m_Socket->Read( &theSenderAddr );
	int theInputLength = (int)strlen(theString);
	if( 0 != theInputLength )
	{
		// Copy string because tokenization apparently damages the original pointer.
		char* theStringCopy = new char[ theInputLength+1 ];
		strcpy( theStringCopy, theString );

		char* theToken = strtok( theStringCopy, " " );

		// Check for commands
		if( 0 == strcmp( theToken, "RequestConnection" ) )
		{
			CLog::Print( "Client requests connection!\n" );
			if( m_ConnectedClientCount < 2 )
			{
				memcpy( &m_ClientAddrs[ m_ConnectedClientCount ], &theSenderAddr, sizeof( sockaddr ) );
				char theBuffer[1024];
				sprintf( theBuffer, "SetPlayer%d", m_ConnectedClientCount );
				m_Socket->Write( theBuffer, &m_ClientAddrs[ m_ConnectedClientCount ] );
				m_ConnectedClientCount++;
			}
		}
		else
		{
			//CLog::Print( "Executing Lua Code: %s\n", theString );
			//luaL_dostring( m_LuaState, theString );
			if ( 'L' == theString[0] )
			{
				m_GameState.SetLeftPlayerY( atoi( theString+1 ) );
			}
			if ( 'R' == theString[0] )
			{
				m_GameState.SetRightPlayerY( atoi( theString+1 ) );
			}
		}

		delete[] theStringCopy;
	}

	if( m_UpdateDelta > 30 )
	{
		char theBuffer[128];
		sprintf( theBuffer, "%d %d", m_GameState.GetLeftPlayerY(), m_GameState.GetRightPlayerY() );
		for( int i=0; i<m_ConnectedClientCount; ++i )
		{
			m_Socket->Write( theBuffer, &m_ClientAddrs[ i ] );
		}
		m_UpdateDelta %= 30;
	}

	// TODO: select() to wait for data at server socket? (Or at game level?)

	m_LastTime = inTime;
}

void CServer::StartServer()
{
	CLog::Print( "Starting Server!\n" );
	m_Socket = new CSocket( 42000 );
}
