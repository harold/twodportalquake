#include "Console.h"
#include <math.h>

CConsole::CConsole( )
{
	m_Active   = true;
	m_CurrentY = 4.f;
	m_TargetY  = 0.f;
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
}

void CConsole::Toggle()
{
	m_Active = !m_Active;
	m_TargetY = m_Active ? 5.f : 0.f;
}
