#pragma once
/*!
* @file Window.h
* Header file window creation through GLFW
*/
#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include <windows.h>
#include <string>
#include "Entity.h"
#include <iostream>
#include "QuatCamera.h"
#include "GameLogic.h"
#include "SFML\Window.hpp"

//New stuff
#include "splashScreen.h"
#include "SFML/Graphics.hpp"

#define MOVE_VELOCITY 0.01f
#define ROTATE_VELOCITY 0.00001f

/*! \class Window.h
\brief The control the creating of the program window
*/


class Window: public Entity
{
	private:
		double lastCursorPositionX; //!< The last x cursor position
		double lastCursorPositionY; //!< The last y cursor position
		double cursorPositionX; //!< The x cursor position
		double cursorPositionY; //!< The y cursor position		
		QuatCamera m_camera; //!< The camera
		GameLogic* m_scene; //!< The scene
		sf::RenderWindow* m_window; //!< The window
		sf::Event m_event; //!< The event
		bool m_bifRunning; //!< If the main loop is running
		char m_ckeyPress; //!< Key that shows what mouse button has been pressed 
		
	public:
		Window(); //!< Default constructor
		void initWindow(); //!< Initialize the window
		void resizeGL(int w, int h); //!< Resizes the camera based on the size of window
		void mainLoop(); //!< Main loop of the program
		void sfEventPoll(); //!< new SFML functions
		

		//!< Update the camera controls (virtual function)
		void update(float t)
		{
			//Current mouse position
			cursorPositionX = sf::Mouse::getPosition().x;
			cursorPositionY = sf::Mouse::getPosition().y;

			//See how much the cursor has moved
			float deltaX = (float)(lastCursorPositionX - cursorPositionX);
			float deltaY = (float)(lastCursorPositionY - cursorPositionY);

			if (m_ckeyPress == 'L') { m_camera.rotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY); }

			else if (m_ckeyPress == 'R') {m_camera.pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY);}

			else if (m_ckeyPress == 'M') { m_camera.roll(deltaX*ROTATE_VELOCITY); }

			//Store the current cursor position
			lastCursorPositionX = cursorPositionX;
			lastCursorPositionY = cursorPositionY;

			//Update the scene
			m_scene->update((float)glfwGetTime(), m_camera);
		}		
};
