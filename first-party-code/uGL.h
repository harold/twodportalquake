#pragma once
#include <windows.h>
#include "gl\glew.h"
#include "gl\wglew.h"

class CuGL
{
	//-------------------------------------------------------------------------
	// Structures
	//-------------------------------------------------------------------------
	public:
	struct SKeys
	{
		bool m_KeyStates[256];
	};

	struct SApplication
	{
		HINSTANCE hInstance;
		LPCWSTR   className;
	};

	struct SGLWindowInit
	{
		SApplication* application;
		LPCWSTR       title;
		int           width;
		int           height;
		BYTE          bitsPerPixel;
		bool          isFullScreen;
	};

	struct SGLWindow
	{
		SKeys*        keys;
		HWND          hWnd;
		HDC           hDC;
		HGLRC         hRC;
		SGLWindowInit init;
		bool          isVisible;
		DWORD         lastTickCount;
		int           m_Width;
		int           m_Height;
	};

	//-------------------------------------------------------------------------
	// Members
	//-------------------------------------------------------------------------
	public:
		SApplication m_Application;
		SGLWindow    m_Window;
		SKeys        m_Keys;

		bool m_ProgramLoopingFlag;


	//-------------------------------------------------------------------------
	// Methods
	//-------------------------------------------------------------------------
	public:
		bool RegisterWindowClass( );
		bool CreateWindowGL( );
		bool DestroyWindowGL( );

	private:
		bool ChangeScreenResolution( int inWidth, int inHeight, int inBPP );

		static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
		static void Reshape( int inWidth, int inHeight );

	
	//-------------------------------------------------------------------------
	// Overrides
	//-------------------------------------------------------------------------
	public:
		virtual bool Initialize( );
		virtual void Deinitialize( );
		virtual void Update( DWORD inMiliseconds, HWND inHWND );
		virtual void Draw( HWND inHWND );
		virtual bool Keyboard( unsigned int inMessage, bool inKeyDownFlag );
		virtual void HandleChar( char inChar );
		virtual void MouseHandler( MSG inMessage );
		virtual void MouseWheel( int inDistance );
		virtual void LeftMouseDown( HWND inHWND );
		virtual void LeftMouseUp( HWND inHWND );
};
