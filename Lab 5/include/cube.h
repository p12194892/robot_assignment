#pragma once
/*!
* @file Cube.h
* Header file creating generic cube object
*/

#include "MeshComponent.h"
#include "string"
#include "FileReader.h"
/*! \class Cube
\brief Generates a cube object
*/

//!< Inherits from Mesh as a cube object is a mesh
class Cube : public MeshComponent
{
	public:
		Cube(); //!< Default Constructor 
		Cube(GLuint programID, std::string sid, FileReader* m_read); //!< Constructor
};