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
#include "CameraComponent.h"
#include "BaseGame.h"
#include "SFML\Window.hpp"

//New stuff
#include "UIComponent.h"
#include "SFML/Graphics.hpp"

#define MOVE_VELOCITY 0.01f
#define ROTATE_VELOCITY 0.00001f

/*! \class Window.h
\brief The control the creating of the program window
*/


class WindowComponent: public Entity
{
	private:
		double m_lastCursorPositionX; //!< The last x cursor position
		double m_lastCursorPositionY; //!< The last y cursor position
		double m_cursorPositionX; //!< The x cursor position
		double m_cursorPositionY; //!< The y cursor position		
		sf::RenderWindow* m_window; //!< The window
		sf::Event m_event; //!< The event
		char m_ckeyPress; //!< Key that shows what mouse button has been pressed 
		bool m_bifRunning;
		CameraComponent m_camera; //!< The camera
		BaseGame* m_baseGame; //!< The scene
	
		public:
		WindowComponent(); //!< Default constructor
		~WindowComponent(); //!< Destructor
		void mainLoop(); //!< Main loop of the program
		void sfEventPoll(); //!< new SFML functions
		bool isRunning();
		void setRunning(bool run);

		//!< Update the camera controls (virtual function)
		void update(float t)
		{
			
				//Current mouse position
				m_cursorPositionX = sf::Mouse::getPosition().x;
				m_cursorPositionY = sf::Mouse::getPosition().y;

				//See how much the cursor has moved
				float deltaX = (float)(m_lastCursorPositionX - m_cursorPositionX);
				float deltaY = (float)(m_lastCursorPositionY - m_cursorPositionY);

				if (m_ckeyPress == 'L') { m_camera.rotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY); }

				else if (m_ckeyPress == 'R') { m_camera.pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY); }

				else if (m_ckeyPress == 'M') { m_camera.roll(deltaX*ROTATE_VELOCITY); }

				//Store the current cursor position
				m_lastCursorPositionX = m_cursorPositionX;
				m_lastCursorPositionY = m_cursorPositionY;

				//Update the scene
				m_baseGame->update((float)glfwGetTime());
		}		

		void init() //!< Initialize the window
		{
			// Load the OpenGL functions.
			gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

			if (!didLoad) {
				//Claen up and abort
				glfwTerminate();
				exit(EXIT_FAILURE);
			}

			gl::Enable(gl::DEPTH_TEST);
			gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

			m_baseGame->init();
		}
};
