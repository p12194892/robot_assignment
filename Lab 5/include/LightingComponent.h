#pragma once
/*!
* @file LightingComponent.h
* Header file which sets the uniform variables which deal with lighting the scene
*/

#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"
#include "CameraComponent.h"

/*! \class LightingComponent
\brief sets the uniform variables which deal with lighting the scene
*/

class LightingComponent
{
	private:
		glm::vec3 m_lightPosition; //!< Light Position
		glm::vec3 m_lightColour; //!< Light Colour

	public:
		LightingComponent(); //!< Default Constructor
		void setLightingParam(GLuint handle, CameraComponent& cameraLocation); //!< Setting the lighting uniform variables in the shader
};