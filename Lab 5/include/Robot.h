#ifndef __ROBOT_H
#define __ROBOT_H

#include "Mesh.h"
#include "cube.h"
#include <vector>
#include "QuatCamera.h"
// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

class Robot
{
private:
	char legStates[2];
	char armStates[2];

	float legAngles[2];
	float armAngles[2];

	float rAngle;
	//make into a vector :)
	Mesh* head;
	Mesh* torso;
	Mesh* rightArm;
	Mesh* leftArm;
	Mesh* rightLeg;
	Mesh* leftLeg;
	Mesh* leftFoot;
	Mesh* rightFoot;

	//One model matrix for the whole robot instead of many!
	glm::mat4 modelMatrix;

	// methods to draw the parts of the robot


public:

	Robot();
	Robot(GLuint programID);
	virtual ~Robot();

	// draws the entire robot
	void DrawRobot();

	// Creates Robot
	void CreateRobot(GLuint programID);

	//Returns model matrix for each body part

	void DrawRobot(QuatCamera c, GLuint programID, glm::vec3 startPos, float angle);
	void setMatrices(QuatCamera camera, GLuint programID);

	void Prepare(float seconds, bool b);
	void AnimateRobot(bool b, char c);
};

#endif