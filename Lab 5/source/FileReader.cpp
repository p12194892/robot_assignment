#define _CRT_SECURE_NO_DEPRECATE
#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"

//!< Default Constructor 
FileReader::FileReader()
{

}

//!< Reads in the obj file and puts data in the specified vectors
void FileReader::ReadFile(const char * filename)
{	
		FILE * file = fopen(filename, "r");

		//test
		FILE * file2 = fopen(filename, "r");

		if (file == NULL) {
			printf("Impossible to open the file !\n");
		}

		std::vector <glm::vec3> points;
		std::vector <glm::vec3> normals;
		std::vector <glm::vec2> texCoords;
		std::vector <int> faces;

		while (1) {

			char lineHeader[128] = "c";	//std::string lineHeader;


			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);

			
			if (res == EOF)
			{
				std::cout << "End Of File";
				break; // EOF = End Of File. Quit the loop.
			}

			//vertex
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);	
				m_vertexPoints.push_back(vertex);
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

				unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
				int matches = 0;

				//bool bSlash = false;
				
			/*	for (int i = 1 < 0; i < 100; i++)
				{
					if (mystring[i] == '/')
					{
						//if you find a / it means that you need to use the other parser....
						bSlash = true;
						break;
					}
				}*/

				/*if (bSlash == false) 
				{
					matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
					m_VertexIndices.push_back(vertexIndex[0]);
					m_VertexIndices.push_back(vertexIndex[1]);
					m_VertexIndices.push_back(vertexIndex[2]);
				}

				else
				{*/
					matches = fscanf(file, " %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
				
					if (matches == 9)
					{

						m_vertexIndices.push_back(vertexIndex[0]);
						m_vertexIndices.push_back(vertexIndex[1]);
						m_vertexIndices.push_back(vertexIndex[2]);
						m_uvIndices.push_back(uvIndex[0]);
						m_uvIndices.push_back(uvIndex[1]);
						m_uvIndices.push_back(uvIndex[2]);
						m_normalIndices.push_back(normalIndex[0]);
						m_normalIndices.push_back(normalIndex[1]);
						m_normalIndices.push_back(normalIndex[2]);
					}
					if (matches != 12 && matches != 9)
					{
						printf("File can't be read by our simple parser : ( Try exporting with other options\n");
						break;
					}

					//Its a quad
					if (matches == 12)
					{
						//4 Indices! need to change to read in 3 for triangles..
						m_vertexIndices.push_back(vertexIndex[0]);
						m_vertexIndices.push_back(vertexIndex[1]);
						m_vertexIndices.push_back(vertexIndex[2]);

						m_vertexIndices.push_back(vertexIndex[0]);
						m_vertexIndices.push_back(vertexIndex[2]);
						m_vertexIndices.push_back(vertexIndex[3]);

						m_uvIndices.push_back(uvIndex[0]);
						m_uvIndices.push_back(uvIndex[1]);
						m_uvIndices.push_back(uvIndex[2]);

						m_uvIndices.push_back(uvIndex[0]);
						m_uvIndices.push_back(uvIndex[2]);
						m_uvIndices.push_back(uvIndex[3]);

						m_normalIndices.push_back(normalIndex[0]);
						m_normalIndices.push_back(normalIndex[1]);
						m_normalIndices.push_back(normalIndex[2]);

						m_normalIndices.push_back(normalIndex[0]);
						m_normalIndices.push_back(normalIndex[2]);
						m_normalIndices.push_back(normalIndex[3]);
					}
				}
		//	}
	}
		//Getting indicies for vertex 
		for (unsigned int i = 0; i < m_vertexIndices.size(); i++) {
			unsigned int vertexIndex = m_vertexIndices[i];
			m_completeVertex.push_back(vertexIndex - 1);
		}

		

		std::cout << "Loaded mesh from: " << filename << std::endl;
}

//!< Gets vertex coordinates
std::vector <glm::vec3> FileReader::getVertexPoints()
{
	return m_vertexPoints;
}

//!< Gets Normal coordinates
std::vector <glm::vec3> FileReader::getNormals()
{
	return m_normals;
}
//!< Gets Texture coordinates 
std::vector <glm::vec2> FileReader::getTexPoints()
{
	return m_texCoords;
}

//!< Gets the Index coordinates
std::vector<int> FileReader::getIndices()
{
	return m_completeVertex;
}
//!< Resets the mesh data stored in the vectors to empty
void FileReader::resetData()
{
	m_vertexPoints.clear();
	m_normals.clear();
	m_texCoords.clear();
	m_vertexIndices.clear();
    m_uvIndices.clear();
	m_normalIndices.clear();
	m_completeVertex.clear();
}