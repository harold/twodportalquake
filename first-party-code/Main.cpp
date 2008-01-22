#include "Game.h"
#include "CommandQueue.h"

int __cdecl main(void) 
{
	CGame theGame;

	theGame.StartServer();

	int theFrameCounter = 0;
	char theInput[80];

	while( true )
	{
		theGame.Update();
		printf( "> " );
		gets( theInput );
		theGame.ClientWrite( theInput );
		// noop
	}

    return 0;
}