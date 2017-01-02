

#ifndef FILEREADER_H
#define FILEREADER_H
#include <vector>
#include "glm\glm.hpp"

using namespace std;
using namespace glm;

class FileReader
{
private:
	vector <glm::vec3> m_points;
	vector <glm::vec3> m_normals;
	vector <glm::vec2>m_texCoords;
	vector <int> m_VertexIndices;
	vector <int> m_uvIndices;
	vector <int> m_normalIndices;
	vector <int> out_vertices;

public:
	FileReader();
	void ReadFile(const char * filename);
	vector <glm::vec3> getVertexPoints();
	vector <glm::vec3> getNormals();
	vector <glm::vec2> getTexPoints();
	vector <int> getIndices();
	void resetData();
};


#endif