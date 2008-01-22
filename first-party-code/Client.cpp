#include "Client.h"


CClient::CClient( )
{

}

CClient::~CClient()
{

}

void CClient::Write( char* inString )
{
	m_Socket.Write( inString );
}