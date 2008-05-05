#include "Console.h"
#include <math.h>

CConsole::CConsole( )
{
	m_Active   = true;
	m_CurrentY = 4.f;
	m_TargetY  = 0.f;

	m_Font.LoadFromFile( ".\\data\\profont.png" );
}

CConsole::~CConsole()
{
}

void CConsole::Update( TTimeUnit inTime )
{
	if( fabs(m_CurrentY-m_TargetY) > 0.01f )
	{
		m_CurrentY -= (m_CurrentY-m_TargetY)*0.0025f;
	}
}

void CConsole::Render()
{
	glLoadIdentity();
/*
	glBegin( GL_TRIANGLES );
		glColor4f( 0.2f, 0.2f, 0.2f, 0.5f );
		glVertex3f( -100, m_CurrentY, -10.0f );
		glVertex3f( -100, 100       , -10.0f );
		glVertex3f(  100, m_CurrentY, -10.0f );

		glVertex3f(  100, m_CurrentY, -10.0f );
		glVertex3f( -100, 100,        -10.0f );
		glVertex3f(  100, 100,        -10.0f );
	glEnd();

	glLineWidth( 3.0f );
	glBegin( GL_LINE_STRIP );
		glColor3f( 0.2f, 0.2f, 0.2f );
		glVertex3f( -100, m_CurrentY, -10.0f );
		glVertex3f(  100, m_CurrentY, -10.0f );
	glEnd();
	glLineWidth( 2.0f );
*/
	RenderString( "Welcome to the thunderdome!" );
}

void CConsole::RenderString( char* inString )
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_Font.GetTexture() );

	int theLength = strlen( inString );
	for( int i=0; i<theLength; i++ )
	{
		int ascii = (int)inString[i];
		int x = ascii % 16;
		int y = ascii / 16;
		float left  = (float)(3 + x*11)/256.f;
		float right = left + (6.f/256.f);

		float bottom = (float)(3 + y*17)/256.f;
		float top    = bottom + (11.f/256.f);

		glColor3f( 1.f, 1.f, 1.f ); 
		glNormal3f( 0, 0, 1.f );
		glBegin( GL_TRIANGLES );
			glTexCoord2d(  left,  top    ); 
			glVertex3f  (  i*6, 11, -1 );
			glTexCoord2d(  right,  top    ); 
			glVertex3f  (  i*6+6, 11, -1 );
			glTexCoord2d(  right,  bottom    ); 
			glVertex3f  (  i*6+6, 0, -1 );
								 
			glTexCoord2d(  left,  top    ); 
			glVertex3f  (  i*6, 11, -1 );
			glTexCoord2d(  right,  bottom    ); 
			glVertex3f  (  i*6+6, 0, -1 );
			glTexCoord2d(  left,  bottom    ); 
			glVertex3f  (  i*6, 0, -1 );
		glEnd();
	}

	glDisable( GL_TEXTURE_2D );
}



void CConsole::Toggle()
{
	m_Active = !m_Active;
	m_TargetY = m_Active ? 5.f : 0.f;
}
