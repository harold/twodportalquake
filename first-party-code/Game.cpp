#include "Game.h"

CGame::CGame()
{
}

CGame::~CGame()
{

}
void CGame::Update()
{
	m_Server.Update();
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