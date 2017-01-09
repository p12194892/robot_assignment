#pragma once
/*!
* @file UIComponent.h
* Header file containing the splashScreen data
*/
#include "MeshComponent.h"

/*! \class UIComponent
\brief  The controller class which displays the splash screen
*/

//!< Inherits from Mesh as the splash screen is a 2d rectangle 
class UIComponent : public MeshComponent {

	public:
		UIComponent(); //!< Default Constructor 
		UIComponent(GLuint programID); //!<  Constructor 

};