#pragma once
/*!
* @file splashScreen.h
* Header file containing the splashScreen data
*/
#include "Mesh.h"

/*! \class splashScreen
\brief  The controller class which displays the splash screen
*/

class SplashScreen: public Mesh  {

	private:
		GLuint m_programID;

	public:
		SplashScreen();
		SplashScreen(GLuint programID);

};