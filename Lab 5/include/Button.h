#pragma once
/*!
* @file Button.h
* Header file containing the button data
*/

#include "SFML\Graphics.hpp"
#include "UIComponent.h"

/*! \class Button
\brief  A button object which the user can click on to transition to the next state
*/

class Button: public UIComponent
{
	public:
		Button();
		Button(GLuint programID);
		void update()
		{
			//update by seeing if there is a click in the bounds!
		}
	
};


