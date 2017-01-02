#pragma once
/*!
* @file splashScreen.h
* Header file containing the splashScreen data
*/
#include "Mesh.h"

/*! \class splashScreen
\brief  The controller class which displays the splash screen
*/

//!< Inherits from Mesh as the splash screen is a 2d rectangle 
class SplashScreen: public Mesh  {

	public:
		SplashScreen(); //!< Default Constructor 
		SplashScreen(GLuint programID); //!<  Constructor 

};