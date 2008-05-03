#pragma once

class CCommandQueue
{
	// Structures
	public:
		struct SNode
		{
			char* m_Data;
			SNode* m_Next;
		};

	// Members
	private:
		SNode* m_Head;
		int    m_Length;

	// Ctor
	public:
		CCommandQueue();
		~CCommandQueue();

	// Methods
		void  AddToBack( char* inString );
		char* TakeFromFront();
		int   GetLength();
};
