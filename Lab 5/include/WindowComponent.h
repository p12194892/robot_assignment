#pragma once
/*!
* @file Window.h
* Header file window creation through SFML
*/
#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include <string>
#include "Entity.h"
#include "CameraComponent.h"
#include "BaseGame.h"
#include "SFML\Window.hpp"
#include <vector>
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
		bool m_bifRunning; //!< Define if the window is running
		std::vector<CameraComponent*> m_Cameras;//!< The multiple cameras
		int m_cameraChangeState; //!< Changes the active camera
		BaseGame* m_baseGame; //!< The scene
		
	public:
		WindowComponent(); //!< Default constructor
		~WindowComponent(); //!< Destructor
		void mainLoop(XMLReader* s); //!< Main loop of the program
		void sfEventPoll(); //!< new SFML functions
		bool isRunning(); //! If the window is running 
		void setRunning(bool run); //!< Sets if the window is running
		sf::RenderWindow* getRenderWindow(); //!< Gets the render window

		//!< Update the camera controls (virtual function)
		void update(float t)
		{

			//Current mouse position
			m_cursorPositionX = sf::Mouse::getPosition().x;
			m_cursorPositionY = sf::Mouse::getPosition().y;

			//See how much the cursor has moved
			float deltaX = (float)(m_lastCursorPositionX - m_cursorPositionX);
			float deltaY = (float)(m_lastCursorPositionY - m_cursorPositionY);

			if (m_ckeyPress == 'L') { m_Cameras.at(m_cameraChangeState)->rotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY); }

			else if (m_ckeyPress == 'R') { m_Cameras.at(m_cameraChangeState)->pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY); }

			else if (m_ckeyPress == 'M') { m_Cameras.at(m_cameraChangeState)->roll(deltaX*ROTATE_VELOCITY); }

			//Store the current cursor position
			m_lastCursorPositionX = m_cursorPositionX;
			m_lastCursorPositionY = m_cursorPositionY;

			//Update the scene
			m_baseGame->update((float)glfwGetTime());
		}
		

		//!< Initialize the window
		void init(XMLReader* s)
		{
			//From here we could then use the XML parser to parse data using the overload virtual function
			s->readWindowAttributes("resources/shader/data.xml");

			//Cameras pushed back onto vector
			m_Cameras.push_back(new CameraComponent(0));
			m_Cameras.push_back(new CameraComponent(1));
			m_Cameras.push_back(new CameraComponent(2));

			//Sets the camera to the first camera
			m_cameraChangeState = 0;

			m_lastCursorPositionX = 0.0;
			m_lastCursorPositionY = 0.0;
			m_cursorPositionX = 0.0;
			m_cursorPositionY = 0.0;

			//Creates the scene
			m_baseGame = new BaseGame();
			
			//SFML window
			m_window = new sf::RenderWindow(sf::VideoMode(std::stoi(s->getData().at(1)), std::stoi(s->getData().at(2))), s->getData().at(0), sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(24));
			m_window->setVerticalSyncEnabled(true);
			m_window->setFramerateLimit(60);
			std::cout << "Window Loaded" << std::endl << std::endl;
			m_bifRunning = false;
		
			// Load the OpenGL functions.
			gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

			if (!didLoad) {
				//Clean up and abort
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
		
			//Enabling depth depth test 
			gl::Enable(gl::DEPTH_TEST);
			
			//Init the base game
			m_baseGame->init();			
		}
};
