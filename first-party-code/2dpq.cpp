#include "2dpq.h"
#include <math.h>

bool C2dpq::Initialize( )
{
	m_Game = new CGame();
	x = 0;
	// Start Of User Initialization
	glClearColor( 1.f, 1.f, 0.8f, 1.0f );
	glClearDepth( 1.0f );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glShadeModel( GL_SMOOTH );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glLineWidth( 2.0f );

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		//printf("Error: %s\n", glewGetErrorString(err));
		return false;
	}
	//printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	wglSwapIntervalEXT( 2 );

	return true;
}

void C2dpq::Deinitialize( )
{
	delete m_Game;
}

void C2dpq::Update( DWORD milliseconds )
{
	m_Game->Update();
	x += 0.01;
}

void C2dpq::Draw( HWND inHWND )
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	glBegin( GL_LINE_STRIP );
	glColor3f( 0.0f, 0.0f, 0.2f );
	for( float i=-10; i<=10; i+=2.f )
	{
		glVertex3f( i, sin((i+x)/2.0f), -10.0f );
	}
	glEnd();

	glFlush();
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