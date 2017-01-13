/*!
* @file Robot.cpp
*/
#include "Robot.h"
#include <glm/gtx/transform.hpp>

//!< Constructor 
Robot::Robot(GLuint programID)
{
	//Angles of arms and legs
	m_farmAngles[LEFT] = 0.0;
	m_farmAngles[RIGHT] = 0.0;
	m_flegAngles[LEFT] = 0.0;
	m_flegAngles[RIGHT] = 0.0;

	//States
	m_carmStates[LEFT] = FORWARD_STATE;
	m_carmStates[RIGHT] = BACKWARD_STATE;

	m_clegStates[LEFT] = FORWARD_STATE;
	m_clegStates[RIGHT] = BACKWARD_STATE;

	//Creating the cube objects to form the robot
	//Setting texture units
	//m_LeftFoot
	m_leftFoot = new Cube(programID);	

	//right foot
	m_rightFoot = new Cube(programID);	

	//m_Head
	m_head = new Cube(programID);

	//m_Torso
	m_torso = new Cube(programID);
		
	//Left Arm
	m_leftArm = new Cube(programID);

	//Right Arm
	m_rightArm = new Cube(programID);

	//m_LeftLeg
	m_leftLeg = new Cube(programID);

	//right leg
	m_rightLeg = new Cube(programID);
}

//!< Default constructor
Robot::Robot()
{

}

//!< Destructor 
Robot::~Robot()
{
}

//!< Draws the robot to the screen, taking it's starting position, the angle of rotation, the camera to update the model matrix and the main program handle
void Robot::drawRobot(CameraComponent c/*!The camera*/, GLuint programID/*!The main program handle*/)
{
	//head
	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 2);
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::scale(glm::vec3(1.0, 1.0, 1.0)) * glm::translate(glm::vec3(0.0, -2.0, 0.0));
	updateModelMatrix(c, programID);
	m_head->draw();

	//m_Torso
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::scale(glm::vec3(2.0, 3.0, 1.0)) * glm::translate(glm::vec3(0.0, -2.0, 0.0));
	updateModelMatrix(c, programID);
	m_torso->draw();

	//Left Arm
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::rotate(m_farmAngles[LEFT], glm::vec3(1.0,0.0,0.0)) * glm::scale(glm::vec3(0.5, 2.0, 0.5)) * glm::translate(glm::vec3(-5.0, -3.0, 0.0));
	updateModelMatrix(c, programID);
	m_leftArm->draw();

	//Right Arm
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::rotate(m_farmAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.5, 2.0, 0.5)) * glm::translate(glm::vec3(5.0, -3.0, 0.0));
	updateModelMatrix(c, programID);
	m_rightArm->draw();

	//right Leg
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::rotate(m_flegAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 3.0, 0.5)) * glm::translate(glm::vec3(1.5, -4.0, 0.0));
	updateModelMatrix(c, programID);
	m_rightLeg->draw();

	//left Leg
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::rotate(m_flegAngles[LEFT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 3.0, 0.5)) * glm::translate(glm::vec3(-1.5, -4.0, 0.0));
	updateModelMatrix(c, programID);
	m_leftLeg->draw();

	//Left foot
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::rotate(m_flegAngles[LEFT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8,0.5, 1.2)) * glm::translate(glm::vec3(-1.5, -31.0, 0.0));
	updateModelMatrix(c, programID);
	m_leftFoot->draw();
	
	//Right foot
	m_modelMatrix = glm::translate(m_startPosition);
	m_modelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_modelMatrix *= glm::rotate(m_flegAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 0.5, 1.2)) * glm::translate(glm::vec3(1.5, -31.0, 0.0));
	updateModelMatrix(c, programID);
	m_rightFoot->draw();

}

//!< Animations of the leg and arm movements
void Robot::prepare(float seconds/*!seconds of time*/, bool b/*if the key has been pressed*/)
{
	if (b == true)
	{
		for (char side = 0; side < 2; side++)
		{
			//0.01 to walk speed
			//0.1 angle for walk
		
			// arms
			if (m_carmStates[side] == FORWARD_STATE)
				m_farmAngles[side] += (float)m_fspeed;
			else
				m_farmAngles[side] -= (float)m_fspeed;

			// change state if exceeding angles
			if (m_farmAngles[side] >= m_fanimationAngle)
				m_carmStates[side] = BACKWARD_STATE;
			else if (m_farmAngles[side] <= -m_fanimationAngle)
				m_carmStates[side] = FORWARD_STATE;

			// legs
			if (m_clegStates[side] == FORWARD_STATE)
				m_flegAngles[side] += m_fspeed;
			else
				m_flegAngles[side] -= m_fspeed;
			//legs
		//	 change state if exceeding angles
			if (m_flegAngles[side] >= m_fanimationAngle)
				m_clegStates[side] = BACKWARD_STATE;
			else if (m_flegAngles[side] <= -m_fanimationAngle)
				m_clegStates[side] = FORWARD_STATE;
		}
	}

}

//!< Sets the speed of the animation 
void Robot::setSpeed(float s)
{
	m_fspeed = s;
}

//!< Sets the angle of arm and leg animation
void Robot::setAnimationAngle(float a)
{
	m_fanimationAngle = a;
}

//!< Gets the speed of the animation
float Robot::getSpeed()
{
	return m_fspeed;
}

//!< Gets the angle of arm and leg animation
float Robot::getAnimationAngle()
{
	return m_fanimationAngle;
}

//!< Sets the angle of rotating the robot with key press
void Robot::setVariableWalkAngle(float f)
{
	m_fvariableAngle = f;
}

//!< Gets the angle of rotating the robot with key press
float Robot::getVariableWalkAngle()
{
	return m_fvariableAngle;
}

//!< Changes the direction of the robot
void Robot::changeDirection(char c)
{
	switch (c)
	{
		case 'U':
			m_startPosition.x += -sin(m_fvariableAngle) * 0.3f;
			m_startPosition.z += -cos(m_fvariableAngle) * 0.3f;
			break;

		case 'W':
			m_startPosition.x -= -sin(m_fvariableAngle) * 0.3f;
			m_startPosition.z -= -cos(m_fvariableAngle) * 0.3f;
			break;

		case 'D':
			m_fvariableAngle -= 0.1f;
			break;

		case 'S':
			m_fvariableAngle += 0.1f;
			break;
	}

}


