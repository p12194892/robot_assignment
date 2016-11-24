#ifdef _WINDOWS
#include <windows.h>
#endif



#include "Robot.h"
#include <glm/gtx/transform.hpp>
Robot::Robot(GLuint programID)
{
	//Angles of arms and legs
	armAngles[LEFT] = 0.0;
	armAngles[RIGHT] = 0.0;
	legAngles[LEFT] = 0.0;
	legAngles[RIGHT] = 0.0;

	//States
	armStates[LEFT] = FORWARD_STATE;
	armStates[RIGHT] = BACKWARD_STATE;

	legStates[LEFT] = FORWARD_STATE;
	legStates[RIGHT] = BACKWARD_STATE;

	
	//leftfoot
	leftFoot = new cube(programID);	

	//right foot
	rightFoot = new cube(programID);	

	//head
	head = new cube(programID);

	//torso
	torso = new cube(programID);
		
	//Left Arm
	leftArm = new cube(programID);

	//Right Arm
	rightArm = new cube(programID);

	//leftleg
	leftLeg = new cube(programID);

	//right leg
	rightLeg = new cube(programID);
}
Robot::Robot()
{

}
Robot::~Robot()
{
}

void Robot::DrawRobot(QuatCamera c, GLuint programID, glm::vec3 startPos, float angle)
{
	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 2);
	//Head
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::scale(glm::vec3(1.0, 1.0, 1.0)) * glm::translate(glm::vec3(-2.0, -2.0, 0.0));
	setMatrices(c, programID);
	head->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 0);
	//Torso
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::scale(glm::vec3(2.0, 3.0, 1.0)) * glm::translate(glm::vec3(-1.0, -2.0, 0.0));
	setMatrices(c, programID);
	torso->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 3);

	//Left Arm
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::rotate(armAngles[LEFT], glm::vec3(1.0,0.0,0.0)) * glm::scale(glm::vec3(0.5, 2.0, 0.5)) * glm::translate(glm::vec3(-9.0, -3.0, 0.0));
	setMatrices(c, programID);
	leftArm->Draw();

	//Right Arm
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::rotate(armAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.5, 2.0, 0.5)) * glm::translate(glm::vec3(1.0, -3.0, 0.0));
	setMatrices(c, programID);
	rightArm->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 1);

	//right Leg
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::rotate(legAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 3.0, 0.5)) * glm::translate(glm::vec3(-1.0, -4.0, 0.0));
	setMatrices(c, programID);
	rightLeg->Draw();


	//left Leg
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::rotate(legAngles[LEFT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 3.0, 0.5)) * glm::translate(glm::vec3(-4.0, -4.0, 0.0));
	setMatrices(c, programID);
	leftLeg->Draw();

	gl::Uniform1i(gl::GetUniformLocation(programID, "col"), 2);

	//Left foot
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::rotate(legAngles[LEFT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8,0.5, 1.2)) * glm::translate(glm::vec3(-4.0, -31.0, 0.0));
	setMatrices(c, programID);
	leftFoot->Draw();
	
	//Right foot
	modelMatrix = glm::translate(startPos);
	modelMatrix *= glm::rotate(angle, glm::vec3(0.0, 1.0, 0.0));
	modelMatrix *= glm::rotate(legAngles[RIGHT], glm::vec3(1.0, 0.0, 0.0)) * glm::scale(glm::vec3(0.8, 0.5, 1.2)) * glm::translate(glm::vec3(-1.0, -31.0, 0.0));
	setMatrices(c, programID);
	rightFoot->Draw();

}

void Robot::setMatrices(QuatCamera camera, GLuint programID)
{

	glm::mat4 MVP = camera.projection() * (camera.view() * modelMatrix);
	gl::UniformMatrix4fv(gl::GetUniformLocation(programID, "MVP"), 1, gl::FALSE_, &MVP[0][0]);
}




void Robot::AnimateRobot(bool b, char c)
{

	//VERY BROKEN
	// ISSUES - rotate looks like it distorts vertex points?? didn't do this when I did m_model = glm::rotate(glm::radians(angle), rotate)  * glm::scale(glm::vec3(scale)) * glm::translate(glm::vec3(translate));
	// Translating and rotating doesn't work 

	if (b == true) 
	{

		//Animate the robot to give a "walking effect"					
		if (c == 'D')
		{
		//	rAngle += 0.1f;
		//	rAngle += -sin(rAngle) * 0.3f;
		//	rAngle += -cos(rAngle) * 0.3f;

		//	head->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	torso->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	leftArm->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	rightArm->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	leftLeg->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	rightLeg->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	leftFoot->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));
		//	rightFoot->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));

			//leftLeg->rotate(rAngle, glm::vec3(0.0, 1.0, 0.0));

			//head->transformCube(glm::vec3(translate), glm::vec3(0.125, 0.125, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
		/*	torso->transformCube(glm::vec3(-20.0, -61.8, fStepForwBack), glm::vec3(0.25, 0.4, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
			leftArm->transformCube(glm::vec3(-130.0, -100.0, fStepForwBack), glm::vec3(0.0625, 0.25, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
			rightArm->transformCube(glm::vec3(-30.0, -100.0, fStepForwBack), glm::vec3(0.0625, 0.25, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
			leftLeg->transformCube(glm::vec3(-50.0, -67.5, fStepForwBack), glm::vec3(0.0625, 0.5, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
			rightLeg->transformCube(glm::vec3(-110.0, -67.5, fStepForwBack), glm::vec3(0.0625, 0.5, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
			leftFoot->transformCube(glm::vec3(-110.0, -630.0, fStepForwBack), glm::vec3(0.0625, 0.0625, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);
			rightFoot->transformCube(glm::vec3(-50.0, -630.0, fStepForwBack), glm::vec3(0.0625, 0.0625, 0.125), glm::vec3(0.0, 1.0, 0.0), rAngle);*/


			/*fStepForwBack += 0.1;

			head->transformCube(glm::vec3(-40.0, -155.0, fStepForwBack), glm::vec3(0.125, 0.125, 0.125), glm::vec3(0.0, 1.0, 0.0), 0);
			torso->transformCube(glm::vec3(-20.0, -61.8, fStepForwBack), glm::vec3(0.25, 0.4, 0.125), glm::vec3(0.0, 1.0, 0.0), 0);
			leftArm->transformCube(glm::vec3(-130.0, -100.0,  fStepForwBack), glm::vec3(0.0625, 0.25, 0.125), glm::vec3(1.0, 0.0, 0.0), armAngles[LEFT]);
			rightArm->transformCube(glm::vec3(-30.0, -100.0,fStepForwBack), glm::vec3(0.0625, 0.25, 0.125), glm::vec3(1.0, 0.0, 0.0), armAngles[RIGHT]);
			leftLeg->transformCube(glm::vec3(-50.0, -67.5,  fStepForwBack), glm::vec3(0.0625, 0.5, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[LEFT]);
			rightLeg->transformCube(glm::vec3(-110.0, -67.5, fStepForwBack), glm::vec3(0.0625, 0.5, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[RIGHT]);
			leftFoot->transformCube(glm::vec3(-110.0, -630.0, fStepForwBack), glm::vec3(0.0625, 0.0625, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[RIGHT]);
			rightFoot->transformCube(glm::vec3(-50.0, -630.0,  fStepForwBack), glm::vec3(0.0625, 0.0625, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[LEFT]);*/
		}


		else if (c == 'W')
		{
			//fStepForwBack = -0.1f;
			//translateHead = glm::vec3(0.0, 0.0, fStepForwBack);
			//translateTorso = glm::vec3(0.0, 0.0, fStepForwBack);



			////rotate??????????
			//leftArm->rotate(armAngles[LEFT], glm::vec3(0.0, 0.0, 1.0));
			//rightArm->rotate(armAngles[RIGHT], glm::vec3(0.0, 0.0, 1.0));
			//leftLeg->rotate(legAngles[LEFT], glm::vec3(0.0, 0.0, 1.0));
			//rightLeg->rotate(legAngles[RIGHT], glm::vec3(0.0, 0.0, 1.0));
			//leftFoot->rotate(legAngles[LEFT], glm::vec3(0.0, 0.0, 1.0));
			//rightFoot->rotate(legAngles[RIGHT], glm::vec3(0.0, 0.0, 1.0));


			//head->translate(translateHead);
			//torso->translate(translateTorso);
			//leftArm->translate(translateTorso);
			//rightArm->translate(translateTorso);
			//leftLeg->translate(translateTorso);
			//rightLeg->translate(translateTorso);
			//leftFoot->translate(translateTorso);
			//rightFoot->translate(translateTorso);

		}

		else if (c == 'U')
		{
		
			//fStepForwBack = 0.1f;
			//translateHead = glm::vec3(0.0, 0.0, fStepForwBack);
			//translateTorso = glm::vec3(0.0, 0.0, fStepForwBack);


			////rotate??????????
			//leftArm->rotate(armAngles[LEFT], glm::vec3(0.0, 0.0, 1.0));
			//rightArm->rotate(armAngles[RIGHT], glm::vec3(0.0, 0.0, 1.0));
			//leftLeg->rotate(legAngles[LEFT], glm::vec3(0.0, 0.0, 1.0));
			//rightLeg->rotate(legAngles[RIGHT], glm::vec3(0.0, 0.0, 1.0));
			//leftFoot->rotate(legAngles[LEFT], glm::vec3(0.0, 0.0, 1.0));
			//rightFoot->rotate(legAngles[RIGHT], glm::vec3(0.0, 0.0, 1.0));


			//head->translate(translateHead);
			//torso->translate(translateTorso);
			//leftArm->translate(translateTorso);
			//rightArm->translate(translateTorso);
			//leftLeg->translate(translateTorso);
			//rightLeg->translate(translateTorso);
			//leftFoot->translate(translateTorso);
			//rightFoot->translate(translateTorso);

			//head->transformCube(glm::vec3(-40.0, -155.0,  fStepForwBack), glm::vec3(0.125, 0.125, 0.125), glm::vec3(0.0, 1.0, 0.0), 0);
			//torso->transformCube(glm::vec3(-20.0, -61.8,  fStepForwBack), glm::vec3(0.25, 0.4, 0.125), glm::vec3(0.0, 1.0, 0.0), 0);
			//leftArm->transformCube(glm::vec3(-130.0, -100.0,  fStepForwBack), glm::vec3(0.0625, 0.25, 0.125), glm::vec3(1.0, 0.0, 0.0), armAngles[LEFT]);
			//rightArm->transformCube(glm::vec3(-30.0, -100.0,  fStepForwBack), glm::vec3(0.0625, 0.25, 0.125), glm::vec3(1.0, 0.0, 0.0), armAngles[RIGHT]);
			//leftLeg->transformCube(glm::vec3(-50.0, -67.5, fStepForwBack), glm::vec3(0.0625, 0.5, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[LEFT]);
			//rightLeg->transformCube(glm::vec3(-110.0, -67.5,  fStepForwBack), glm::vec3(0.0625, 0.5, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[RIGHT]);
			//leftFoot->transformCube(glm::vec3(-110.0, -630.0,  fStepForwBack), glm::vec3(0.0625, 0.0625, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[RIGHT]);
			//rightFoot->transformCube(glm::vec3(-50.0, -630.0, fStepForwBack), glm::vec3(0.0625, 0.0625, 0.125), glm::vec3(1.0, 0.0, 0.0), legAngles[LEFT]);
		}

		else if (c == 'L')
		{
			
		}

		else if (c == 'R')
		{


		}
	
	}

}	

void Robot::Prepare(float seconds, bool b)
{
	if (b == true)
	{
		for (char side = 0; side < 2; side++)
		{
			// arms
			if (armStates[side] == FORWARD_STATE)
				armAngles[side] += 0.01;
			else
				armAngles[side] -= 0.01;

			// change state if exceeding angles
			if (armAngles[side] >= 0.1f)
				armStates[side] = BACKWARD_STATE;
			else if (armAngles[side] <= -0.1f)
				armStates[side] = FORWARD_STATE;

			// legs
			if (legStates[side] == FORWARD_STATE)
				legAngles[side] += 0.01f;
			else
				legAngles[side] -= 0.01f;
			//legs
		//	 change state if exceeding angles
			if (legAngles[side] >= 0.1f)
				legStates[side] = BACKWARD_STATE;
			else if (legAngles[side] <= -0.1f)
				legStates[side] = FORWARD_STATE;
		}
	}
}

