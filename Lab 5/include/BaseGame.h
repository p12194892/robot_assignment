/*!
* @file GameLogic.h
* Header file control of rendering and controlling the simulation 
*/

#pragma once
#include "Texture.h"
#include <vector>
#include <glm\glm.hpp>
#include "cube.h"
#include "gl_core_4_3.hpp"
#include "Robot.h"
#include "FileReader.h"
#include "glslprogram.h"
#include "Button.h"
#include "SplashScreenComponent.h"
#include <vector>
#include "CollisionComponent.h"
#include "SoundComponent.h"
#include "Entity.h"
#include "MeshComponent.h"
#include "ShaderLinkerComponent.h"
#include <iostream>
/*! \class GameLogicComponent
\brief The control of rendering and controlling the simulation  
*/

//!< Inherits from scene
class BaseGame : public Entity
{
private:
	//Game objects that make the scene
	MeshComponent* m_room; //!< The room 
	Robot* m_robot; //!< The robot mesh	
	std::vector<MeshComponent*> m_objects;
	MeshComponent* m_box2; //!< The Box Object
	MeshComponent* m_box; //!< The Box Object
	MeshComponent* m_man; //!< The Man Object
	MeshComponent* m_garlicpress; //!< The Garlic Press Object
	MeshComponent* m_mouse; //!< The Mickey Mouse Object
	MeshComponent* m_cone; //!< The Cone Object
	MeshComponent* m_character; //!< BB8 Object
	SoundComponent* m_soundComponent;  //!< Sound loader object
	CollisionComponent* m_collision; //!< Collision detection 
	GLuint m_programHandle; //!< The main program handle
	bool m_bKeyPress; //!< If a key has been pressed
	GLSLProgram prog; //!< Program to run the simulation
	FileReader* m_read; //!< File Reader
	SplashScreenComponent* m_splashScreenComponent;	//!< Splash Screen
	char m_cGameState; //!< Game State
	ShaderLinkerComponent* m_linkShader;
	
public:
	BaseGame(); //!< Default constructor	
	void render(CameraComponent camera); //!< Render mesh objects
 	void keyPress(bool b, char c); //!< Detects when a key is press
	char getGameState(); //!< Obtains the current game state
	void changeGameState(int i); //!< Changes the game state
	void createObjects(); //!< Creates objects to be used in the simulation

	//!< Update the scene with animations
	void update(float t)
	{
		switch (m_cGameState)
		{
		case 0:
			//Any code for getting the splash screen button
			break;

		case 1:
			float fTime = t / float(1000); //! Divide milliseconds to 1000 to obtain one second.

			m_robot->prepare(fTime, m_bKeyPress);

			//Collision Detection
			m_objects = m_collision->checkVectorDistance(m_objects, m_robot->getStartPos());

			for (int i = 0; i < m_objects.size(); i++)
			{
				if (!m_objects.at(i)->isDrawable())
				{
					//pop it off the list and play a sound
					std::cout << std::endl << "Picked up object: " << m_objects.at(i)->getID() << std::endl << std::endl;
					m_objects.erase(m_objects.begin() + i);					
					m_soundComponent->GetSound(0)->play();
				}
			}
			break;
		}
	}

	//!< Initialise the scene 
	void init()
	{
		//Initialize Game States
		m_cGameState = 0; //Game state, 0 = Splash Screen

		//Initialize Key Press
		m_bKeyPress = false;

		//Initialize the vertex and fragment shader
		m_linkShader = new ShaderLinkerComponent();
		m_linkShader->createShaders();

		//Obtains the program handle
		m_programHandle = m_linkShader->getProgramHandle();

		//Initialize File Reader
		m_read = new FileReader();

		//Initialize game objects
		createObjects();

		//Initialize Collision Detection
		m_collision = new CollisionComponent();

		//Initialize Game Sounds
		m_soundComponent = m_soundComponent->Instance();

		//Reading in XML???
		//XMLDocument doc
	}



 //void setLightParams(QuatCamera camera);
 //void compileAndLinkShader();
};
 