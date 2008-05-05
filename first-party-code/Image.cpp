#include "Image.h"

CImage::CImage()
{
	m_Bitmap = NULL;
}

CImage::~CImage()
{
	// TODO: Clean up?
}

GLuint CImage::LoadFromFile( char* inPath )
{
	FREE_IMAGE_FORMAT theFormat;
	FIBITMAP* theInputBitmap = NULL;
	// check the file signature and deduce its format
	theFormat = FreeImage_GetFileType( inPath, 0 );
	if( theFormat == FIF_UNKNOWN )
	{
		// no signature ?
		// try to guess the file format from the file extension
		theFormat = FreeImage_GetFIFFromFilename( inPath );
	}
	
	// check that the plugin has reading capabilities ...
	if( (theFormat != FIF_UNKNOWN) && FreeImage_FIFSupportsReading( theFormat ) ) {
		// ok, let's load the file
		theInputBitmap = FreeImage_Load(theFormat, inPath, 0);
	}

	// --------------------------------------------------------------
	FIBITMAP *theSource = FreeImage_ConvertTo32Bits( theInputBitmap );
	FreeImage_Unload( theInputBitmap );

	// Allocate a raw buffer
	m_Width = FreeImage_GetWidth( theSource );
	m_Height = FreeImage_GetHeight( theSource );
	int theScanWidth = FreeImage_GetPitch( theSource );
	m_Bitmap = new BYTE[ m_Height * theScanWidth ];
	// convert the bitmap to raw bits (top-left pixel first)
	FreeImage_ConvertToRawBits( m_Bitmap, theSource, theScanWidth, 32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, true);
	FreeImage_Unload( theSource );

	// --------------------------------------------------------------
	glGenTextures( 1, &m_GLTexture );
	glBindTexture( GL_TEXTURE_2D, m_GLTexture );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, GetBits() );

	return m_GLTexture;
}

BYTE* CImage::GetBits()
{
	return m_Bitmap;
}

int CImage::GetWidth()
{
	return m_Width;
}

int CImage::GetHeight()
{
	return m_Height;
}

GLuint CImage::GetTexture()
{
	return m_GLTexture;
}
