#include "Timer.h"

//==============================================================================
/**		
 *	Constructor
 */
CTimer::CTimer( ) :
	m_StartTime( 0 ),
	m_Frequency( 0 ),
	m_IsRunning( false )
{
	LARGE_INTEGER theFrequency;
	::QueryPerformanceFrequency( &theFrequency );
	m_Frequency = theFrequency.QuadPart;

	Start( );
}

//==============================================================================
/**
 *	Start the timer
 */
void CTimer::Start( )
{
	if ( !m_IsRunning )
		m_StartTime = GetPlatformTime( );
	m_IsRunning = true;
}

//==============================================================================
/**
 *	Stop the timer
 */
void CTimer::Stop( )
{
	if ( m_IsRunning )
		m_StartTime = GetPlatformTime( ) - m_StartTime;
	m_IsRunning = false;
}

//==============================================================================
/**
 *	Reset the timer
 */
void CTimer::Reset( )
{
	if ( m_IsRunning )
		m_StartTime = GetPlatformTime( );
	else
		m_StartTime = 0;
}

//==============================================================================
/**		
 *  Gets the current time in milliseconds.
 *	@return the current time since timer was started(in miliseconds),
 *	or time when it was stopped
 */
TTimeUnit CTimer::GetTimeMilliSecs( )
{
	return static_cast<TTimeUnit>( GetTimeMicroSecs( ) / 1000.0 );
}

//=============================================================================
/**
 *	Get the number of usecs elapsed since start was called.
 *	If the timer is running then this will return the time from when start was
 *	called. If the timer is stopped then this will return the amount of time
 *	between the start and last stop.
 *	@return returns the elasped micro second.
 */
TMicroSeconds CTimer::GetTimeMicroSecs( )
{
	if ( m_IsRunning )
		return GetPlatformTime( ) - m_StartTime;
	else
		return m_StartTime;
}


//=============================================================================
/**
 *	Internal method to return the system time.
 *	@return current time in micro seconds.
 */
TMicroSeconds CTimer::GetPlatformTime( )
{
	LARGE_INTEGER	theCurrentTime;
	::QueryPerformanceCounter( &theCurrentTime );
	return static_cast<TMicroSeconds>( theCurrentTime.QuadPart * 1000000 / m_Frequency );
}
