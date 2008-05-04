#pragma once
#include "Server.h"
#include "Client.h"
#include "SyncPrimitive.h"
#include "CommandQueue.h"
#include "Timer.h"

class CGame
{
	// Members
		private:
			CServer m_Server;
			CClient m_Client;

			CTimer  m_Timer;

			CSyncPrimitive m_InputSyncPrimitive;
			CCommandQueue  m_InputCommandQueue;

	// Ctor
		public:
			CGame();
			~CGame();

	// Methods
		private:
		public:
			void Update();
			void Render();
			void ParseCommand( char* inString );
			void SendInput( char* inString );

			void ToggleConsole();
};