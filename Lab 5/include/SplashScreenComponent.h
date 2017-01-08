#pragma once
/*!
* @file SplashScreenComponent.h
* Header file containing the splashScreen data
*/
#include "MeshComponent.h"

/*! \class SplashScreenComponent
\brief  The controller class which displays the splash screen
*/

//!< Inherits from Mesh as the splash screen is a 2d rectangle 
class SplashScreenComponent : public MeshComponent {

	public:
		SplashScreenComponent(); //!< Default Constructor 
		SplashScreenComponent(GLuint programID); //!<  Constructor 

};