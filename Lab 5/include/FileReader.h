#pragma once
/*!
* @file FileReader.h
* Header file containing the file reader attributes
*/

#include <vector>
#include "glm\glm.hpp"

/*! \class FileReader
\brief Reads in vertex, vertex normals, textures and index data from obj files
*/

class FileReader
{
private:
	std::vector <glm::vec3> m_vertexPoints; //!< Vertex coordinates
	std::vector <glm::vec3> m_normals; //!< Normal coordinates
	std::vector <glm::vec2>m_texCoords; //!< Texture coordinates
	std::vector <int> m_vertexIndices; //!< Indices for drawing vertex data 
	std::vector <int> m_uvIndices; //!< Indices for drawing uv texture data 
	std::vector <int> m_normalIndices; //!< Indices for drawing normal data 
	std::vector <int> m_completeVertex; //!< Vertex coordinate data (-1 in the index)

public:
	FileReader(); //!< Default Constructor 
	void ReadFile(const char * filename); //!< Reads in the obj file and puts data in the specified vectors
	std::vector <glm::vec3> getVertexPoints(); //!< Gets vertex coordinates
	std::vector <glm::vec3> getNormals(); //!<  Gets Normal coordinates
	std::vector <glm::vec2> getTexPoints(); //!< Gets Texture coordinates 
	std::vector <int> getIndices(); //!< Gets the Index coordinates
	void resetData(); //!< Resets the mesh data stored in the vectors to empty
};
