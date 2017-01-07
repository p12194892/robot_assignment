#pragma once
/*!
* @file Button.h
* Header file containing the button data
*/

#include "SFML\Graphics.hpp"
#include "Entity.h"

/*! \class Button
\brief  A button object which the user can click on to transition to the next state
*/

class Button: public Entity
{
	private:
		sf::RectangleShape m_buttonShape;
		sf::Text m_buttonText;
	public:
		Button(); 
		Button(float xpos, float ypos, float w, float h);
};


