#pragma once
/*!
* @file ShaderLinkerComponent.h
* Header file Creates and links to the shaders
*/

#include "gl_core_4_3.hpp"
#include <string>

/*! \class ShaderLinkerComponent
\brief Creates and links to the shaders
*/

class ShaderLinkerComponent
{
	private:
		GLuint m_programHandle; //!< The main program handle
		void linkShaders(GLint vertShader, GLint fragShader); //!< Links the shader
		std::string m_svertexShader; //!< Vertex shader file reference
		std::string m_sfragmentShader; //!< Fragment shader file reference

	public:
		ShaderLinkerComponent(std::string svertexshader, std::string sfragmentshader);
		void createShaders(); //!< Creates the fragment and vertex shaders
		GLuint getProgramHandle(); //!< Returns the main program handle
		void setUseShader(); //!< Uses the current shader

};