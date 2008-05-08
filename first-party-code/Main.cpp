#include "WindowsIncludes.h"
#include "2dpq.h"

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
//#pragma comment( lib, "glaux.lib" )

// Program Entry (WinMain)
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	UNREFERENCED_PARAMETER( nCmdShow );
	C2dpq the2dpq;

	bool               isMessagePumpActive = true;
	MSG                msg;
	DWORD              theTickCount;

	// Fill Out Application Data
	the2dpq.m_Application.className = L"OpenGL";
	the2dpq.m_Application.hInstance = hInstance;

	// Fill Out Window
	ZeroMemory( &the2dpq.m_Window, sizeof(CuGL::SGLWindow) );
	the2dpq.m_Window.keys              = &the2dpq.m_Keys;
	the2dpq.m_Window.init.application  = &the2dpq.m_Application;
	the2dpq.m_Window.init.title        = L"2dpq";
	the2dpq.m_Window.init.width        = 800;
	the2dpq.m_Window.init.height       = 450;
	the2dpq.m_Window.init.bitsPerPixel = 32;
	the2dpq.m_Window.init.isFullScreen = false;

	ZeroMemory( &the2dpq.m_Keys, sizeof(CuGL::SKeys) );

	// Register A Class For Our Window To Use
	if ( the2dpq.RegisterWindowClass( ) == false )
	{
		// Failure
		MessageBox (HWND_DESKTOP, L"Error Registering Window Class!", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

	the2dpq.m_ProgramLoopingFlag = true;
	while ( the2dpq.m_ProgramLoopingFlag )
	{
		// Create A Window
		if ( the2dpq.CreateWindowGL() == true )
		{
			// At This Point We Should Have A Window That Is Setup To Render OpenGL
			the2dpq.Initialize( );
			while ( isMessagePumpActive )
			{
				// Success Creating Window.  Check For Window Messages
				if ( PeekMessage( &msg, the2dpq.m_Window.hWnd, 0, 0, PM_REMOVE ) != 0)
				{
					// Check For WM_QUIT Message
					if ( msg.message != WM_QUIT && msg.message != WM_CLOSE )
					{
						if ( 
							msg.message == WM_LBUTTONDOWN   || 
							msg.message == WM_LBUTTONUP     || 
							msg.message == WM_LBUTTONDBLCLK || 
							msg.message == WM_CAPTURECHANGED )
						{
							the2dpq.MouseHandler( msg );
						}
						else if( 
							msg.message == WM_KEYDOWN    ||
							msg.message == WM_SYSKEYDOWN || 
							msg.message == WM_KEYUP      ||
							msg.message == WM_SYSKEYUP )
						{
							TranslateMessage( &msg );
							//the2dpq.Keyboard( (UINT)msg.wParam, (msg.message == WM_KEYDOWN || msg.message == WM_SYSKEYDOWN) );           
						}
						else if( msg.message == WM_CHAR || msg.message == WM_SYSCHAR )
						{
							char theBuffer[1024];
							sprintf( theBuffer, "%c", (char)msg.wParam );
							::OutputDebugStringA( theBuffer );
						}
						else
						{
							DispatchMessage( &msg );
						}
					}
					else
					{
						isMessagePumpActive = false;
						the2dpq.m_ProgramLoopingFlag = false;
					}
				}
				else
				{
					if ( the2dpq.m_Window.isVisible == false )
					{
						WaitMessage();
					}
					else
					{
						// Process Application Loop
						theTickCount = GetTickCount();
						the2dpq.Update( theTickCount - the2dpq.m_Window.lastTickCount );
						the2dpq.m_Window.lastTickCount = theTickCount;
						the2dpq.Draw( the2dpq.m_Window.hWnd );

						SwapBuffers( the2dpq.m_Window.hDC );
						Sleep(1);
					}
				}
			}

			// Application Is Finished
			the2dpq.Deinitialize();

			the2dpq.DestroyWindowGL( );
		}
		else
		{
			// Error Creating Window
			MessageBox (HWND_DESKTOP, L"Error Creating OpenGL Window", L"Error", MB_OK | MB_ICONEXCLAMATION);
			the2dpq.m_ProgramLoopingFlag = false;
		}
	}

	UnregisterClass( the2dpq.m_Application.className, the2dpq.m_Application.hInstance );
	return 0;
}
