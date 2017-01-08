#pragma once
/*!
* @file CollisionComponent.h
* Header file control of detecting collisions
*/

#include <vector>
#include "MeshComponent.h"

/*! \class CollisionComponent
\brief The control of detecting collisions between 3d objects
*/

class CollisionComponent
{
	public:
		CollisionComponent(); //!< Default Constructor 
		std::vector<MeshComponent*> checkVectorDistance(std::vector<MeshComponent*> objects, glm::vec3 robotPos);//!< Checks the distance between two starting vectors
};



