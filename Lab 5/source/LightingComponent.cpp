#include "LightingComponent.h"

//!< Default Constructor
LightingComponent::LightingComponent()
{
	m_lightPosition = glm::vec3(-2.0f, -26.0f, -20.0f);
	m_lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
}

//!< Setting the lighting uniform variables in the shader
void LightingComponent::setLightingParam(GLuint handle, CameraComponent& cameraLocation)
{
	//Set the uniform light variables

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].ambient"), 1.0f, 1.0f, 1.0f);	
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].intensities"),4.0f, 4.0f, 4.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].quadratic"), 0.032f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].direction"), 0.0f, 1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].outerCutOff"), glm::cos(glm::radians(10.0f)));

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].intensities"),0.0f, 0.0f, 5.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].quadratic"), 0.032f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].direction"), 0.0f, 1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].outerCutOff"), glm::cos(glm::radians(10.0f)));

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].intensities"), 5.0f, 5.0f, 0.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].quadratic"), 0.032f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].direction"), 0.0f, 1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].outerCutOff"), glm::cos(glm::radians(10.0f)));
}