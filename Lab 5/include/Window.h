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

#define MOVE_VELOCITY 0.01f
#define ROTATE_VELOCITY 0.00001f

/*! \class Window.h
\brief The control the creating of the program window
*/


class Window: public Entity
{
	private:
		GLFWwindow* m_window; //!< The GLFW Window
		double lastCursorPositionX; //!< The last x cursor position
		double lastCursorPositionY; //!< The last y cursor position
		double cursorPositionX; //!< The x cursor position
		double cursorPositionY; //!< The y cursor position		
		QuatCamera* m_camera; //!< The camera
		GameLogic* m_scene; //!< The scene
		
	public:
		Window(); //!< Default constructor
		void initWindow(); //!< Initialize the window
		GLFWwindow* getWindow(); //!< Obtain the window
		static void key_callback(GLFWwindow* window, int key, int cancode, int action, int mods); //!< Keyboard callback 
		static void scroll_callback(GLFWwindow *window, double x, double y); //!< Scroll mouse callback
		void keyPress(int key, int action, int mods, int cancode); //!< Keyboard key press user control
		void scrollPress(double x, double y); //!< Scroll mouse user control
		void resizeGL(int w, int h); //!< Resizes the camera based on the size of window
		void mainLoop(); //!< Main loop of the program
		void terminate(); //!< Termination of the program

		//!< Update the camera controls (virtual function)
		void update(float t)
		{
			//Get the current cursor position
			glfwGetCursorPos(m_window, &cursorPositionX, &cursorPositionY);

			//See how much the cursor has moved
			float deltaX = (float)(lastCursorPositionX - cursorPositionX);
			float deltaY = (float)(lastCursorPositionY - cursorPositionY);

			//Need to disable the camera features when in the splash screen state
			if (m_scene->getGameState() == 1)
			{
				//Using a different way (i.e. instead of callback) to check for LEFT mouse button
				if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT))
				{
					//std::cout << "Left button \n";
					//Rotate the camera. The 0.001f is a velocity mofifier to make the speed sensible

					//	std::cout <<"deltaX " << deltaX << " deltaY " << deltaY << "\n";

					m_camera->rotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY);

				}

				//Using a different way (i.e. instead of callback) to check for RIGHT mouse button
				if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT))
				{
					//std::cout << "Right button \n";
					//Rotate the camera. The 0.01f is a velocity mofifier to make the speed sensible
					m_camera->pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY);

				}
				//To adjust Roll with MIDDLE mouse button
				if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE))
				{
					m_camera->roll(deltaX*ROTATE_VELOCITY);

				}

				//Scroll callback
				glfwSetScrollCallback(m_window, scroll_callback);//Set callback

																 //Store the current cursor position
				lastCursorPositionX = cursorPositionX;
				lastCursorPositionY = cursorPositionY;
				m_scene->update((float)glfwGetTime(), *m_camera);
			}
		} 
};
