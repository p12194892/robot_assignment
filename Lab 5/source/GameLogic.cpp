
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

	//Initialize File Reader
	m_Read = new FileReader();

	//Initialize game objects
	createObjects();	

	//Initialize Collision Detection
	m_Collision = new Collision();

	//Initialize Game Sounds
	m_SounderLoader = m_SounderLoader->Instance();
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
	//Creating box
	m_Box = new Mesh("Box Model");
	m_Read->resetData();	
	m_Read->ReadFile("resources/obj/cube.obj");
	m_Box->setVertrices(m_Read->getVertexPoints());
	m_Box->setIndices(m_Read->getIndices());
	m_Box->setNormals(m_Read->getNormals());
	m_Box->setStartPos(glm::vec3(20.0, -37.0, 0.0));
	m_Box->Load(m_ProgramHandle);
	m_Box->translateModelMat(m_Box->getStartPos());
	m_Box->scaleModelMat(glm::vec3(3));

	//Creating man
	m_Man = new Mesh("Man Model");
	m_Read->resetData();
	m_Read->ReadFile("resources/obj/man.obj");
	m_Man->setVertrices(m_Read->getVertexPoints());
	m_Man->setIndices(m_Read->getIndices());
	m_Man->setNormals(m_Read->getNormals());
	m_Man->setStartPos(glm::vec3(20.0, -34.0, 0.0));
	m_Man->Load(m_ProgramHandle);
	m_Man->translateModelMat(m_Man->getStartPos());
	m_Man->scaleModelMat(glm::vec3(4));

	//Creating cone
	m_Cone = new Mesh("Cone Model");
	m_Read->resetData();
	m_Read->ReadFile("resources/obj/cone.obj");
	m_Cone->setVertrices(m_Read->getVertexPoints());
	m_Cone->setIndices(m_Read->getIndices());
	m_Cone->setNormals(m_Read->getNormals());
	m_Cone->setStartPos(glm::vec3(-20.0, -40.0, -30.0));
	m_Cone->Load(m_ProgramHandle);
	m_Cone->translateModelMat(m_Cone->getStartPos());
	m_Cone->scaleModelMat(glm::vec3(2));

	//Creating cone
	m_Character = new Mesh("BB8 Model");
	m_Read->resetData();
	m_Read->ReadFile("resources/obj/bb8.obj");
	m_Character->setVertrices(m_Read->getVertexPoints());
	m_Character->setIndices(m_Read->getIndices());
	m_Character->setNormals(m_Read->getNormals());
	m_Character->setStartPos(glm::vec3(0.0, -40.0, -20.0));
	m_Character->Load(m_ProgramHandle);
	m_Character->translateModelMat(m_Character->getStartPos());
	m_Character->scaleModelMat(glm::vec3(0.0625));

	//Creating Mickey Mouse
	m_Mouse = new Mesh("Mickey Mouse Model");
	m_Read->resetData();
	m_Read->ReadFile("resources/obj/mouse.obj");
	m_Mouse->setVertrices(m_Read->getVertexPoints());
	m_Mouse->setIndices(m_Read->getIndices());
	m_Mouse->setNormals(m_Read->getNormals());
	m_Mouse->setStartPos(glm::vec3(20.0, -40.0, -30.0));
	m_Mouse->Load(m_ProgramHandle);
	m_Mouse->translateModelMat(m_Mouse->getStartPos());
	m_Mouse->scaleModelMat(glm::vec3(6));

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
	
	//Creating garlic press
	m_Garlicpress = new Mesh("Garlic Press Model");
	m_Read->resetData();
	m_Read->ReadFile("resources/obj/garlicpress.obj");
	m_Garlicpress->setVertrices(m_Read->getVertexPoints());
	m_Garlicpress->setIndices(m_Read->getIndices());
	m_Garlicpress->setNormals(m_Read->getNormals());
	m_Garlicpress->setStartPos(glm::vec3(-20.0, -34.0, 0.0));
	m_Garlicpress->Load(m_ProgramHandle);
	m_Garlicpress->translateModelMat(m_Garlicpress->getStartPos());
	m_Garlicpress->scaleModelMat(glm::vec3(0.5));

	//Creating box
	m_Box2 = new Mesh("Box Model 2");
	m_Read->resetData();
	m_Read->ReadFile("resources/obj/cube.obj");
	m_Box2->setVertrices(m_Read->getVertexPoints());
	m_Box2->setIndices(m_Read->getIndices());
	m_Box2->setNormals(m_Read->getNormals());
	m_Box2->setStartPos(glm::vec3(-20.0, -37.0, 0.0));
	m_Box2->Load(m_ProgramHandle);
	m_Box2->translateModelMat(m_Box2->getStartPos());
	m_Box2->scaleModelMat(glm::vec3(3));
	
	//Clears the data being read in from OBJ files
	m_Read->resetData();

	//Putting the objects into a containter to traverse through
	m_Objects.push_back(m_Box);
	m_Objects.push_back(m_Box2);
	m_Objects.push_back(m_Garlicpress);
	m_Objects.push_back(m_Mouse);
	m_Objects.push_back(m_Man);
	m_Objects.push_back(m_Cone);
	m_Objects.push_back(m_Character);

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

			//Collision Detection
			m_Objects = m_Collision->checkVectorDistance(m_Objects, m_Robot->getInitPos());

			for (int i = 0; i < m_Objects.size(); i++)
			{
				if (!m_Objects.at(i)->isDrawable())
				{
					//pop it off the list and play a sound
					m_Objects.erase(m_Objects.begin()+i);
					m_SounderLoader->GetSound(0)->play();
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

			for (int i = 0; i < m_Objects.size(); i++)
			{
					// Draw what is on the objects list
					gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "col"), i);
					UpdateModelMatrix(camera, m_Objects.at(i)->getModelMat());
					m_Objects.at(i)->Draw();
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
