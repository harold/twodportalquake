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
		virtual void Update( DWORD inMiliseconds, HWND inHWND );
		virtual void Draw( HWND inHWND );
		virtual bool Keyboard( unsigned int inMessage, bool inKeyDownFlag );
		virtual void HandleChar( char inChar );
		virtual void MouseWheel( int inDistance );
		virtual void LeftMouseDown( HWND inHWND );
		virtual void LeftMouseUp( HWND inHWND );
};