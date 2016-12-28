#include "Mesh.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "Bitmap.h"

Mesh::Mesh() {
	m_bDrawable = true;
}

void Mesh::Load(GLuint programID)
{
	m_programHandleID = programID;
	GLuint index_buffer;
	GLuint vertex_buffer;
	GLuint normal_buffer;
	GLuint uv_buffer;
	// Create and populate the buffer objects using separate buffers
	//Create and set-up the vertex array object
	//Holds the vbos
	gl::GenVertexArrays(1, &m_vaoHandle);

	//index buffer
	gl::GenBuffers(1, &index_buffer);

	//vertex buffer
	gl::GenBuffers(1, &vertex_buffer);

	//Normal buffer
	gl::GenBuffers(1, &normal_buffer);

	//uv buffer
	gl::GenBuffers(1, &uv_buffer);

	gl::BindVertexArray(m_vaoHandle);
	//Positions
	gl::BindBuffer(gl::ARRAY_BUFFER, vertex_buffer);
	gl::BufferData(gl::ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], gl::STATIC_DRAW);
	GLuint locl = gl::GetAttribLocation(m_programHandleID, "vertPosition");
	gl::VertexAttribPointer(locl, 3, gl::FLOAT, FALSE, sizeof(glm::vec3), (GLubyte *)NULL);
	gl::EnableVertexAttribArray(locl);  //Enables the array for vertex

	if (m_normals.size() != 0)
	{
		//Normals
		gl::BindBuffer(gl::ARRAY_BUFFER, normal_buffer);
		gl::BufferData(gl::ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], gl::STATIC_DRAW);
		GLuint locl2 = gl::GetAttribLocation(m_programHandleID, "VertexNormal");
		gl::VertexAttribPointer(locl2, 3, gl::FLOAT, FALSE, sizeof(glm::vec3), (GLubyte *)NULL);
		gl::EnableVertexAttribArray(locl2);  //Enables the array for vertex
	}
	if (m_uvData.size() != 0)
	{
		//Texture
		gl::BindBuffer(gl::ARRAY_BUFFER, uv_buffer);
		gl::BufferData(gl::ARRAY_BUFFER, m_uvData.size() * sizeof(glm::vec2), &m_uvData[0], gl::STATIC_DRAW);
		GLuint loc3 = gl::GetAttribLocation(m_programHandleID, "fragTexCoord");
		gl::VertexAttribPointer(loc3, 2, gl::FLOAT, FALSE, sizeof(glm::vec2), (GLubyte *)NULL);
		gl::EnableVertexAttribArray(loc3);	
	}

	//Indices
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, index_buffer);//activates the buffer for the indicies //Putting the data into the buffer
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], gl::STATIC_DRAW);//finds how big the buffer needs to be
	
	if (m_uvData.size() != 0)
	{																											  
		//Load the texture
	/*	Bitmap bmp = Bitmap::bitmapFromFile(m_sTexName);
		bmp.flipVertically();
		m_gTexture = new Texture(bmp);

		//Set texture
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, m_gTexture->object());
		GLint loc = gl::GetUniformLocation(programHandleID, "tex");
		gl::Uniform1f(loc, 0);

		gl::ActiveTexture(gl::TEXTURE1);
		gl::BindTexture(gl::TEXTURE_2D, m_gTexture->object());
		GLint l = gl::GetUniformLocation(programHandleID, "but");
		gl::Uniform1f(l, 1);
		//gl::Uniform1f(loc, 1);*/
		loadTexture();
	}
}

void Mesh::loadTexture()
{
	//Load the texture
	Bitmap bmp = Bitmap::bitmapFromFile(m_sTexName);
	bmp.flipVertically();
	m_gTexture = new Texture(bmp);

	//Set texture
	if (m_iTexUnit == 1)
	{
		gl::ActiveTexture(gl::TEXTURE1);
		gl::Uniform1i(gl::GetUniformLocation(m_programHandleID, "tex2"), m_iTexUnit);
		gl::BindTexture(gl::TEXTURE_2D, m_gTexture->object());
	}

	else
	{
		gl::ActiveTexture(gl::TEXTURE0);
		gl::Uniform1i(gl::GetUniformLocation(m_programHandleID, "tex"), m_iTexUnit);
		gl::BindTexture(gl::TEXTURE_2D, m_gTexture->object());
	}
	

	
	//GLint loc = gl::GetUniformLocation(programHandleID, &m_TexType);
	//gl::Uniform1f(loc, 0);

}

void Mesh::Draw()
{
	gl::BindVertexArray(m_vaoHandle);
	gl::DrawElements(gl::TRIANGLES, (GLsizei)m_indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);
}

void Mesh::cubeMap(std::string s, std::string s2) {
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
	
	GLuint loc2 = gl::GetUniformLocation(m_programHandleID, s2.c_str());
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

void Mesh::setNormals(std::vector<glm::vec3> n)
{
	m_normals = n;
}

void Mesh::setDrawable(bool b)
{
	m_bDrawable = b;
}

bool Mesh::isDrawable()
{
	return m_bDrawable;
}

glm::mat4 Mesh::getModelMat()
{
	return m_ModelMatrix;
}

void Mesh::translateModelMat(glm::vec3 t)
{
	m_ModelMatrix *= glm::translate(t);
}

void Mesh::scaleModelMat(glm::vec3 s)
{
	m_ModelMatrix *= glm::scale(s);
}

void Mesh::rotateModelMat(glm::vec3 r)
{
	//To be done
}

glm::vec3 Mesh::getStartPos()
{
	return m_startPosition;
}

void Mesh::setStartPos(glm::vec3 s)
{
	m_startPosition = s;
}