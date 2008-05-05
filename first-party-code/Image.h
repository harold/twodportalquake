#pragma once
#include "FreeImage.h"
#include "gl/glew.h"

class CImage
{
	private: // members
		BYTE*   m_Bitmap;
		int     m_Width;
		int     m_Height;
		GLuint  m_GLTexture;

	public: // ctor
		CImage();
		~CImage();

	public: // load
		GLuint LoadFromFile( char* inPath );

	public: // access
		BYTE*  GetBits();
		int    GetWidth();
		int    GetHeight();
		GLuint GetTexture();
};
