#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"

class Mesh
{
	protected:
		std::vector<glm::vec3> m_vertices;
		std::vector< int> m_indices;
		std::vector<glm::vec2> m_uvData;
		GLuint vaoHandle;
		GLuint programHandleID;


	public:
		Mesh();
		void Draw();
		void cubeMap(std::string s, const GLchar s2);
		void setVertrices(std::vector<glm::vec3> v);
		void setIndices(std::vector< int> i);
		void Load(GLuint programID);
};