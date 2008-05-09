#include "uGL.h"
#pragma warning( disable : 4311 )	//  'type cast' : pointer truncation
#pragma warning( disable : 4312 )	//  'type cast' : pointer truncation

bool CuGL::RegisterWindowClass( )
{
	// Register A Window Class
	WNDCLASSEX theWindowClass;
	ZeroMemory (&theWindowClass, sizeof (WNDCLASSEX));

	theWindowClass.cbSize        = sizeof (WNDCLASSEX);
	theWindowClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	theWindowClass.lpfnWndProc   = reinterpret_cast<WNDPROC>(WindowProc);
	theWindowClass.hInstance     = m_Application.hInstance;
	theWindowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
	theWindowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	theWindowClass.lpszClassName = m_Application.className;

	if ( RegisterClassEx( &theWindowClass ) == 0 )
	{
		// NOTE: Failure, Should Never Happen
		MessageBox (HWND_DESKTOP, L"RegisterClassEx Failed!", L"Error", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

bool CuGL::CreateWindowGL( )
{
	DWORD theWindowStyle = WS_OVERLAPPEDWINDOW;
	DWORD theWindowExtendedStyle = WS_EX_APPWINDOW;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		m_Window.init.bitsPerPixel,
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		16,																// 16Bit Z-Buffer (Depth Buffer)  
		0,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	RECT theWindowRect = {0, 0, m_Window.init.width, m_Window.init.height};

	GLuint thePixelFormat;

	if ( m_Window.init.isFullScreen )
	{
		if ( ChangeScreenResolution( m_Window.init.width, m_Window.init.height, m_Window.init.bitsPerPixel) == false)
		{
			// Fullscreen Mode Failed.  Run In Windowed Mode Instead
			MessageBox (HWND_DESKTOP, L"Mode Switch Failed.\nRunning In Windowed Mode.", L"Error", MB_OK | MB_ICONEXCLAMATION);
			m_Window.init.isFullScreen = false;
		}
		else
		{
			// Going fullscreen
			ShowCursor( false );
			theWindowStyle = WS_POPUP;
			theWindowExtendedStyle |= WS_EX_TOPMOST;
		}
	}
	else
	{
		AdjustWindowRectEx( &theWindowRect, theWindowStyle, 0, theWindowExtendedStyle );
	}

	// Create The OpenGL Window
	m_Window.hWnd = CreateWindowEx( theWindowExtendedStyle,
                                     m_Window.init.application->className,
                                     m_Window.init.title,
                                     theWindowStyle,
                                     0, 0,                                   // Window X,Y Position
                                     theWindowRect.right  - theWindowRect.left,
                                     theWindowRect.bottom - theWindowRect.top,
                                     HWND_DESKTOP,                           // Desktop Is Window's Parent
                                     0,                                      // No Menu
                                     m_Window.init.application->hInstance,
                                     &m_Window);

	if ( m_Window.hWnd == 0 )
	{
		// Failed to create the window.
		return false;
	}

	m_Window.hDC = GetDC( m_Window.hWnd );
	if ( m_Window.hDC == 0 )
	{
		// Failed to get device context
		DestroyWindow( m_Window.hWnd );
		m_Window.hWnd = 0;
		return false;
	}

	thePixelFormat = ChoosePixelFormat( m_Window.hDC, &pfd );
	if ( thePixelFormat == 0 )
	{
		ReleaseDC( m_Window.hWnd, m_Window.hDC );
		m_Window.hDC = 0;
		DestroyWindow( m_Window.hWnd );
		m_Window.hWnd = 0;
		return false;
	}

	if( SetPixelFormat( m_Window.hDC, thePixelFormat, &pfd ) == false )
	{
		ReleaseDC( m_Window.hWnd, m_Window.hDC );
		m_Window.hDC = 0;
		DestroyWindow( m_Window.hWnd );
		m_Window.hWnd = 0;
		return false;
	}

	m_Window.hRC = wglCreateContext( m_Window.hDC );
	if ( m_Window.hRC == 0 )
	{
		ReleaseDC( m_Window.hWnd, m_Window.hDC );
		m_Window.hDC = 0;
		DestroyWindow( m_Window.hWnd );
		m_Window.hWnd = 0;
		return false;
	}

	// Make The Rendering Context Our Current Rendering Context
	if( wglMakeCurrent( m_Window.hDC, m_Window.hRC ) == false )
	{
		// Failed
		wglDeleteContext( m_Window.hRC );
		m_Window.hRC = 0;
		ReleaseDC( m_Window.hWnd, m_Window.hDC );
		m_Window.hDC = 0;
		DestroyWindow( m_Window.hWnd );
		m_Window.hWnd = 0;
		return false;
	}

	ShowWindow( m_Window.hWnd, SW_NORMAL );
	m_Window.isVisible = true;

	Reshape( m_Window.init.width, m_Window.init.height );

	ZeroMemory( m_Window.keys, sizeof(SKeys) );

	m_Window.lastTickCount = GetTickCount();

	return true;
}

bool CuGL::DestroyWindowGL( )
{
	if( m_Window.hWnd != 0 )
	{
		if ( m_Window.hDC != 0 )
		{
			wglMakeCurrent( m_Window.hDC, 0 );
			if( m_Window.hRC != 0 )
			{
				wglDeleteContext( m_Window.hRC );
				m_Window.hRC = 0;

			}
			ReleaseDC( m_Window.hWnd,  m_Window.hDC );
			m_Window.hDC = 0;
		}
		DestroyWindow( m_Window.hWnd );
		m_Window.hWnd = 0;
	}

	if ( m_Window.init.isFullScreen )
	{
		ChangeDisplaySettings( NULL,0 );
		ShowCursor( true );
	}

	return true;
}

bool CuGL::ChangeScreenResolution( int inWidth, int inHeight, int inBPP )
{
	DEVMODE dmScreenSettings;
	ZeroMemory( &dmScreenSettings, sizeof (DEVMODE) );
	dmScreenSettings.dmSize	      = sizeof (DEVMODE);
	dmScreenSettings.dmPelsWidth  = inWidth;
	dmScreenSettings.dmPelsHeight = inHeight;
	dmScreenSettings.dmBitsPerPel = inBPP;
	dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL ) // CDS_FULLSCREEN = 4 on windows
	{
		return false;
	}

	return true;
}

// Process Window Message Callbacks
LRESULT CALLBACK CuGL::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// Get The Window Context
	SGLWindow* theWindow = (SGLWindow*)( GetWindowLong( hWnd, GWL_USERDATA ) );

	switch ( uMsg )
	{
		case WM_SYSCOMMAND:
		{
			switch ( wParam )
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}

		case WM_CREATE:
		{
			CREATESTRUCT* theCreationStruct = (CREATESTRUCT*)(lParam);
			theWindow = (SGLWindow*)( theCreationStruct->lpCreateParams );
			SetWindowLong( hWnd, GWL_USERDATA, (LONG)(theWindow) );
		}
		return 0;

		case WM_SIZE:
			switch (wParam)
			{
				case SIZE_MINIMIZED:
					theWindow->isVisible = false;
				return 0;

				case SIZE_MAXIMIZED:
					theWindow->isVisible = true;
					Reshape( LOWORD (lParam), HIWORD (lParam) );
				return 0;

				case SIZE_RESTORED:
					theWindow->isVisible = true;
					Reshape( LOWORD (lParam), HIWORD (lParam) );
				return 0;
			}
		break;

		case WM_CLOSE:
			PostMessage( hWnd, WM_QUIT, 0, 0 );
			return 0;
		break;

		case WM_KEYDOWN:
			if ( (wParam >= 0) && (wParam <= 255) )
			{
				theWindow->keys->m_KeyStates[wParam] = true;
				return 0;
			}
		break;

		case WM_KEYUP:
			if ((wParam >= 0) && (wParam <= 255))
			{
				theWindow->keys->m_KeyStates[wParam] = false;
				return 0;
			}
		break;
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

void CuGL::Reshape( int inWidth, int inHeight )
{
	glViewport( 0, 0, inWidth, inHeight );
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();

//	float theAspectRatio = static_cast<float>(inWidth) / static_cast<float>(inHeight);
//	gluPerspective( 45.0f, theAspectRatio, 1.0f, 100.0f );

	glOrtho( -inWidth/2, inWidth/2, -inHeight/2, inHeight/2, 0.5, 100 );
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

bool CuGL::Initialize( )
{
	return true;
}

void CuGL::Deinitialize( )
{
}

void CuGL::Update( DWORD milliseconds )
{
	UNREFERENCED_PARAMETER( milliseconds );
}

void CuGL::Draw( HWND inHWND )
{
	UNREFERENCED_PARAMETER( inHWND );
}

bool CuGL::Keyboard( unsigned int inMessage, bool inKeyDownFlag )
{
	return true;
}

void CuGL::HandleChar( char inChar )
{
}

void CuGL::MouseHandler( MSG inMessage )
{
	switch( inMessage.message )
	{
		case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        {
            // Capture the mouse, so if the mouse button is 
            // released outside the window, we'll get the WM_LBUTTONUP message
			SetCapture( inMessage.hwnd );
			LeftMouseDown( inMessage.hwnd );
        }

        case WM_LBUTTONUP:
        {
            ReleaseCapture();
			LeftMouseUp( inMessage.hwnd );
			break;
        }

        case WM_CAPTURECHANGED:
        {
            if( (HWND)inMessage.lParam != inMessage.hwnd )
            {
                ReleaseCapture();
            }
            break;
        }
	}
}

void CuGL::LeftMouseDown( HWND inHWND )
{
	UNREFERENCED_PARAMETER( inHWND );
}

void CuGL::LeftMouseUp( HWND inHWND )
{
	UNREFERENCED_PARAMETER( inHWND );
}