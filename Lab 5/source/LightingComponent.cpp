#include "LightingComponent.h"

//!< Default Constructor
LightingComponent::LightingComponent()
{
}

//!< Setting the lighting uniform variables in the shader
void LightingComponent::setLightingParam(GLuint handle, CameraComponent& cameraLocation)
{
	//Set the uniform light variables
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].intensities"), 3.0f, 3.0f, 3.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[0].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].quadratic"), 0.032f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[0].outerCutOff"), glm::cos(glm::radians(10.0f)));

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].position"), 10.0f, -27.0f, -20.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].intensities"), 0.0f, 0.0f, 5.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[1].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].quadratic"), 0.032f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[1].outerCutOff"), glm::cos(glm::radians(10.0f)));

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].position"), -20.0f, -27.0f, -20.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].intensities"), 5.0f, 5.0f, 0.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[2].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].quadratic"), 0.032f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[2].outerCutOff"), glm::cos(glm::radians(10.0f)));

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[3].position"), 20.0f, -27.0f, 20.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[3].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[3].intensities"), 5.0f, 0.0f, 0.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[3].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[3].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[3].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[3].quadratic"), 0.032f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[3].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[3].outerCutOff"), glm::cos(glm::radians(10.0f)));

	gl::Uniform3f(gl::GetUniformLocation(handle, "light[4].position"), -20.0f, -27.0f, 20.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[4].ambient"), 1.0f, 1.0f, 1.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[4].intensities"), 0.0f, 5.0f, 0.0f);
	gl::Uniform3f(gl::GetUniformLocation(handle, "light[4].direction"), 0.0f, -1.0f, 0.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[4].constant"), 1.0f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[4].linear"), 0.09f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[4].quadratic"), 0.032f);
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[4].cutOff"), glm::cos(glm::radians(5.0f)));
	gl::Uniform1f(gl::GetUniformLocation(handle, "light[4].outerCutOff"), glm::cos(glm::radians(10.0f)));
}
	
