/*!
* @file main.cpp
\brief The entry for the program
*/

#include "Window.h"

int main(int argc, char *argv[])
{
	//The window wrapper class
	Window* m_mainWindow;
	m_mainWindow = new Window();

	//Window initialization
	m_mainWindow->initWindow();
	
	//Enter the main loop for the program
	m_mainWindow->mainLoop();
}

