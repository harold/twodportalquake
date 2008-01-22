#include "SyncPrimitive.h"


CSyncPrimitive::CSyncPrimitive( )
{
	m_Mutex = CreateMutex( NULL, FALSE, "SyncPrimitive" );
}

CSyncPrimitive::~CSyncPrimitive()
{
	ReleaseMutex( m_Mutex );
}

void CSyncPrimitive::Grab()
{
	WaitForSingleObject( m_Mutex, INFINITE );
}

void CSyncPrimitive::Drop()
{
	ReleaseMutex( m_Mutex );
}
