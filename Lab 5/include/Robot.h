#pragma once

/*!
* @file Robot.h
* Header file containing the robot attributes
*/


/*! \class Robot
\brief The Robot that walks around the 3D environment 
*/

#include "MeshComponent.h"
#include "cube.h"
#include <vector>
#include "CameraComponent.h"

// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

class Robot : public MeshComponent
{
private:
	char m_clegStates[2]; //!< The leg state
	char m_carmStates[2]; //!< The arm state
	float m_flegAngles[2];//!< The leg angle
	float m_farmAngles[2];//!< The arm angle
	MeshComponent* m_head; //!< The mesh of the robot head
	MeshComponent* m_torso; //!< The mesh of the robot torso
	MeshComponent* m_rightArm; //!< The mesh of the right arm
	MeshComponent* m_leftArm; //!< The mesh of the left arm
	MeshComponent* m_rightLeg; //!< The mesh of the right leg
	MeshComponent* m_leftLeg; //!< The mesh of the left leg
	MeshComponent* m_leftFoot; //!< The mesh of the left foot
	MeshComponent* m_rightFoot; //!< The mesh of the right foot
	float m_fspeed; //!< The speed of the robot
	float m_fanimationAngle; //!< The angle of arm and leg animation
	float m_fvariableAngle; //!< The angle of rotating the robot with key press

public:
	Robot(); //!< Default constructor
	Robot(GLuint programID/*!The main program handle*/); //!< Constructor 
	virtual ~Robot(); //!< Destructor 
	void drawRobot(CameraComponent c/*!The camera*/, GLuint programID/*!The main program handle*/); //!< Draws the robot to the screen, taking it's starting position, the angle of rotation, the camera to update the model matrix and the main program handle
	void prepare(float seconds/*!seconds of time*/, bool b/*if the key has been pressed*/); //!< Animations of the leg and arm movements
	void setSpeed(float s); //!< Sets the speed of the animation 
	void setAnimationAngle(float a); //!< Sets the angle of arm and leg animation
	float getSpeed(); //!< Gets the speed of the animation
	float getAnimationAngle(); //!< Gets the angle of arm and leg animation
	void setVariableWalkAngle(float a); //!< Sets the angle of rotating the robot with key press
	float getVariableWalkAngle(); //!< Gets the angle of rotating the robot with key press
	void changeDirection(char c); //!< Changes the direction of the robot
};