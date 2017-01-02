#include "cube.h"

//!< Default Constructor 
Cube::Cube()
{

}

//!< Constructor
Cube::Cube(GLuint programID)
{
	//1*1*1 Generic cube
	m_vertices.push_back(glm::vec3(-1.0f, -1.0, 1.0f));//0 V1
	m_vertices.push_back(glm::vec3(1.0f, -1.0f, 1.0f));//1 V2
	m_vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0f));//2 V3
	m_vertices.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));//3 V4
	m_vertices.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));//4 V5
	m_vertices.push_back(glm::vec3(1.0f, -1.0f, -1.0f));//5 V6
	m_vertices.push_back(glm::vec3(1.0f, 1.0, -1.0f));//6 V7
	m_vertices.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));//7 V8

	m_indices = {
		0,1,2,
		2,3,0,
		1,5,6,
		6,2,1,
		7,6,5,
		5,4,7,
		4,0,3,
		3,7,4,
		4,5,1,
		1,0,4,
		3,2,6,
		6,7,3
	};

	//make sure the program handle is the main handle
	m_programHandleID = programID;

	//Load the mesh data into the buffers
	Load(m_programHandleID);
}

