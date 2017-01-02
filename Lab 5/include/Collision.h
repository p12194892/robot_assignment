#pragma once
/*!
* @file Collision.h
* Header file control of detecting collisions
*/

#include <vector>
#include "Mesh.h"

/*! \class Collision
\brief The control of detecting collisions between 3d objects
*/

class Collision
{
	public:
		Collision(); //!< Default Constructor 
		std::vector<Mesh*> checkVectorDistance(std::vector<Mesh*> objects, glm::vec3 robotPos);//!< Checks the distance between two starting vectors
};



