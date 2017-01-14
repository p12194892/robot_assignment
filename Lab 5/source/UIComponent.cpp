#include "UIComponent.h"

//!< Default Constructor 
UIComponent::UIComponent()
{

}

//!<  Constructor 
UIComponent::UIComponent(GLuint programID)
{
	//Loading a 2d rectangle to texture 
	m_vertices.push_back(glm::vec3(-0.1f, 0.1f, 0.0f));//0 V1
	m_vertices.push_back(glm::vec3(0.1f, 0.1f, 0.0f));//1 V2
	m_vertices.push_back(glm::vec3(0.1f, -0.1, 0.0f));//2 V3
	m_vertices.push_back(glm::vec3(-0.1f, -0.1f, 0.0f));//3 V4

	m_uvData.push_back(glm::vec2(0.0f, 1.0f));
	m_uvData.push_back(glm::vec2(1.0f, 1.0f));
	m_uvData.push_back(glm::vec2(1.0f, 0.0f));
	m_uvData.push_back(glm::vec2(0.0f, 0.0f));

	m_indices = {
		0,1,3,
		1,3,2
	};
	Load(programID);

}
