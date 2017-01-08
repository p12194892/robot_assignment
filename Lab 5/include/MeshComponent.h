#pragma once
/*!
* @file MeshComponent.h
* Header file creating a mesh object
*/

#include <vector>
#include <string>
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"
#include "Texture.h"
#include "CameraComponent.h"

/*! \class MeshComponent
\brief Generates a general mesh
*/

class MeshComponent
{
	protected:
		std::vector<glm::vec3> m_vertices; //!< Vertex data
		std::vector<glm::vec3> m_normals; //!< Normal data 
		std::vector< int> m_indices; //!< Index data 
		std::vector<glm::vec2> m_uvData; //!< UV data
		GLuint m_vaoHandle; //!< Vertex array buffer
		GLuint m_programHandleID; //!< Main program handle
		bool m_bDrawable; //!< If the mesh is drawable
		Texture *m_gTexture; //!< Texture Object
	    int m_iTexUnit; //!< Texture Unit
		glm::mat4 m_modelMatrix; //!< Model Matrix
		glm::vec3 m_startPosition; //!< Starting position 
		std::string m_sMeshObjectID; //!< Mesh ID

	public:
		MeshComponent(); //!< Default Constructor 
		MeshComponent(std::string name); //!< Constructor 
		void Load(GLuint programID); //!< Loads the buffers
		void draw(); //!< Draws the mesh
		void cubeMap(std::string s, std::string s2); //!< Cube Maps the texture (May move to cube)
		void setVertrices(std::vector<glm::vec3> v); //!< Sets vertex data
		void setIndices(std::vector< int> i); //!< Sets index data
		void setNormals(std::vector<glm::vec3> n); //!< Sets normal data
		void setUVs(std::vector<glm::vec2> uv);
		void setDrawable(bool b); //!< Set if the mesh is drawable
		bool isDrawable(); //!< If the mesh is drawable
		void loadTexture(std::string sname, std::string s2); //!< Loads the texture
		glm::mat4 getModelMat(); //!< Gets the model matrix
		void translateModelMat(glm::vec3 t); //!< Translates the mesh
		void scaleModelMat(glm::vec3 s); //!< Scales the mesh
		void rotateModelMat(glm::vec3 r); //!<  Rotates the mesh
		glm::vec3 getStartPos(); //!< Gets the starting position of the mesh
		void setStartPos(glm::vec3 s); //!< Sets the starting position of the mesh
		void updateModelMatrix(CameraComponent camera, GLuint programHandle);//!< Updates the model matrix
		void setTextureUnit(int i);
		std::string MeshComponent::getID();

};