#include "Mesh.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "Bitmap.h"

Mesh::Mesh() {

}

void Mesh::Load()
{
	GLuint index_buffer;
	GLuint vertex_buffer;


	// Create and populate the buffer objects using separate buffers
	//Create and set-up the vertex array object
	//Holds the vbos
	gl::GenVertexArrays(1, &vaoHandle);

	//index buffer
	gl::GenBuffers(1, &index_buffer);

	//vertex buffer
	gl::GenBuffers(1, &vertex_buffer);

	gl::BindVertexArray(vaoHandle);
	//Positions
	gl::BindBuffer(gl::ARRAY_BUFFER, vertex_buffer);
	gl::BufferData(gl::ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], gl::STATIC_DRAW);
	GLuint locl = gl::GetAttribLocation(programHandleID, "vertPosition");
	gl::VertexAttribPointer(locl, 3, gl::FLOAT, FALSE, sizeof(glm::vec3), (GLubyte *)NULL);
	gl::EnableVertexAttribArray(locl);  //Enables the array for vertex

	//Indices
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, index_buffer);//activates the buffer for the indicies //Putting the data into the buffer
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], gl::STATIC_DRAW);//finds how big the buffer needs to be
}

void Mesh::Draw()
{
	gl::BindVertexArray(vaoHandle);
	gl::DrawElements(gl::TRIANGLES, (GLsizei)m_indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);
}


void Mesh::cubeMap(std::string s, const GLchar s2) {
	std::string suffixes[] = { "right","left","up", "down", "back", "front" };
	GLuint target[6];
	target[0] = gl::TEXTURE_CUBE_MAP_POSITIVE_X; //Right
	target[1] = gl::TEXTURE_CUBE_MAP_NEGATIVE_X; //Left
	target[2] = gl::TEXTURE_CUBE_MAP_POSITIVE_Y; //Top
	target[3] = gl::TEXTURE_CUBE_MAP_NEGATIVE_Y; //Bottom
	target[4] = gl::TEXTURE_CUBE_MAP_POSITIVE_Z; // Back
	target[5] = gl::TEXTURE_CUBE_MAP_NEGATIVE_Z; //front

	gl::ActiveTexture(gl::TEXTURE0);
	GLuint loc;
	gl::GenTextures(1, &loc);
	gl::BindTexture(gl::TEXTURE_CUBE_MAP, loc);

	for (int i = 0; i < 6; i++)
	{
		//change this to 6 pictures
		std::string textureFile = std::string(s) + "_" + suffixes[i] + ".png";
		Bitmap bmp = Bitmap::bitmapFromFile(textureFile);
		gl::TexImage2D(target[i], 0, gl::RGB, bmp.width(), bmp.height(), 0, gl::RGB, gl::UNSIGNED_BYTE, bmp.pixelBuffer());
	}

	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameteri(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	
	GLuint loc2 = gl::GetUniformLocation(programHandleID, &s2);
	gl::Uniform1i(loc2, 0);
}
void Mesh::setVertrices(std::vector<glm::vec3> v)
{
	m_vertices = v;
}

void Mesh::setIndices(std::vector<int> i)
{
	m_indices = i;
}
