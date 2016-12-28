#pragma once
#include <vector>
#include <string>
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"
#include "Texture.h"

class Mesh
{
	protected:
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec3> m_normals;
		std::vector< int> m_indices;
		std::vector<glm::vec2> m_uvData;
		GLuint vaoHandle;
		GLuint programHandleID;
		bool m_bDrawable;
		Texture *m_gTexture;
		std::string m_sTexName;
		 GLchar m_TexType;
		 int m_iTexUnit;

	public:
		Mesh();
		void Draw();
		void cubeMap(std::string s, const GLchar s2);
		void setVertrices(std::vector<glm::vec3> v);
		void setIndices(std::vector< int> i);
		void setNormals(std::vector<glm::vec3> n);
		void Load(GLuint programID);
		void setDrawable(bool b);
		bool isDrawable();
		void loadTexture();

};