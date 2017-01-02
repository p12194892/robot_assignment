
#include "GameLogic.h"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <glm\glm.hpp>
#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <glm\gtc\type_ptr.hpp>
#include <string>
#include "QuatCamera.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
using std::string;

//!< Default constructor
GameLogic::GameLogic() {}

//!< Initialise the scene 
void GameLogic::initScene(QuatCamera& camera)
{
	//Initialize Game States
	m_cGameState = 0; //Game state, 0 = Splash Screen
	
	//Initialize Key Press
	m_bKeyPress = false;

	//Initialize the vertex and fragment shader
	createShaders();

	//Initialize File Reader
	m_read = new FileReader();

	//Initialize game objects
	createObjects();	

	//Initialize Collision Detection
	m_collision = new Collision();

	//Initialize Game Sounds
	m_sounderLoader = m_sounderLoader->Instance();
}

//!< Creates the fragment and vertex shaders
void GameLogic::createShaders()
{

	//////////////////////////////////////////////////////
	/////////// Vertex shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file
	ifstream inFile("resources/shader/basic.vert");
	if (!inFile) {
		fprintf(stderr, "Error opening file: resources/shader/basic.vert\n");
		exit(1);
	}


	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	GLuint vertShader = gl::CreateShader(gl::VERTEX_SHADER);
	if (0 == vertShader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = { codeStr.c_str() };
	gl::ShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(vertShader);

	// Check compilation status
	GLint result;
	gl::GetShaderiv(vertShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(vertShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file into shaderCode here
	ifstream fragFile("resources/shader/basic.frag");
	if (!fragFile) {
		fprintf(stderr, "Error opening file: resources/shader/basic.frag\n");
		exit(1);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Create the shader object
	GLuint fragShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (0 == fragShader) {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	gl::ShaderSource(fragShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(fragShader);

	// Check compilation status
	gl::GetShaderiv(fragShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Fragment shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(fragShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	linkMe(vertShader, fragShader);
}

//!< Creates objects to be used in the simulation
void GameLogic::createObjects()
{
	//Creating box
	m_box = new Mesh("Box Model");
	m_read->resetData();	
	m_read->ReadFile("resources/obj/cube.obj");
	m_box->setVertrices(m_read->getVertexPoints());
	m_box->setIndices(m_read->getIndices());
	m_box->setNormals(m_read->getNormals());
	m_box->setStartPos(glm::vec3(20.0, -37.0, 0.0));
	m_box->Load(m_programHandle);
	m_box->translateModelMat(m_box->getStartPos());
	m_box->scaleModelMat(glm::vec3(3));

	//Creating man
	m_man = new Mesh("Man Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/man.obj");
	m_man->setVertrices(m_read->getVertexPoints());
	m_man->setIndices(m_read->getIndices());
	m_man->setNormals(m_read->getNormals());
	m_man->setStartPos(glm::vec3(20.0, -34.0, 0.0));
	m_man->Load(m_programHandle);
	m_man->translateModelMat(m_man->getStartPos());
	m_man->scaleModelMat(glm::vec3(4));

	//Creating cone
	m_cone = new Mesh("Cone Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/cone.obj");
	m_cone->setVertrices(m_read->getVertexPoints());
	m_cone->setIndices(m_read->getIndices());
	m_cone->setNormals(m_read->getNormals());
	m_cone->setStartPos(glm::vec3(-20.0, -40.0, -30.0));
	m_cone->Load(m_programHandle);
	m_cone->translateModelMat(m_cone->getStartPos());
	m_cone->scaleModelMat(glm::vec3(2));

	//Creating cone
	m_character = new Mesh("BB8 Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/bb8.obj");
	m_character->setVertrices(m_read->getVertexPoints());
	m_character->setIndices(m_read->getIndices());
	m_character->setNormals(m_read->getNormals());
	m_character->setStartPos(glm::vec3(0.0, -40.0, -20.0));
	m_character->Load(m_programHandle);
	m_character->translateModelMat(m_character->getStartPos());
	m_character->scaleModelMat(glm::vec3(0.0625));

	//Creating Mickey Mouse
	m_mouse = new Mesh("Mickey Mouse Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/mouse.obj");
	m_mouse->setVertrices(m_read->getVertexPoints());
	m_mouse->setIndices(m_read->getIndices());
	m_mouse->setNormals(m_read->getNormals());
	m_mouse->setStartPos(glm::vec3(20.0, -40.0, -30.0));
	m_mouse->Load(m_programHandle);
	m_mouse->translateModelMat(m_mouse->getStartPos());
	m_mouse->scaleModelMat(glm::vec3(6));

	//Making the splash screen 
	m_ss = new SplashScreen(m_programHandle);
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), true);
	m_ss->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_ss->scaleModelMat(glm::vec3(13));

	//Create the room to hold the scene
	m_room = new Cube(m_programHandle);
	m_room->scaleModelMat(glm::vec3(40));
	m_room->cubeMap("resources/cubemap", "cube_texture");

	//Create Robot character
	m_robot = new Robot(m_programHandle);
	m_robot->setSpeed(0.001f);
	m_robot->setAnimationAngle(0.2f);
	m_robot->setStartPos(glm::vec3(0.0, -24.0, 0.0));
	m_robot->setVariableWalkAngle(0.0);
	gl::Enable(gl::DEPTH_TEST);
	
	//Creating garlic press
	m_garlicpress = new Mesh("Garlic Press Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/garlicpress.obj");
	m_garlicpress->setVertrices(m_read->getVertexPoints());
	m_garlicpress->setIndices(m_read->getIndices());
	m_garlicpress->setNormals(m_read->getNormals());
	m_garlicpress->setStartPos(glm::vec3(-20.0, -34.0, 0.0));
	m_garlicpress->Load(m_programHandle);
	m_garlicpress->translateModelMat(m_garlicpress->getStartPos());
	m_garlicpress->scaleModelMat(glm::vec3(0.5));

	//Creating box
	m_box2 = new Mesh("Box Model 2");
	m_read->resetData();
	m_read->ReadFile("resources/obj/cube.obj");
	m_box2->setVertrices(m_read->getVertexPoints());
	m_box2->setIndices(m_read->getIndices());
	m_box2->setNormals(m_read->getNormals());
	m_box2->setStartPos(glm::vec3(-20.0, -37.0, 0.0));
	m_box2->Load(m_programHandle);
	m_box2->translateModelMat(m_box2->getStartPos());
	m_box2->scaleModelMat(glm::vec3(3));
	
	//Clears the data being read in from OBJ files
	m_read->resetData();

	//Putting the objects into a containter to traverse through
	m_objects.push_back(m_box);
	m_objects.push_back(m_box2);
	m_objects.push_back(m_garlicpress);
	m_objects.push_back(m_mouse);
	m_objects.push_back(m_man);
	m_objects.push_back(m_cone);
	m_objects.push_back(m_character);

	//Lighting stuff
	//compileAndLinkShader();
	//Set up the lighting
	//setLightParams(camera);
}

//!< Links the shader
void GameLogic::linkMe(GLint vertShader, GLint fragShader)
{
    // Create the program object
	m_programHandle = gl::CreateProgram();
    if(0 == m_programHandle) {
        fprintf(stderr, "Error creating program object.\n");
        exit(1);
    }
    // Attach the shaders to the program object
    gl::AttachShader(m_programHandle, vertShader );
    gl::AttachShader(m_programHandle, fragShader );

    // Link the program
    gl::LinkProgram(m_programHandle);

    // Check for successful linking
    GLint status;
    gl::GetProgramiv(m_programHandle, gl::LINK_STATUS, &status );
    if (FALSE == status) {

        fprintf( stderr, "Failed to link shader program!\n" );

        GLint logLen;
        gl::GetProgramiv(m_programHandle, gl::INFO_LOG_LENGTH, &logLen );

        if (logLen > 0) {
            char * log = (char *)malloc(logLen);

            GLsizei written;
            gl::GetProgramInfoLog(m_programHandle, logLen, &written, log);

            fprintf(stderr, "Program log: \n%s", log);

            free(log);
        }
    } else {
        gl::UseProgram(m_programHandle);
    }
    
}

//!< Update the scene with animations
void GameLogic::update(float t, QuatCamera& camera)
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
					m_objects.erase(m_objects.begin()+i);
					m_sounderLoader->GetSound(0)->play();
				}
			}
			break;
	}	
}

//!< Render mesh objects
void GameLogic::render(QuatCamera camera)
{
   gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	switch (m_cGameState)
	{
		//Splash screen state
		case 0:
			m_ss->updateModelMatrix(camera, m_programHandle);
			m_ss->draw();
			
		break;

		//Simulation game state
		case 1:		
			//Tells the shader not to render the splash screen
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), false);

			//Draw robot
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), true);
			m_robot->drawRobot(camera, m_programHandle);

			for (int i = 0; i < m_objects.size(); i++)
			{
					// Draw what is on the objects list
					gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "col"), i);
					m_objects.at(i)->updateModelMatrix(camera, m_programHandle);
					m_objects.at(i)->draw();
			}		

					//Setting material properties for the cube
				/*	prog.setUniform("Kd", 0.0f, 1.0f, 0.0f);
					prog.setUniform("Ld", 0.0f, 1.0f, 0.0f);

					prog.setUniform("Ka", 0.0f, 1.0f, 0.0f);
					prog.setUniform("La", 0.0f, 0.1f, 0.0f);

					prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);
					prog.setUniform("Ls", 0.2f, 0.2f, 0.2f);*/					
				
			//gl::PolygonMode(gl::FRONT_AND_BACK, gl::LINE);

			//Room
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), false);
			m_room->updateModelMatrix(camera, m_programHandle);
			//Draw the room
			m_room->draw();

			break;
	}
}

//!< Resizing the view port
void GameLogic::resize(QuatCamera camera,int w, int h)
{
    gl::Viewport(0,0,w,h);
	camera.setAspectRatio((float)w / (float)h);
}

//!< Detects when a key is press
void GameLogic::keyPress(bool b, char c)
{
	m_bKeyPress = b;
	m_robot->changeDirection(c);
}

//!< Obtains the current game state
char GameLogic::getGameState()
{
	return m_cGameState;
}

//!< Changes the game state
void GameLogic::changeGameState(int i)
{
	m_cGameState = i;
}

/*void GameLogic::setLightParams(QuatCamera camera)
{
//vec3 worldLight = vec3(-5.0f, -5.0f, 5.0f);

//  prog.setUniform("Ld", 1.0f, 1.0f, 1.0f);
//  prog.setUniform("LightPosition", camera.view() * vec4(worldLight,1.0) );
//	prog.setUniform("LightPosition", worldLight);
}*/

/*void GameLogic::buttonPress(float x, float y)
{
if (m_cGameState == 0) //If the game state is splash screen
{
//A way to find out if the splash screen has been clicked



}
}*/

/*void GameLogic::compileAndLinkShader()
{
try {
prog.compileShader("resources/shader/basic.vert");
prog.compileShader("resources/shader/basic.frag");
prog.link();
prog.validate();
prog.use();
}
catch (GLSLProgramException & e) {
cerr << e.what() << endl;
exit(EXIT_FAILURE);
}
}*/
