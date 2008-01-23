#include "Game.h"
#include "Log.h"

CGame::CGame()
{
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
			m_Client.Write( theString );
			delete[] theString;
		}
	m_InputSyncPrimitive.Drop();

	Sleep( 2 );
}

void CGame::SendInput( char* inString )
{
	m_InputSyncPrimitive.Grab();
		m_InputCommandQueue.AddToBack( inString );
	m_InputSyncPrimitive.Drop();
}

void CGame::StartServer()
{
	m_Server.SetGame( this );
	m_Server.StartServer();
}

CServer* CGame::GetServer()
{
	return &m_Server;
}

void CGame::ClientWrite( char* inString )
{
	m_Client.Write( inString );
}