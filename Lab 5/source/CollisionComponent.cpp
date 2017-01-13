#include "CollisionComponent.h"
#include <glm\glm.hpp>

//!< Default Constructor
CollisionComponent::CollisionComponent()
{

}

//!< Checks the distance between two starting vectors
std::vector<MeshComponent*> CollisionComponent::checkVectorDistance(std::vector<MeshComponent*> objects, glm::vec3 robotPos)
{
	std::vector<MeshComponent*> meshObjects = objects;

	for (int i = 0; i < meshObjects.size(); i++)
	{
		if (meshObjects.at(i)->isDrawable() == true)
		{
			//Works out the distance between the objects and the robot
			glm::vec3 distance;
			distance.x = meshObjects.at(i)->getStartPos().x - robotPos.x;
			distance.z = meshObjects.at(i)->getStartPos().z - robotPos.z;

			float d = sqrt(dot(distance, distance));

			if (d < 10)
			{
				meshObjects.at(i)->setDrawable(false);

			}
		}
	}
	return meshObjects;
}