#define _CRT_SECURE_NO_DEPRECATE
#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"

using namespace std;


FileReader::FileReader()
{

}

void FileReader::ReadFile(const char  * filename)
{	
		FILE * file = fopen(filename, "r");
		if (file == NULL) {
			printf("Impossible to open the file !\n");
		}

		vector <glm::vec3> points;
		vector <glm::vec3> normals;
		vector <glm::vec2> texCoords;
		vector <int> faces;

		while (1) {

			char lineHeader[128] = "c";	//std::string lineHeader;
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			//vertex
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);	
				m_points.push_back(vertex);	
			}

			//Textures
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				m_texCoords.push_back(uv);
			}

			//Normals
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				m_normals.push_back(normal);
			}
			//Indices
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					break;
				}
				m_VertexIndices.push_back(vertexIndex[0]);
				m_VertexIndices.push_back(vertexIndex[1]);
				m_VertexIndices.push_back(vertexIndex[2]);
				m_uvIndices.push_back(uvIndex[0]);
				m_uvIndices.push_back(uvIndex[1]);
				m_uvIndices.push_back(uvIndex[2]);
				m_normalIndices.push_back(normalIndex[0]);
				m_normalIndices.push_back(normalIndex[1]);
				m_normalIndices.push_back(normalIndex[2]);
			}

	}
		
		for (unsigned int i = 0; i < m_VertexIndices.size(); i++) {
			unsigned int vertexIndex = m_VertexIndices[i];
			out_vertices.push_back(vertexIndex - 1);
		}
		cout << "Loaded mesh from: " << filename << endl;
}


vector <glm::vec3> FileReader::getVertexPoints()
{
	return m_points;
}

vector <glm::vec3> FileReader::getNormals()
{
	return m_normals;
}

vector <glm::vec2> FileReader::getTexPoints()
{
	return m_texCoords;
}

vector<int> FileReader::getIndices()
{
	return out_vertices;
}