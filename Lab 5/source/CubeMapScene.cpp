
#include "CubeMapScene.h"
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


//#define SINGLE_BUFFER

CubeMapScene::CubeMapScene() {}

void CubeMapScene::initScene(QuatCamera camera)
{
	m_bKeyPress = false;
    //////////////////////////////////////////////////////
    /////////// Vertex shader //////////////////////////
    //////////////////////////////////////////////////////
	
    // Load contents of file
    ifstream inFile( "resources/shader/basic.vert" );
    if (!inFile) {
        fprintf(stderr, "Error opening file: resources/shader/basic.vert\n" );
        exit(1);
    }
	

    std::stringstream code;
    code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

    // Create the shader object
    GLuint vertShader = gl::CreateShader( gl::VERTEX_SHADER );
    if (0 == vertShader) {
      fprintf(stderr, "Error creating vertex shader.\n");
      exit(EXIT_FAILURE);
    }

    // Load the source code into the shader object
    const GLchar* codeArray[] = {codeStr.c_str()};
    gl::ShaderSource(vertShader, 1, codeArray, NULL);

    // Compile the shader
    gl::CompileShader( vertShader );

    // Check compilation status
    GLint result;
    gl::GetShaderiv( vertShader, gl::COMPILE_STATUS, &result );
    if( FALSE == result ) {
       fprintf( stderr, "Vertex shader compilation failed!\n" );

       GLint logLen;
       gl::GetShaderiv( vertShader, gl::INFO_LOG_LENGTH, &logLen );

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
    ifstream fragFile( "resources/shader/basic.frag" );
    if (!fragFile) {
        fprintf(stderr, "Error opening file: resources/shader/basic.frag\n" );
        exit(1);
    }

    std::stringstream fragCode;
    fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

    // Create the shader object
    GLuint fragShader = gl::CreateShader( gl::FRAGMENT_SHADER );
    if (0 == fragShader) {
      fprintf(stderr, "Error creating fragment shader.\n");
      exit(1);
    }

    // Load the source code into the shader object
    codeArray[0] = codeStr.c_str();
    gl::ShaderSource( fragShader, 1, codeArray, NULL );

    // Compile the shader
    gl::CompileShader( fragShader );

    // Check compilation status
    gl::GetShaderiv( fragShader, gl::COMPILE_STATUS, &result );
    if (FALSE == result) {
       fprintf( stderr, "Fragment shader compilation failed!\n" );

       GLint logLen;
       gl::GetShaderiv( fragShader, gl::INFO_LOG_LENGTH, &logLen );

       if (logLen > 0) {
           char * log = (char *)malloc(logLen);

           GLsizei written;
           gl::GetShaderInfoLog(fragShader, logLen, &written, log);

           fprintf(stderr, "Shader log: \n%s", log);

           free(log);
       }
    }

    linkMe(vertShader, fragShader);

    /////////////////// Create the VBO //////////////////

	//Create the room
	  m_Room = new cube(m_ProgramHandle);
	 m_ModelMatrix = glm::scale(glm::vec3(30));

	m_Room->cubeMap("resources/cubemap", GLchar("cube_texture"));
	
	//Create Robot
	m_Robot = new Robot(m_ProgramHandle);

	//Set start position
	m_StartPosition = { 0.0,-14.0,0.0 };
	m_fRobotAngle = 0;

	//Make a class for mesh data
	gl::Enable(gl::DEPTH_TEST);


//////EXAMPLE OF CUBE BEING READ IN BY OBJ READER AND BEING RENDERED///
	cube1 = new Mesh;
	m_Read = new FileReader();
	m_Read->ReadFile("resources/obj/cube.obj");
	cube1->setVertrices(m_Read->getVertexPoints());
	cube1->setIndices(m_Read->getIndices());
	cube1->Load(m_ProgramHandle);
	m_ModelMatrix2 = glm::translate(glm::vec3(10.0, -29.0, 0.0));

}

void CubeMapScene::linkMe(GLint vertShader, GLint fragShader)
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

void CubeMapScene::update(float t, QuatCamera camera)
{
	float fTime = t / float(1000); //! Divide milliseconds to 1000 to obtain one second.

	m_Robot->Prepare(m_fAngle, m_fSpeed, fTime, m_bKeyPress);
}

void CubeMapScene::render(QuatCamera camera)
{
    gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//Draw robot
	gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "drawRcube"), true);
	m_Robot->DrawRobot(camera, m_ProgramHandle, m_StartPosition, m_fRobotAngle);
	
	//Read in cube
	gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "col"), 0);
	UpdateModelMatrix(camera, m_ModelMatrix2);
	cube1->Draw();

	//Room
	gl::Uniform1i(gl::GetUniformLocation(m_ProgramHandle, "drawRcube"), false);
	UpdateModelMatrix(camera, m_ModelMatrix);
	m_Room->Draw();

	
}

void CubeMapScene::resize(QuatCamera camera,int w, int h)
{
    gl::Viewport(0,0,w,h);
	camera.setAspectRatio((float)w / (float)h);
}

void CubeMapScene::UpdateModelMatrix(QuatCamera camera, glm::mat4 model)
{

	m_MVP = camera.projection() * (camera.view() * model);
	gl::UniformMatrix4fv(gl::GetUniformLocation(m_ProgramHandle, "MVP"), 1, gl::FALSE_, &m_MVP[0][0]);
}

void CubeMapScene::keyPress(bool b, char c)
{
	m_bKeyPress = b;
	m_cKey = c;

	if (c == 'D')
	{
		m_fRobotAngle -= 0.1f;
	}

	else if (c == 'S')
	{
		m_fRobotAngle += 0.1f;
	}

	else if (c == 'U')
	{
		m_StartPosition.x += -sin(m_fRobotAngle) * 0.3f;
		m_StartPosition.z += -cos(m_fRobotAngle) * 0.3f;

		//Walking
		m_fSpeed = 0.01f;
		m_fAngle = 0.1f;
	}

	else if (c == 'W')
	{
		m_StartPosition.x -= -sin(m_fRobotAngle) * 0.3f;
		m_StartPosition.z -= -cos(m_fRobotAngle) * 0.3f;
		//Walking
		m_fSpeed = 0.01f;
		m_fAngle = 0.1f;
	}

	else if (c == 'P')
	{
		//Running Key
		m_StartPosition.x += -sin(m_fRobotAngle) * 1.0f;
		m_StartPosition.z += -cos(m_fRobotAngle) * 1.0f;
		//Running
		m_fSpeed = 0.1f;
		m_fAngle = 0.5f;
	}

	else if (c == 'O')
	{
		//Running Key
		m_StartPosition.x -= -sin(m_fRobotAngle) * 1.0f;
		m_StartPosition.z -= -cos(m_fRobotAngle) * 1.0f;
		//Running
		m_fSpeed = 0.1f;
		m_fAngle = 0.5f;
	}


}