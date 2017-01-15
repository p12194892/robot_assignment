#pragma once
/*!
* @file Texture.h
* Header file creates a 2D texture with specifed wrapping conditions
*/
#include "gl_core_4_3.hpp"
#include "Bitmap.h"

/*! \class Texture
\brief Creates a 2D texture with specifed wrapping conditions
*/
    class Texture {
	private:
		GLfloat m_originalWidth;//!< Gets the original width of bitmap
		GLfloat m_originalHeight; //!< Gets the original height of bitmap
		GLuint m_texture; //!< 2D Texture handle

    public:
		 Texture(int iunit,const Bitmap& bitmap,GLint minMagFiler = gl::LINEAR, GLint wrapMode = gl::CLAMP_TO_EDGE); //!< Constructor
        GLfloat originalWidth() const; //!< Gets the original width of bitmap
        GLfloat originalHeight() const; //!< Gets the original height of bitmap
		GLuint getTextureId(); //!< Gets the texture handle
  };