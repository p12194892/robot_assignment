
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


GameLogic::GameLogic() {}

void GameLogic::initScene(QuatCamera camera)
{
	//Initialize Game States
	m_cGameState = 0; //Game state, 0 = Splash Screen
	
	//Initialize Key Press
	m_bKeyPress = false;

	//Initialize the vertex and fragment shader
	createShaders();

	//Initialize game objects
	createObjects();	
}

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

void GameLogic::createObjects()
{
	//Making the splash screen 
	m_ss = new SplashScreen(m_ProgramHandle);
	gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "bSplashScreenState"), true);
	m_ss->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_ss->scaleModelMat(glm::vec3(13));

	//Create the room to hold the scene
	m_Room = new cube(m_ProgramHandle);
	m_Room->scaleModelMat(glm::vec3(40));
	m_Room->cubeMap("resources/cubemap", "cube_texture");


	//Create Robot character
	m_Robot = new Robot(m_ProgramHandle);
	m_Robot->setSpeed(0.001f);
	m_Robot->setAngle(0.2f);
	m_Robot->setInitPos(glm::vec3(0.0, -24.0, 0.0));
	m_Robot->setVariableWalkAngle(0.0);
	gl::Enable(gl::DEPTH_TEST);
	
	m_Box = new Mesh;
	m_Read = new FileReader();
	m_Read->ReadFile("resources/obj/cube.obj");
	m_Box->setVertrices(m_Read->getVertexPoints());
	m_Box->setIndices(m_Read->getIndices());
	m_Box->setNormals(m_Read->getNormals());
	m_Box->setStartPos(glm::vec3(20.0, -39.0, 0.0));
	m_Box->Load(m_ProgramHandle);
	m_Box->translateModelMat(m_Box->getStartPos());

	//Lighting stuff
	//compileAndLinkShader();
	//Set up the lighting
	//setLightParams(camera);
}

void GameLogic::linkMe(GLint vertShader, GLint fragShader)
{
    // Create the program object
	m_ProgramHandle = gl::CreateProgram();
    if(0 == m_ProgramHandle) {
        fprintf(stderr, "Error creating program object.\n");
        exit(1);
    }
    // Attach the shaders to the program object
    gl::AttachShader(m_ProgramHandle, vertShader );
    gl::AttachShader(m_ProgramHandle, fragShader );

    // Link the program
    gl::LinkProgram(m_ProgramHandle);

    // Check for successful linking
    GLint status;
    gl::GetProgramiv(m_ProgramHandle, gl::LINK_STATUS, &status );
    if (FALSE == status) {

        fprintf( stderr, "Failed to link shader program!\n" );

        GLint logLen;
        gl::GetProgramiv(m_ProgramHandle, gl::INFO_LOG_LENGTH, &logLen );

        if (logLen > 0) {
            char * log = (char *)malloc(logLen);

            GLsizei written;
            gl::GetProgramInfoLog(m_ProgramHandle, logLen, &written, log);

            fprintf(stderr, "Program log: \n%s", log);

            free(log);
        }
    } else {
        gl::UseProgram(m_ProgramHandle);
    }
    
}

void GameLogic::update(float t, QuatCamera camera)
{

	switch (m_cGameState)
	{
		case 0:
		//Any code for getting the splash screen button
		break;

		case 1:
			float fTime = t / float(1000); //! Divide milliseconds to 1000 to obtain one second.
			m_Robot->Prepare(fTime, m_bKeyPress);

			if (m_Box->isDrawable() == true)
			{
				//Works out the distance between the objects and the robot
				vec3 distance;
				distance.x = m_Box->getStartPos().x - m_Robot->getInitPos().x;
				distance.z = m_Box->getStartPos().z - m_Robot->getInitPos().z;
				float d = sqrt(dot(distance, distance));

				if (d < 2)
				{
					m_Box->setDrawable(false);
				}
			}

			break;

	}	
}

void GameLogic::render(QuatCamera camera)
{
   gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	switch (m_cGameState)
	{
		//Splash screen state
		case 0:
	
			UpdateModelMatrix(camera, m_ss->getModelMat());
			m_ss->Draw();
			
		break;

		//Simulation game state
		case 1:
			//Tells the shader not to render the splash screen
			gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "bSplashScreenState"), false);

			//Draw robot
			gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "drawRcube"), true);
			m_Robot->DrawRobot(camera, m_ProgramHandle);

			if (m_Box->isDrawable())
			{
				//Read in cube
				gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "col"), 0);

				//UpdateModelMatrix(camera, m_ModelMatrix2);
				UpdateModelMatrix(camera, m_Box->getModelMat());

				//Setting material properties for the cube
			/*	prog.setUniform("Kd", 0.0f, 1.0f, 0.0f);
				prog.setUniform("Ld", 0.0f, 1.0f, 0.0f);

				prog.setUniform("Ka", 0.0f, 1.0f, 0.0f);
				prog.setUniform("La", 0.0f, 0.1f, 0.0f);

				prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);
				prog.setUniform("Ls", 0.2f, 0.2f, 0.2f);*/

				m_Box->Draw();
			}

			//Now set up the teapot 
		//	UpdateModelMatrix(camera, m_Box->getModelMat());
			//Set the Teapot material properties in the shaders and render
		//	teapot->render();

			//Room
			gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "drawRcube"), false);
			UpdateModelMatrix(camera, m_Room->getModelMat());
			//Draw the room
			m_Room->Draw();

			break;
	}
		
	
}

void GameLogic::resize(QuatCamera camera,int w, int h)
{
    gl::Viewport(0,0,w,h);
	camera.setAspectRatio((float)w / (float)h);
}

void GameLogic::UpdateModelMatrix(QuatCamera camera, glm::mat4 model)
{
	camera.updateMVP(model);
	gl::UniformMatrix4fv(gl::GetUniformLocation(m_ProgramHandle, "MVP"), 1, gl::FALSE_, &camera.getMVP()[0][0]);

	

	//Lighting stuff - See if this works?
/*	mat4 mv = camera.view() * model;
//	prog.setUniform("ModelViewMatrix", mv);
	prog.setUniform("NormalMatrix",
		mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
//	prog.setUniform("MVP", camera.projection() * mv);
	// the correct matrix to transform the normal is the transpose of the inverse of the M matrix
	//mat3 normMat = glm::transpose(glm::inverse(mat3(model)));
	prog.setUniform("M", model);
	//prog.setUniform("NormalMatrix", normMat);
	prog.setUniform("V", camera.view());
	//prog.setUniform("P", camera.projection());*/


}

void GameLogic::keyPress(bool b, char c)
{
	m_bKeyPress = b;
	m_Robot->changeDirection(c);

	if (c == 'F')
	{
		m_cCam2 = 'F';
	}
}

char GameLogic::getGameState()
{
	return m_cGameState;
}

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
