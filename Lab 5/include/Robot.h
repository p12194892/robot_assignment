/*!
* @file Robot.h
* Header file containing the robot attributes
*/

#ifndef __ROBOT_H
#define __ROBOT_H

/*! \class Robot
\brief The Robot that walks around the 3D environment 
*/

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
	char m_cLegStates[2]; //!< The leg state
	char m_cArmStates[2]; //!< The arm state
	float m_fLegAngles[2];//!< The leg angle
	float m_fArmAngles[2];//!< The arm angle
	Mesh* m_Head; //!< The mesh of the robot head
	Mesh* m_Torso; //!< The mesh of the robot torso
	Mesh* m_RightArm; //!< The mesh of the right arm
	Mesh* m_LeftArm; //!< The mesh of the left arm
	Mesh* m_RightLeg; //!< The mesh of the right leg
	Mesh* m_LeftLeg; //!< The mesh of the left leg
	Mesh* m_LeftFoot; //!< The mesh of the left foot
	Mesh* m_RightFoot; //!< The mesh of the right foot
	glm::mat4 m_ModelMatrix; //!< Model matrix of the entire robot
public:
	Robot(); //!< Default constructor
	Robot(GLuint programID/*!The main program handle*/); //!< Constructor 
	virtual ~Robot(); //!< Destructor 
	void DrawRobot(QuatCamera c/*!The camera*/, GLuint programID/*!The main program handle*/, glm::vec3 startPos/*!The start position offset*/, float angle/*!The angle of rotation*/); //!< Draws the robot to the screen, taking it's starting position, the angle of rotation, the camera to update the model matrix and the main program handle
	void UpdateModelMatrix(QuatCamera camera/*!The camera*/, GLuint programID/*!The main program handle*/); //!< Updates the model matrix based on translation, scale and rotation
	void Prepare(float speed, float angle, float seconds/*!seconds of time*/, bool b/*if the key has been pressed*/); //!< Animations of the leg and arm movements
};

#endif