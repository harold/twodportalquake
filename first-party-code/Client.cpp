#include "Client.h"
#include "Log.h"

CClient::CClient( )
{
	_beginthread( CClient::ClientThreadMain, 0, this );
}

CClient::~CClient()
{

}

void CClient::Write( char* inString )
{
	m_Socket.Write( inString );
}

CCommandQueue* CClient::GetCommandQueue()
{
	return &m_ClientCommandQueue;
}

CSyncPrimitive* CClient::GetSyncPrimitive()
{
	return &m_ClientSyncPrimitive;
}

CClientSocket* CClient::GetSocket()
{
	return &m_Socket;
}

void CClient::ClientThreadMain( void* inClient )
{
	CClient* theClient = reinterpret_cast<CClient*>(inClient);
	CClientSocket* theSocket = theClient->GetSocket();

	char* theString;

	while( true )
	{
		theString = theSocket->Read();
		if( !theString )
		{
			Sleep( 8 );
			continue;
		}
/*
		CLog::Print( "Client receiving: " );
		CLog::Print( theString );
		CLog::Print( "\n" );
*/
		theClient->GetSyncPrimitive()->Grab();
			theClient->GetCommandQueue()->AddToBack( theString );
		theClient->GetSyncPrimitive()->Drop();
	}
}