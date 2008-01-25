#include "WindowsIncludes.h"
#include "Server.h"
#include "Game.h"
#include "Log.h"

CServer::CServer( )
{
	m_LuaState = luaL_newstate();
	luaL_openlibs( m_LuaState );
	luaL_dostring( m_LuaState, "STATE = 0" );
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

	Sleep( 8 );
}

void CServer::SetGame( CGame* inGame )
{
	m_Game = inGame;
}

void CServer::StartServer()
{
	CLog::Print( "Starting Server!\n" );
	_beginthread( CServer::ServerThreadMain, 0, this->m_Game );
}

CServerSocket* CServer::GetSocket()
{
	return &m_Socket;
}

CSyncPrimitive* CServer::GetSyncPrimitive()
{
	return &m_ServerSyncPrimitive;
}

CCommandQueue* CServer::GetCommandQueue()
{
	return &m_ServerCommandQueue;
}

void CServer::ServerThreadMain( void* inGame )
{
	CGame* theGame = reinterpret_cast<CGame*>(inGame);
	CServer* theServer = theGame->GetServer();
	CServerSocket* theSocket = theServer->GetSocket();

	char* theString;

	while( true )
	{
		theString = theSocket->Read();
		theServer->GetSyncPrimitive()->Grab();
			theServer->GetCommandQueue()->AddToBack( theString );
		theServer->GetSyncPrimitive()->Drop();

		theSocket->Write( "Hello from the server!" );
	}
}
