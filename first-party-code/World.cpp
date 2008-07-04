#include "World.h"
#include "Game.h"
#include "MoonMan.h"

CWorld::CWorld( )
{
	m_MoonMan = new CMoonMan();
}

CWorld::~CWorld()
{
	delete m_MoonMan;
	m_MoonMan = NULL;
}

void CWorld::SetGame( CGame* inGame )
{
	m_Game = inGame;
}

void CWorld::Update( TTimeUnit inTime )
{
	m_MoonMan->Update();
}

void CWorld::Render()
{
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

	float theAspectRatio = static_cast<float>(m_Game->GetScreenWidth()) / static_cast<float>(m_Game->GetScreenHeight());
	gluPerspective( 45.0f, theAspectRatio, 1.0f, 10000.0f );

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	// TODO: HH - Real camera transforms
	glTranslatef( 0.f, 0.f, -10.f );

	m_MoonMan->Render();
/*
	glBegin( GL_LINE_STRIP );
	glColor3f( 0.0f, 0.0f, 0.8f );
	for( float i=-10; i<=10; i+=0.1f )
	{
		glVertex3f( i/2, sin(i/2.0f), 0.0f );
	}
	glEnd();
*/
}

void CWorld::MouseWheel( int inDistance )
{
}
