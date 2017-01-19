#include "MeshComponent.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "Bitmap.h"

//!< Default Constructor 
MeshComponent::MeshComponent() {
	m_bDrawable = true;
	m_banimating = false;
}

//!< Constructor 
MeshComponent::MeshComponent(std::string name)
{
	m_bDrawable = true;
	m_sMeshObjectID = name;
	m_banimating = false;
}

//!< Loads the buffers
void MeshComponent::Load(GLuint programID)
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
		GLuint locl2 = gl::GetAttribLocation(m_programHandleID, "vertNormal");
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
}

//!< Loads the texture
void MeshComponent::loadTexture(std::string sname)
{
	//Load the texture
	Bitmap bmp = Bitmap::bitmapFromFile(sname);
	bmp.flipVertically();
	m_gTexture = new Texture(m_iTexUnit,bmp);
}

//!< Draws the mesh
void MeshComponent::draw()
{
	gl::BindVertexArray(m_vaoHandle);
	gl::DrawElements(gl::TRIANGLES, (GLsizei)m_indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);

}

//!< Sets vertex data
void MeshComponent::setVertrices(std::vector<glm::vec3> v)
{
	m_vertices = v;
}

//!< Sets index data
void MeshComponent::setIndices(std::vector<int> i)
{
	m_indices = i;
}

//!< Sets normal data
void MeshComponent::setNormals(std::vector<glm::vec3> n)
{
	m_normals = n;
}

//!< Set if the mesh is drawable
void MeshComponent::setDrawable(bool b)
{
	m_bDrawable = b;
}

//!< If the mesh is drawable
bool MeshComponent::isDrawable()
{
	return m_bDrawable;
}

//!< Gets the model matrix
glm::mat4 MeshComponent::getModelMat()
{
	return m_modelMatrix;
}

//!< Translates the mesh
void MeshComponent::translateModelMat(glm::vec3 t)
{
	m_modelMatrix *= glm::translate(t);
}

//!< Scales the mesh
void MeshComponent::scaleModelMat(glm::vec3 s)
{
	m_modelMatrix *= glm::scale(s);
}

//!<  Rotates the mesh
void MeshComponent::rotateModelMat(float a, glm::vec3 r)
{
	m_modelMatrix *= glm::rotate(glm::radians(a), r);
}

//!< Gets the starting position of the mesh
glm::vec3 MeshComponent::getStartPos()
{
	return m_startPosition;
}

//!< Sets the starting position of the mesh
void MeshComponent::setStartPos(glm::vec3 s)
{
	m_startPosition = s;
}

//!< Updates the model matrix
void MeshComponent::updateModelMatrix(CameraComponent& camera, GLuint programHandle)
{
	camera.updateMVP(m_modelMatrix);
	//need to send view, model and projection seperately
	gl::UniformMatrix4fv(gl::GetUniformLocation(programHandle, "M"), 1, gl::FALSE_, &m_modelMatrix[0][0]);
	gl::UniformMatrix4fv(gl::GetUniformLocation(programHandle, "V"), 1, gl::FALSE_, &camera.getView()[0][0]);
	gl::UniformMatrix4fv(gl::GetUniformLocation(programHandle, "P"), 1, gl::FALSE_, &camera.projection()[0][0]);
	gl::UniformMatrix4fv(gl::GetUniformLocation(programHandle, "MVP"), 1, gl::FALSE_, &camera.getMVP()[0][0]);
}

//!< Sets a texture unit
void MeshComponent::setTextureUnit(int i)
{
	m_iTexUnit = i;
}

//!< Sets UV texture coordinates
void MeshComponent::setUVs(std::vector<glm::vec2> uv)
{
	m_uvData = uv;
}

//!< Gets the mesh ID
std::string MeshComponent::getID()
{
	return m_sMeshObjectID;
}

//!< Gets a texture unit
int MeshComponent::getTextureUnit()
{
	return m_iTexUnit;
}

//!< Gets the textured 2D object
Texture* MeshComponent::getTextureObject()
{
	return m_gTexture;
}

//!< Gets a cube map texture handle
GLuint MeshComponent::getCubeMapTexture()
{
	return m_cubemapTex;
}
//!< Sets if the object is animating
void MeshComponent::setAnimating(bool b)
{
	m_banimating = b;
}

//!< If the object is animating
bool MeshComponent::isAnimating()
{
	return m_banimating;
}