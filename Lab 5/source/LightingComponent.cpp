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

	gl::Uniform3f(gl::GetUniformLocation(handle, "light.ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.diffuse"), m_lightColour.x, m_lightColour.y, m_lightColour.z);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.specular"), 1.0f, 1.0f, 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.quadratic"), 0.032f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.direction"), 0.0f, 1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.cutOff"), glm::cos(glm::radians(45.5f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.outerCutOff"), glm::cos(glm::radians(120.0f)));
}