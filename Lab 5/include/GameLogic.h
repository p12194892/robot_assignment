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

/*! \class GameLogic
\brief The control of rendering and controlling the simulation  
*/

//!< Inherits from scene
class GameLogic : public Scene
{
private:
	//Game objects that make the scene
	Mesh* m_Room; //!< The room 
	Robot* m_Robot; //!< The robot mesh	
	Mesh* m_Box; //!< Read in box

	GLuint m_ProgramHandle; //!< The main program handle
	bool m_bKeyPress; //!< If a key has been pressed
	GLSLProgram prog;
	FileReader* m_Read;
	SplashScreen* m_ss;	
	char m_cGameState;
	char m_cCam2;
	//Button* m_startButton;

public:
	GameLogic(); //!< Default constructor	
	void initScene(QuatCamera camera); //!< Initialise the scene 
	void update( float t, QuatCamera camera); //!< Update the scene with animations
	void render(QuatCamera camera); //!< Render mesh objects
	void resize(QuatCamera camera, int, int); //!< Resizing the view port
 	void keyPress(bool b, char c); //!< Detects when a key is press
	void UpdateModelMatrix(QuatCamera camera, glm::mat4 model); //!< Update the model matrix
	char getGameState();
	void changeGameState(int i);
	void linkMe(GLint vertShader, GLint fragShader); //!< Links the shader
	void createShaders();
	void createObjects();

 //	void buttonPress(float x, float y);
 //void setLightParams(QuatCamera camera);
 //void compileAndLinkShader();
};
#endif  