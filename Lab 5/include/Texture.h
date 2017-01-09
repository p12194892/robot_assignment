#pragma once

#include "gl_core_4_3.hpp"
#include "Bitmap.h"

    class Texture {

	private:
		GLfloat _originalWidth;
		GLfloat _originalHeight;
		Texture(const Texture&);

    public:
        /**
         Creates a texture from a bitmap.
         
         The texture will be loaded upside down because tdogl::Bitmap pixel data
         is ordered from the top row down, but OpenGL expects the data to
         be from the bottom row up.
         
         @param bitmap  The bitmap to load the texture from
         @param minMagFiler  GL_NEAREST or GL_LINEAR
         @param wrapMode GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, or GL_CLAMP_TO_BORDER
         */
        Texture(int iunit,const Bitmap& bitmap,
                GLint minMagFiler = gl::LINEAR,
                GLint wrapMode = gl::CLAMP_TO_EDGE);

        /**
         @result The original width (in pixels) of the bitmap this texture was made from
         */
        GLfloat originalWidth() const;

        /**
         @result The original height (in pixels) of the bitmap this texture was made from
         */
        GLfloat originalHeight() const;
        
   
    };