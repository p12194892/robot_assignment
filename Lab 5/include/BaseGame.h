/*!
* @file BaseGame.h
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
#include "Button.h"
#include "UIComponent.h"
#include <vector>
#include "CollisionComponent.h"
#include "SoundComponent.h"
#include "Entity.h"
#include "MeshComponent.h"
#include "ShaderLinkerComponent.h"
#include "LightingComponent.h"
#include <iostream>

/*! \class BaseGame
\brief The base game that renders the scene and updates the game objects
*/

//!< Inherits from scene
class BaseGame : public Entity
{
private:
	Robot* m_robot; //!< The robot mesh	
	std::vector<MeshComponent*> m_objects;//! List of game objects
	MeshComponent* m_room; //!< The room 
	MeshComponent* m_rubix; //!< The rubix object
	MeshComponent* m_box; //!< The Box Object
	MeshComponent* m_box2; //!< The Box Object
	MeshComponent* m_cone; //!< The Cone Object
	MeshComponent* m_sphere; //!< A sphere object
	MeshComponent* m_cylinder; //!< The Cone Object
	MeshComponent* m_cylinder2; //!< The Cone Object
	MeshComponent* m_torus; //!< Torus Object
	MeshComponent* m_torus2; //!< Torus Object
	MeshComponent* m_sphere2; //!< A sphere object
	MeshComponent* m_star; //!< The star object
	MeshComponent* m_star2; //!< The star object
	MeshComponent* m_star3; //!< The star object
	MeshComponent* m_star4; //!< The star object
	UIComponent* m_splashScreenComponent; //!< Splash Screen
	UIComponent* m_menuScreenComponent; //!< Menu
	UIComponent* m_instructionsComponent; //!< Instructions Screen
	Button* m_buttonStart; //!< Start Button
	Button* m_buttonExit; //!< Exit Button
	Button* m_buttonInstruction; //!< Instruction Button
	Button* m_backButton; //!< Back Button
	SoundComponent* m_soundComponent;  //!< Sound loader object
	CollisionComponent* m_collision; //!< Collision detection 
	GLuint m_programHandle; //!< The main program handle
	bool m_bKeyPress; //!< If a key has been pressed
	FileReader* m_read; //!< File Reader, reads in obj files
	char m_cGameState; //!< Game State
	ShaderLinkerComponent* m_menuShader; //!< GUI shaders 
	ShaderLinkerComponent* m_lightingShader; //!< Runs the simulation with lighting
	LightingComponent* m_generalLight;//!< Spot Light
	float m_frotate; //!< Animating star

public:
	BaseGame(); //!< Default constructor	
	void render(CameraComponent& camera); //!< Render mesh objects
 	void keyPress(bool b, char c); //!< Detects when a key is press
	char getGameState(); //!< Obtains the current game state
	void changeGameState(int i); //!< Changes the game state
	void createObjects(); //!< Creates objects to be used in the simulation

	//Virtual functions inherited
	//!< Update the scene with animations
	void update(float t)
	{
		switch (m_cGameState)
		{
		case 0:
			break;
		case 1:
			break;
		
		case 2:
			float fTime = t / float(1000); //! Divide milliseconds to 1000 to obtain one second.

			//Update the robot movement
			m_robot->prepare(fTime, m_bKeyPress);

			if (m_objects.size() != 0)
			{
				//Animate stars	 	
				if (m_frotate >= 0)
				{
					if (m_frotate >= 6.28319)
					{
						m_frotate = 0;
					}
					m_frotate += 0.5f;
				}

				m_star4->rotateModelMat(m_frotate, glm::vec3(0.0, 1.0, 0.0));
				m_star2->rotateModelMat(m_frotate, glm::vec3(0.0, 1.0, 0.0));
				m_star3->rotateModelMat(m_frotate, glm::vec3(0.0, 1.0, 0.0));
				m_star->rotateModelMat(m_frotate, glm::vec3(0.0, 1.0, 0.0));
				m_cylinder->rotateModelMat(m_frotate, glm::vec3(0.0, 1.0, 0.0));
				m_cylinder2->rotateModelMat(m_frotate, glm::vec3(0.0, 1.0, 0.0));
				m_sphere->rotateModelMat(m_frotate, glm::vec3(1.0, 1.0, 0.0));
				m_sphere2->rotateModelMat(m_frotate, glm::vec3(1.0, 0.0, 1.0));
			}

			if (m_objects.size() == 0)
			{
				std::cout << "All Objects Picked Up :) " << std::endl;
			}

			else
			{
				//Collision Detection between objects and robot
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
			}
			break;
		}
	}

	//!< Initialise the scene 
	void init()
	{
		//Initialize Game States
		m_cGameState = 0; //Game state, 0 = Splash Screen, 1 = Menu Screen, 2 = Simulation Screen

		//Initialize Key Press
		m_bKeyPress = false;

		//Initialize the vertex and fragment shader
		m_menuShader = new ShaderLinkerComponent("resources/shader/basic.vert","resources/shader/basic.frag");
		m_lightingShader = new ShaderLinkerComponent("resources/shader/lighting.vert", "resources/shader/lighting.frag");

		//Initalize lighting in the scene
		m_generalLight = new LightingComponent();
		
		//Obtains the program handle
		m_programHandle = m_menuShader->getProgramHandle();

		//Initialize File Reader
		m_read = new FileReader();

		//Initialize game objects
		createObjects();

		//Initialize Collision Detection
		m_collision = new CollisionComponent();

		//Animation 
		m_frotate = 0;

		//Initialize Game Sounds
		m_soundComponent = m_soundComponent->Instance();
		m_soundComponent->GetSound(1)->play();
		m_soundComponent->GetSound(1)->setLoop(true);
	}
};
 