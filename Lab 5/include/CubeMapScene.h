/*!
* @file CubeMapScene.h
* Header file control of rendering the environment 
*/

#ifndef CubeMapScene_H
#define CubeMapScene_H
#include "Texture.h"
#include <vector>
#include <glm\glm.hpp>
#include "scene.h"
#include "cube.h"
#include "gl_core_4_3.hpp"
#include "Robot.h"
#include "FileReader.h"

/*! \class CubeMapScene
\brief The control of rendering the environment 
*/

class CubeMapScene : public Scene
{
private:
	GLuint m_ProgramHandle; //!< The main program handle
	Mesh* m_Room; //!< The room 
	Mesh* m_Box; //!< An Object in the room
	glm::mat4 m_ModelMatrix; //!< Model view matrix of the room
	glm::mat4 m_MVP; //!< The model, view and projection matrix
	bool m_bKeyPress; //!< If a key has been pressed
	char m_cKey; //!< What type of key has been pressed
	Robot* m_Robot; //!< The robot mesh
	glm::vec3 m_StartPosition; //!< The starting position of the robot
	float m_fRobotAngle;//!< The angle of the robot 
	void linkMe(GLint vertShader, GLint fragShader); //!< Links the shader
	Mesh* cube1;
	float m_fSpeed;
	float m_fAngle;


	FileReader* m_Read;

public:
	CubeMapScene(); //!< Default constructor	
	void initScene(QuatCamera camera); //!< Initialise the scene 
	void update( float t, QuatCamera camera); //!< Update the scene with animations
	void render(QuatCamera camera); //!< Render mesh objects
	void resize(QuatCamera camera, int, int); //!< Resizing the view port
 	void keyPress(bool b, char c); //!< Detects when a key is press
	void UpdateModelMatrix(QuatCamera camera, glm::mat4 model); //!< Update the model matrix
};
#endif  