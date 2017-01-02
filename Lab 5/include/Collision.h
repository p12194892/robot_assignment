#pragma once
#include <vector>
#include "Mesh.h"
/*!
* @file Collision.h
* Header file control of detecting collisions 
*/


/*! \class Collision
\brief The control of detecting collisions between 3d objects
*/

class Collision
{
	private:
	public:
		Collision();
		std::vector<Mesh*> checkVectorDistance(std::vector<Mesh*> objects, glm::vec3 robotPos);

};



