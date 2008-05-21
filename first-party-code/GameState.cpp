#include "GameState.h"

CGameState::CGameState( )
{
	m_LeftPlayerY = 0;
	m_RightPlayerY = 0;
	m_BallX = 0;
	m_BallY = 0;

}

CGameState::~CGameState()
{
}

int CGameState::GetLeftPlayerY()
{
	return m_LeftPlayerY;
}

int CGameState::GetRightPlayerY()
{
	return m_RightPlayerY;
}

int CGameState::GetBallX()
{
	return m_BallX;
}

int CGameState::GetBallY()
{
	return m_BallY;
}

void CGameState::SetLeftPlayerY( int inY )
{
	m_LeftPlayerY = inY;
}

void CGameState::SetRightPlayerY( int inY )
{
	m_RightPlayerY = inY;
}

void CGameState::SetBallX( int inX )
{
	m_BallX = inX;
}

void CGameState::SetBallY( int inY )
{
	m_BallY = inY;
}

