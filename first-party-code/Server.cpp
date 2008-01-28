#include "WindowsIncludes.h"
#include "Server.h"
#include "Game.h"
#include "Log.h"

CServer::CServer( )
{
	m_CurrentPort = 42000;
	m_Socket = new CServerSocket( m_CurrentPort );
	m_LuaState = luaL_newstate();
	luaL_openlibs( m_LuaState );
	luaL_dostring( m_LuaState, "STATE = 42" );
}

CServer::~CServer()
{

}

void CServer::Update()
{
	m_ServerSyncPrimitive.Grab();
		char* theString = 0;
		while( theString = m_ServerCommandQueue.TakeFromFront( ) )
		{
			CLog::Print( "Executing Lua Code: " );
			CLog::Print( theString );
			CLog::Print( "\n" );
			luaL_dostring( m_LuaState, theString );
			delete[] theString;
		}
	m_ServerSyncPrimitive.Drop();
/*
	lua_getglobal( m_LuaState, "STATE" );
	double x = lua_tonumber( m_LuaState, -1 );

	char theBuffer[80];
	sprintf( theBuffer, "Game State: %0.f", x );
	m_Socket.Write( theBuffer );

	lua_settop( m_LuaState, 0 );
*/
	Sleep( 8 );
}

void CServer::StartServer()
{
	CLog::Print( "Starting Server!\n" );
	_beginthread( CServer::ServerThreadMain, 0, this );
}

int CServer::GetNextPort()
{
	m_CurrentPort++;
	return m_CurrentPort;
}

CServerSocket* CServer::GetSocket()
{
	return m_Socket;
}

CSyncPrimitive* CServer::GetSyncPrimitive()
{
	return &m_ServerSyncPrimitive;
}

CCommandQueue* CServer::GetCommandQueue()
{
	return &m_ServerCommandQueue;
}

void CServer::ServerThreadMain( void* inServer )
{
	CServer* theServer = reinterpret_cast<CServer*>(inServer);
	CServerSocket* theSocket = theServer->GetSocket();

	char* theString;

	while( true )
	{
		theString = theSocket->Read();
		if( !theString )
		{
			Sleep( 8 );
			continue;
		}

		int theInputLength = (int)strlen(theString);
		if( theInputLength == 0 )
		{
			// Empty input
			continue;
		}

		// Copy string because tokenization apparently damages the original pointer.
		char* theStringCopy = new char[ theInputLength+1 ];
		strcpy( theStringCopy, theString );
		
		char* theToken = strtok( theStringCopy, " " );

		// Check for commands
		if( 0 == strcmp( theToken, "RequestConnection" ) )
		{
			// TODO: Fetch actual next port and sprintf this.
			int thePort = theServer->GetNextPort();
			char theResponse[80];
			sprintf( theResponse, "OkaySwitchPorts %d", thePort );
			theSocket->Write( theResponse );
		}
		else
		{
			theServer->GetSyncPrimitive()->Grab();
				theServer->GetCommandQueue()->AddToBack( theString );
			theServer->GetSyncPrimitive()->Drop();
		}

		delete[] theStringCopy;
	}
}
