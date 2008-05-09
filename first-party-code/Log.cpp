#include "Log.h"
#include "WindowsIncludes.h"

void CLog::Print( char* inFormat, ... )
{
	va_list theArgs;
	va_start( theArgs, inFormat );
	int theLength = _vscprintf( inFormat, theArgs )+1; // _vscprintf doesn't count terminating '\0'
    char* theBuffer = new char[theLength * sizeof(char)];
    vsprintf( theBuffer, inFormat, theArgs ); // C4996

	::OutputDebugStringA( theBuffer );
    delete[] theBuffer;
}