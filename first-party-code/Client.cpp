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

void CClient::ConnectToServer( char* inHost, char* inPort )
{
	m_Socket.SetHostNameAndPort( inHost, inPort );
	m_Socket.Write( "RequestConnection" );
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
		if( 0 == strcmp( theToken, "OkaySwitchPorts" ) )
		{
			char* thePort;
			thePort = strtok( 0, " " );

			theSocket->SetHostNameAndPort( 0, thePort );
			theSocket->Write( "Hello!" );
		}
		else
		{
			theClient->GetSyncPrimitive()->Grab();
				theClient->GetCommandQueue()->AddToBack( theString );
			theClient->GetSyncPrimitive()->Drop();
		}

		delete[] theStringCopy;
	}
}