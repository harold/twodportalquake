#include "Game.h"
#include "Console.h"
#include <math.h>
#include <stdio.h> //sprintf

CConsole::CConsole( )
{
	m_Active   = false;
	m_CurrentY = 230.f;
	m_TargetY  = 230.f;

	m_Font.LoadFromFile( ".\\data\\profont.png" );

	m_LineCursorIndex = 0;
	for( int i=0; i<8; ++i )
	{
		m_Lines[i] = 0;
	}

	memset( m_InputBuffer, 0, 128 );
}

CConsole::~CConsole()
{
}

void CConsole::SetGame( CGame* inGame )
{
	m_Game = inGame;
}

void CConsole::Update( TTimeUnit inTime )
{
	if( fabs(m_CurrentY-m_TargetY) > 0.01f )
	{
		m_CurrentY -= (m_CurrentY-m_TargetY)*0.05f;
	}
}

void CConsole::Render()
{
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	int theWidth  = m_Game->GetScreenWidth();
	int theHeight = m_Game->GetScreenHeight();
	glOrtho( -theWidth/2, theWidth/2, -theHeight/2, theHeight/2, 0.5, 100 );

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();

	glBegin( GL_TRIANGLES );
		glColor4f( 0.3f, 0.3f, 0.3f, 0.5f );
		glVertex3f( -theWidth/2, m_CurrentY-2, -10.0f );
		glVertex3f( -theWidth/2, theHeight/2,  -10.0f );
		glVertex3f(  theWidth/2, m_CurrentY-2, -10.0f );

		glVertex3f(  theWidth/2, m_CurrentY-2, -10.0f );
		glVertex3f( -theWidth/2, theHeight/2,  -10.0f );
		glVertex3f(  theWidth/2, theHeight/2,  -10.0f );
	glEnd();

	glLineWidth( 3.0f );
	glBegin( GL_LINE_STRIP );
		glColor3f( 0.2f, 0.2f, 0.2f );
		glVertex3f( -theWidth/2, m_CurrentY-2, -10.0f );
		glVertex3f(  theWidth/2, m_CurrentY-2, -10.0f );
	glEnd();
	glLineWidth( 2.0f );

	for( int i=0; i<8; i++ )
	{
		int theIndex = m_LineCursorIndex-i-1;
		if( theIndex < 0 ) theIndex += 8;
		RenderString( theWidth, m_CurrentY+(i+1)*11, m_Lines[ theIndex ] );
	}
	char theBuffer[256];
	sprintf( theBuffer, "> %s", m_InputBuffer );
	RenderString( theWidth, m_CurrentY, theBuffer );
}

void CConsole::RenderString( int inScreenWidth, int inY, char* inString )
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

		glNormal3f( 0, 0, 1.f );
		glPushMatrix();
		glTranslatef( -inScreenWidth/2+10, inY, 0 );
		glBegin( GL_TRIANGLES );
			glColor3f( 0.f, 1.f, 0.f ); 
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

bool CConsole::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	if( inKeyDownFlag )
	{
		if( inMessage == 8 ) // backspace
		{
			m_InputBuffer[ strlen(m_InputBuffer)-1 ] = 0;
			return false;
		}
		else if( inMessage == 13 ) // return
		{
			Print( m_InputBuffer );
			m_Game->SendInput( m_InputBuffer );
			strcpy( m_InputBuffer, "" );
			return false;
		}
	}

	return true;
}

void CConsole::HandleChar( char inChar )
{
	sprintf( m_InputBuffer, "%s%c", m_InputBuffer, inChar );
}

void CConsole::Toggle()
{
	m_Active = !m_Active;
	if ( m_Active )
	{
		m_TargetY = m_Game->GetScreenHeight()/2-115;
	}
	else
	{
		m_TargetY = m_Game->GetScreenHeight()/2+5;
	}
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
