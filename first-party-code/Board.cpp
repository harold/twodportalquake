#include "Game.h"
#include "Board.h"

CBoard::CBoard( )
{
	m_Tiles[0].LoadFromFile( "./data/grass.png" );
	m_Tiles[1].LoadFromFile( "./data/road.png" );
	m_Tiles[2].LoadFromFile( "./data/castle.png" );
	m_Tiles[3].LoadFromFile( "./data/water.png" );

	m_Layout[0][3] = 0; m_Layout[1][3] = 0; m_Layout[2][3] = 1; m_Layout[3][3] = 0;
	m_Layout[0][2] = 3; m_Layout[1][2] = 3; m_Layout[2][2] = 1; m_Layout[3][2] = 3;
	m_Layout[0][1] = 0; m_Layout[1][1] = 0; m_Layout[2][1] = 1; m_Layout[3][1] = 0;
	m_Layout[0][0] = 2; m_Layout[1][0] = 0; m_Layout[2][0] = 1; m_Layout[3][0] = 0;
}

CBoard::~CBoard()
{
}

void CBoard::SetGame( CGame* inGame )
{
	m_Game = inGame;
}

void CBoard::Update( TTimeUnit inTime )
{
}

void CBoard::Render()
{
	glEnable( GL_TEXTURE_2D );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

	float theAspectRatio = static_cast<float>(m_Game->GetScreenWidth()) / static_cast<float>(m_Game->GetScreenHeight());
	gluPerspective( 45.0f, theAspectRatio, 1.0f, 10000.0f );

	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef( -256.f, -256.f, 0 );
	for ( int x = 0; x < 4; ++x )
	{
		for ( int y = 0; y < 4 ; ++y )
		{
			glBindTexture( GL_TEXTURE_2D, m_Tiles[m_Layout[x][y]].GetTexture() );

			glBegin( GL_TRIANGLE_STRIP );
				glColor4f( 1.f, 1.f, 1.f, 1.f );
				glTexCoord2d( 0, 0 ); glVertex3f( 0,   0,   -2000.0f );
				glTexCoord2d( 0, 1 ); glVertex3f( 0,   128, -2000.0f );
				glTexCoord2d( 1, 0 ); glVertex3f( 128, 0,   -2000.0f );
				glTexCoord2d( 1, 1 ); glVertex3f( 128, 128, -2000.0f );
			glEnd();
			glTranslatef( 0, 128.f, 0 );
		}
		glTranslatef( 128.f, 0, 0 );
		glTranslatef( 0, -4*128.f, 0 );
	}

	glDisable( GL_TEXTURE_2D );
}
