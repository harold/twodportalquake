#include <string.h> // For strlen, strcpy

#include "CommandQueue.h"

CCommandQueue::CCommandQueue()
{
	m_Head = 0;
	m_Length = 0;
}

CCommandQueue::~CCommandQueue()
{
	char* theString = 0;
	while( theString = TakeFromFront() )
	{
		delete[] theString;
	}
}

void CCommandQueue::AddToBack( char* inString )
{
	m_Length++;

	// Empty list case:
	if( m_Head == 0 )
	{
		m_Head = new SNode;
		m_Head->m_Next = 0;
		m_Head->m_Data = new char[ strlen( inString ) + 1];
		strcpy( m_Head->m_Data, inString );

		return;
	}

	// Seek to the end
	SNode* theNode = m_Head;
	while( theNode->m_Next != 0 )
	{
		theNode = theNode->m_Next;
	}

	theNode->m_Next = new SNode;
	theNode->m_Next->m_Next = 0;
	theNode->m_Next->m_Data = new char[ strlen( inString ) + 1];
	strcpy( theNode->m_Next->m_Data, inString );

}

char* CCommandQueue::TakeFromFront()
{
	m_Length--;

	// Empty list case:
	if( m_Head == 0 )
	{
		return 0;
	}

	char* theOutAddress = m_Head->m_Data;
	SNode* theDropped = m_Head;
	m_Head = m_Head->m_Next;
	delete theDropped;

	return theOutAddress;
}

int CCommandQueue::GetLength()
{
	return m_Length;
}