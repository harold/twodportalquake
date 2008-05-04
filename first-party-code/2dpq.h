#pragma once

#include "Game.h"
#include "uGL.h"

class C2dpq : public CuGL
{
	//-------------------------------------------------------------------------
	// Members
	//-------------------------------------------------------------------------
	private:
		float x;
		CGame* m_Game;

	//-------------------------------------------------------------------------
	// Overrides
	//-------------------------------------------------------------------------
	public:
		virtual bool Initialize();
		virtual void Deinitialize( );
		virtual void Update( DWORD inMiliseconds );
		virtual void Draw( HWND inHWND );
		virtual void Keyboard( unsigned int inMessage, bool inKeyDownFlag );
		virtual void LeftMouseDown( HWND inHWND );
		virtual void LeftMouseUp( HWND inHWND );
};