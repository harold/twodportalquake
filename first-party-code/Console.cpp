#include "Console.h"
#include <math.h>
#include <stdio.h> //sprintf

CConsole::CConsole( )
{
	m_Active   = true;
	m_CurrentY = 4.f;
	m_TargetY  = 0.f;

	m_Font.LoadFromFile( ".\\data\\profont.png" );

	m_LineCursorIndex = 0;
	for( int i=0; i<8; ++i )
	{
		m_Lines[i] = 0;
	}

	memset( m_InputBuffer, 0, 128 );

	Print( "1" );
	Print( "2" );
	Print( "3" );
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
	for( int i=0; i<8; i++ )
	{
		int theIndex = m_LineCursorIndex-i-1;
		if( theIndex < 0 ) theIndex += 8;
		RenderString( i*11, m_Lines[ theIndex ] );
	}
	char theBuffer[256];
	sprintf( theBuffer, "> %s", m_InputBuffer );
	RenderString( -11, theBuffer );
}

void CConsole::RenderString( int inY, char* inString )
{
	if( !inString ) return;

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
		glPushMatrix();
		glTranslatef( -390, 130+inY, 0 );
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
		glPopMatrix();
	}

	glDisable( GL_TEXTURE_2D );
}

void CConsole::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	if( inKeyDownFlag )
	{
		if( inMessage == 8 ) // backspace
		{
			m_InputBuffer[ strlen(m_InputBuffer)-1 ] = 0;
		}
		else if( inMessage == 13 ) // return
		{
			Print( m_InputBuffer );
			strcpy( m_InputBuffer, "" );
		}
		else
		{
			sprintf( m_InputBuffer, "%s%c", m_InputBuffer, (char)inMessage );
		}
	}
}

void CConsole::Toggle()
{
	m_Active = !m_Active;
	m_TargetY = m_Active ? 5.f : 0.f;
}

void CConsole::Print( char* inString )
{
	if( m_Lines[ m_LineCursorIndex ] )
	{
		delete m_Lines[ m_LineCursorIndex ];
	}
	m_Lines[ m_LineCursorIndex ] = new char[strlen(inString)+1];
	strcpy( m_Lines[ m_LineCursorIndex ], inString );
	m_LineCursorIndex++;
	if( m_LineCursorIndex == 8 ) m_LineCursorIndex = 0;
}
