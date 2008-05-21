#pragma once
#include "Server.h"
#include "Client.h"
#include "Console.h"
#include "SyncPrimitive.h"
#include "CommandQueue.h"
#include "Timer.h"

class CGame
{
	// Members
		private:
			CServer   m_Server;
			CClient   m_Client;
			CConsole  m_Console;

			CTimer    m_Timer;

			CSyncPrimitive m_InputSyncPrimitive;
			CCommandQueue  m_InputCommandQueue;

	// Ctor
		public:
			CGame();
			~CGame();

	// Methods
		private:
		public:
			void ConsolePrint( char* inString );

			void Update( HWND inHWND );
			void Render();
			bool Keyboard( unsigned int inMessage, bool inKeyDownFlag );
			void HandleChar( char inChar );
			void ParseCommand( char* inString );
			void SendInput( char* inString );
};
