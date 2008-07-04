#pragma once
#include <windows.h>
#include "Types.h"
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
