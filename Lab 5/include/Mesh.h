#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"

class Mesh
{
	protected:
		std::vector<glm::vec3> m_vertices;
		std::vector<unsigned int> m_indices;
		std::vector<glm::vec2> m_uvData;
		glm::mat4 m_model;
		GLuint vaoHandle;
		GLuint programHandleID;

		void Load();
	public:
		Mesh();
		void transformCube(const glm::vec3 t, const glm::vec3 s, const glm::vec3 r, const float angle);
		glm::mat4 getModelMatrix();
		void translate(const glm::vec3 t);
		void rotate(const float a, const glm::vec3 r);
		void scale(const glm::vec3 s);
		void Draw();
		void cubeMap(std::string s, const GLchar s2);
};