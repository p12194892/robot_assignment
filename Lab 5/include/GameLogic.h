/*!
* @file GameLogic.h
* Header file control of rendering and controlling the simulation 
*/

#ifndef GameLogic_H
#define GameLogic_H
#include "Texture.h"
#include <vector>
#include <glm\glm.hpp>
#include "scene.h"
#include "cube.h"
#include "gl_core_4_3.hpp"
#include "Robot.h"
#include "FileReader.h"
#include "glslprogram.h"
#include "Button.h"
#include "splashScreen.h"
#include <vector>
#include "Collision.h"
#include "SoundLoader.h"

/*! \class GameLogic
\brief The control of rendering and controlling the simulation  
*/

//!< Inherits from scene
class GameLogic : public Scene
{
private:
	//Game objects that make the scene
	Mesh* m_room; //!< The room 
	Robot* m_robot; //!< The robot mesh	
	std::vector<Mesh*> m_objects;
	Mesh* m_box2; //!< The Box Object
	Mesh* m_box; //!< The Box Object
	Mesh* m_man; //!< The Man Object
	Mesh* m_garlicpress; //!< The Garlic Press Object
	Mesh* m_mouse; //!< The Mickey Mouse Object
	Mesh* m_cone; //!< The Cone Object
	Mesh* m_character; //!< BB8 Object
	SoundLoader* m_sounderLoader;  //!< Sound loader object
	Collision* m_collision; //!< Collision detection 
	GLuint m_programHandle; //!< The main program handle
	bool m_bKeyPress; //!< If a key has been pressed
	GLSLProgram prog; //!< Program to run the simulation
	FileReader* m_read; //!< File Reader
	SplashScreen* m_ss;	//!< Splash Screen
	char m_cGameState; //!< Game State
	
public:
	GameLogic(); //!< Default constructor	
	void initScene(QuatCamera camera); //!< Initialise the scene 
	void update( float t, QuatCamera camera); //!< Update the scene with animations
	void render(QuatCamera camera); //!< Render mesh objects
	void resize(QuatCamera camera, int, int); //!< Resizing the view port
 	void keyPress(bool b, char c); //!< Detects when a key is press
	char getGameState(); //!< Obtains the current game state
	void changeGameState(int i); //!< Changes the game state
	void linkMe(GLint vertShader, GLint fragShader); //!< Links the shader
	void createShaders(); //!< Creates the fragment and vertex shaders
	void createObjects(); //!< Creates objects to be used in the simulation

 //void setLightParams(QuatCamera camera);
 //void compileAndLinkShader();
};
#endif  