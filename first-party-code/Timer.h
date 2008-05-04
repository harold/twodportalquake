#pragma once
#include <windows.h>

typedef INT64 TMicroSeconds;		///< Time in microseconds
typedef INT32 TTimeUnit;			///< Time in milliseconds

class CTimer
{
	protected:
		TMicroSeconds	m_StartTime;
		TMicroSeconds	m_Frequency;
		BOOL			m_IsRunning;

	//==============================================================================
	//	Methods
	//==============================================================================
	public:		// Construction
						CTimer( );
				
	public:		// Operation
		void			Start( );
		void			Stop( );
		void			Reset( );
		TTimeUnit		GetTimeMilliSecs( );
		TMicroSeconds	GetTimeMicroSecs( );

	private:	// Utility
		TMicroSeconds	GetPlatformTime( );
};
