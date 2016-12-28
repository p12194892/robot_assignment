/*!
* @file Robot.cpp
*/
#include "Robot.h"
#include <glm/gtx/transform.hpp>

//!< Constructor 
Robot::Robot(GLuint programID)
{
	//Angles of arms and legs
	m_fArmAngles[LEFT] = 0.0;
	m_fArmAngles[RIGHT] = 0.0;
	m_fLegAngles[LEFT] = 0.0;
	m_fLegAngles[RIGHT] = 0.0;

	//States
	m_cArmStates[LEFT] = FORWARD_STATE;
	m_cArmStates[RIGHT] = BACKWARD_STATE;

	m_cLegStates[LEFT] = FORWARD_STATE;
	m_cLegStates[RIGHT] = BACKWARD_STATE;

	//Creating the cube objects to form the robot

	//m_LeftFoot
	m_LeftFoot = new cube(programID);	

	//right foot
	m_RightFoot = new cube(programID);	

	//m_Head
	m_Head = new cube(programID);

	//m_Torso
	m_Torso = new cube(programID);
		
	//Left Arm
	m_LeftArm = new cube(programID);

	//Right Arm
	m_RightArm = new cube(programID);

	//m_LeftLeg
	m_LeftLeg = new cube(programID);

	//right leg
	m_RightLeg = new cube(programID);
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
void Robot::DrawRobot(QuatCamera c/*!The camera*/, GLuint programID/*!The main program handle*/)
{
	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 2);
	//m_Head
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::scale(glm::vec3(1.0, 1.0, 1.0)) * glm::translate(glm::vec3(0.0, -2.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_Head->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 0);
	//m_Torso
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::scale(glm::vec3(2.0, 3.0, 1.0)) * glm::translate(glm::vec3(0.0, -2.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_Torso->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 3);

	//Left Arm
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::rotate(m_fArmAngles[LEFT], glm::vec3(1.0,0.0,0.0)) * glm::scale(glm::vec3(0.5, 2.0, 0.5)) * glm::translate(glm::vec3(-5.0, -3.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_LeftArm->Draw();

	//Right Arm
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::rotate(m_fArmAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.5, 2.0, 0.5)) * glm::translate(glm::vec3(5.0, -3.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_RightArm->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 1);

	//right Leg
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::rotate(m_fLegAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 3.0, 0.5)) * glm::translate(glm::vec3(1.5, -4.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_RightLeg->Draw();


	//left Leg
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::rotate(m_fLegAngles[LEFT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 3.0, 0.5)) * glm::translate(glm::vec3(-1.5, -4.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_LeftLeg->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 2);

	//Left foot
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::rotate(m_fLegAngles[LEFT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8,0.5, 1.2)) * glm::translate(glm::vec3(-1.5, -31.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_LeftFoot->Draw();
	
	//Right foot
	m_ModelMatrix = glm::translate(m_initPos);
	m_ModelMatrix *= glm::rotate(m_fvariableAngle, glm::vec3(0.0, 1.0, 0.0));
	m_ModelMatrix *= glm::rotate(m_fLegAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 0.5, 1.2)) * glm::translate(glm::vec3(1.5, -31.0, 0.0));
	UpdateModelMatrix(c, programID);
	m_RightFoot->Draw();

}

//!< Updates the model matrix based on translation, scale and rotation
void Robot::UpdateModelMatrix(QuatCamera camera/*!The camera*/, GLuint programID/*!The main program handle*/)
{

 MVP = camera.projection() * (camera.view() * m_ModelMatrix);
	gl::UniformMatrix4fv(gl::GetUniformLocation(programID, "MVP"), 1, gl::FALSE_, &MVP[0][0]);
}

//!< Animations of the leg and arm movements
void Robot::Prepare(float seconds/*!seconds of time*/, bool b/*if the key has been pressed*/)
{
	if (b == true)
	{
		for (char side = 0; side < 2; side++)
		{
			//0.01 to walk speed
			//0.1 angle for walk
		
			// arms
			if (m_cArmStates[side] == FORWARD_STATE)
				m_fArmAngles[side] += (float)m_fSpeed;
			else
				m_fArmAngles[side] -= (float)m_fSpeed;

			// change state if exceeding angles
			if (m_fArmAngles[side] >= m_fAngle)
				m_cArmStates[side] = BACKWARD_STATE;
			else if (m_fArmAngles[side] <= -m_fAngle)
				m_cArmStates[side] = FORWARD_STATE;

			// legs
			if (m_cLegStates[side] == FORWARD_STATE)
				m_fLegAngles[side] += m_fSpeed;
			else
				m_fLegAngles[side] -= m_fSpeed;
			//legs
		//	 change state if exceeding angles
			if (m_fLegAngles[side] >= m_fAngle)
				m_cLegStates[side] = BACKWARD_STATE;
			else if (m_fLegAngles[side] <= -m_fAngle)
				m_cLegStates[side] = FORWARD_STATE;
		}
	}

}

void Robot::setSpeed(float s)
{
	m_fSpeed = s;
}

void Robot::setAngle(float a)
{
	m_fAngle = a;
}

float Robot::getSpeed()
{
	return m_fSpeed;
}

float Robot::getAngle()
{
	return m_fAngle;
}

void Robot::setInitPos(glm::vec3 s)
{
	m_initPos = s;
}

void Robot::setVariableWalkAngle(float f)
{
	m_fvariableAngle = f;
}

glm::vec3 Robot::getInitPos()
{
	return m_initPos;
}

float Robot::getVariableWalkAngle()
{
	return m_fvariableAngle;
}

void Robot::changeDirection(char c)
{
	switch (c)
	{
		case 'U':
			m_initPos.x += -sin(m_fvariableAngle) * 0.3f;
			m_initPos.z += -cos(m_fvariableAngle) * 0.3f;
			break;

		case 'W':
			m_initPos.x -= -sin(m_fvariableAngle) * 0.3f;
			m_initPos.z -= -cos(m_fvariableAngle) * 0.3f;
			break;

		case 'D':
			m_fvariableAngle -= 0.1f;
			break;

		case 'S':
			m_fvariableAngle += 0.1f;
			break;
	}

}


