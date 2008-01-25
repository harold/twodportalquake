#include "WindowsIncludes.h"
#include "Game.h"

void InputThreadMain( void* inGame )
{
	CGame* theGame = reinterpret_cast<CGame*>(inGame);
	char theInput[80];

	while( true )
	{
		gets( theInput );
		theGame->SendInput( theInput );
	}
}

int __cdecl main(void) 
{
	CGame theGame;
	_beginthread( InputThreadMain, 0, &theGame );

	while( true )
	{
		theGame.Update();
	}

    return 0;
}
