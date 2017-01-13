#include "LightingComponent.h"

//!< Default Constructor
LightingComponent::LightingComponent()
{
	m_lightPosition = glm::vec3(-2.0f, -25.0f, 20.0f);
	m_lightColour = glm::vec3(glm::vec3(sin(1 * 2.0), sin(1 * 0.7), sin(1 * 1.3)));
}

//!< Setting the lighting uniform variables in the shader
void LightingComponent::setLightingParam(GLuint handle, CameraComponent& cameraLocation)
{
	//Set the uniform light variables

	gl::Uniform3f(gl::GetUniformLocation(handle, "light.position"), m_lightPosition.x,m_lightPosition.y, m_lightPosition.z);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.diffuse"), m_lightColour.x, m_lightColour.y, m_lightColour.z);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.ambient"), 0.1f ,0.1f, 0.1f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.specular"),1.0f, 1.0f, 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.quadratic"), 0.032f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light.direction"), 0.0f,-1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.cutOff"), glm::cos(glm::radians(24.5f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light.outerCutOff"), glm::cos(glm::radians(34.5f)));
	gl::Uniform3f(gl::GetUniformLocation(handle, "cameraPosition"), cameraLocation.position().x, cameraLocation.position().y, cameraLocation.position().z);
	gl::Uniform1f(gl::GetUniformLocation(handle, "material.shininess"), 32.0f);
	gl::Uniform1i(gl::GetUniformLocation(handle, "material.diffuse"), 0);
	gl::Uniform1i(gl::GetUniformLocation(handle, "material.specular"), 0);



}