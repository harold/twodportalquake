#include "Log.h"
#include <stdio.h>

CLog::CLog()
{
}

CLog::~CLog()
{
}

void CLog::Print( char* inString )
{
	printf( inString );
}