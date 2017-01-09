#include "Texture.h"
#include <stdexcept>

//!< Formating the bitmap
static GLenum TextureFormatForBitmapFormat(Bitmap::Format format)
{
	switch (format) {
	case Bitmap::Format_RGB: return gl::RGB;
	case Bitmap::Format_RGBA: return gl::RGBA;
	default: throw std::runtime_error("Unrecognised Bitmap::Format");
	}
}

//!< Constructor
Texture::Texture(int iunit, const Bitmap& bitmap, GLint minMagFiler, GLint wrapMode) :
    m_originalWidth((GLfloat)bitmap.width()),
    m_originalHeight((GLfloat)bitmap.height())
{
	gl::GenTextures(1, &m_texture);
	gl::BindTexture(gl::TEXTURE_2D, m_texture);

    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, minMagFiler);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, minMagFiler);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, wrapMode);
    gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, wrapMode);
    gl::TexImage2D(gl::TEXTURE_2D,
                 0, 
				 TextureFormatForBitmapFormat(bitmap.format()),
                 (GLsizei)bitmap.width(), 
                 (GLsizei)bitmap.height(),
                 0, 
				 TextureFormatForBitmapFormat(bitmap.format()),
                 gl::UNSIGNED_BYTE, 
                 bitmap.pixelBuffer());

	gl::BindTexture(gl::TEXTURE_2D, 0);
}

//!< Gets the original width of bitmap
GLfloat Texture::originalWidth() const
{
    return m_originalWidth;
}

//!< Gets the original height of bitmap
GLfloat Texture::originalHeight() const
{
    return m_originalHeight;
}

//!< Gets the texture handle
GLuint Texture::getTextureId() 
{
	return m_texture;
}

