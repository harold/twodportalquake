#include "2dpq.h"
#include "Log.h"

bool C2dpq::Initialize( )
{
	m_Game = new CGame( this );

	// Start Of User Initialization
	glClearColor( 0, 0, 0, 1.0f );
	glClearDepth( 1.0f );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glLineWidth( 2.0f );
	glEnable (GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		CLog::Print("Error: %s\n", glewGetErrorString(err));
		return false;
	}
	CLog::Print("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	wglSwapIntervalEXT( 2 );

	return true;
}

void C2dpq::Deinitialize( )
{
	delete m_Game;
}

void C2dpq::Update( DWORD milliseconds, HWND inHWND )
{
	m_Game->Update( inHWND );
}

void C2dpq::Draw( HWND inHWND )
{
	m_Game->Render();
}

bool C2dpq::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	return m_Game->Keyboard( inMessage, inKeyDownFlag );
}

void C2dpq::HandleChar( char inChar )
{
	return m_Game->HandleChar( inChar );
}

void C2dpq::LeftMouseDown( HWND inHWND )
{
	glLoadIdentity( );

	POINT theCursor;
    GetCursorPos( &theCursor );
    ScreenToClient( inHWND, &theCursor );
}

void C2dpq::LeftMouseUp( HWND inHWND )
{
}