#pragma once
/*!
* @file Cube.h
* Header file creating generic cube object
*/

#include "Mesh.h"
#include "string"

/*! \class Cube
\brief Generates a cube object
*/

//!< Inherits from Mesh as a cube object is a mesh
class Cube : public Mesh
{
	public:
		Cube(); //!< Default Constructor 
		Cube(GLuint programID); //!< Constructor
};