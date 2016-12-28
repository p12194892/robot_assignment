#pragma once
/*!
* @file Button.h
* Header file containing the button data
*/

#include "Mesh.h"

/*! \class Button
\brief  A button object which the user can click on to transition to the next state
*/

class Button : public Mesh {

	private:
		GLuint m_programID;
	public:
		Button(); 
		Button(GLuint m_programID);
		~Button();

};


