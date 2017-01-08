#pragma once
#include "gl_core_4_3.hpp"

class ShaderLinkerComponent
{
	private:
		GLuint m_programHandle; //!< The main program handle
	public:
		ShaderLinkerComponent();
		void createShaders(); //!< Creates the fragment and vertex shaders
		void linkShaders(GLint vertShader, GLint fragShader); //!< Links the shader
		GLuint getProgramHandle();
};