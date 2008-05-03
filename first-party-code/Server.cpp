#include "WindowsIncludes.h"
#include "Server.h"
#include "Game.h"
#include "Log.h"

CServer::CServer( )
{
	m_ConnectedClientCount = 0;
	m_Socket = 0;
	m_LuaState = luaL_newstate();
	luaL_openlibs( m_LuaState );
	luaL_dostring( m_LuaState, "STATE = 42" );
}

CServer::~CServer()
{

}

void CServer::Update()
{
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
				m_Socket->Write( "OkayLet'sPlay", &m_ClientAddrs[ m_ConnectedClientCount ] );
				m_ConnectedClientCount++;
			}
		}
		else
		{
			CLog::Print( "Executing Lua Code: " );
			CLog::Print( theString );
			CLog::Print( "\n" );
			luaL_dostring( m_LuaState, theString );
		}

		delete[] theStringCopy;
	}

/*
	lua_getglobal( m_LuaState, "STATE" );
	double x = lua_tonumber( m_LuaState, -1 );

	char theBuffer[80];
	sprintf( theBuffer, "Game State: %0.f", x );
	m_Socket.Write( theBuffer );

	lua_settop( m_LuaState, 0 );
*/

	// TODO: select() to wait for data at server socket? (Or at game level?)
}

void CServer::StartServer()
{
	CLog::Print( "BEGIN: Starting Server!\n" );
	m_Socket = new CSocket( 42000 );
	CLog::Print( "END:   Starting Server!\n" );
}