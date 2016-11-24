
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
	m_keyPress = false;
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
	
	/*m_Box = new cube(programHandle);
	m_Box->cubeMap("resources/rmap", GLchar("cube_texture2"));
	m_Box->transformCube(glm::vec3(15, 0, 0), glm::vec3(0.25, 0.25, 0.25), glm::vec3(0.0, 0.0, 0.0), 0);*/

	//Create the room
	m_Room = new cube(programHandle);
	//m_Room->transformCube(glm::vec3(0.0, 0.0, 0.0), glm::vec3(4, 4, 4), glm::vec3(0.0, 1.0, 0.0), 0);
	ModelMatrix = glm::scale(glm::vec3(30));

	m_Room->cubeMap("resources/cubemap", GLchar("cube_texture"));
	
	//Create Robot
	robot = new Robot(programHandle);

	
	//Set start position
	startPosition = { 0.0,-14.0,0.0 };
	fAngle = 0;

	//Make a class for mesh data
	gl::Enable(gl::DEPTH_TEST);
}

void CubeMapScene::linkMe(GLint vertShader, GLint fragShader)
{

    
    // Create the program object
    programHandle = gl::CreateProgram();
    if(0 == programHandle) {
        fprintf(stderr, "Error creating program object.\n");
        exit(1);
    }


    // Attach the shaders to the program object
    gl::AttachShader( programHandle, vertShader );
    gl::AttachShader( programHandle, fragShader );

    // Link the program
    gl::LinkProgram( programHandle );

    // Check for successful linking
    GLint status;
    gl::GetProgramiv( programHandle, gl::LINK_STATUS, &status );
    if (FALSE == status) {

        fprintf( stderr, "Failed to link shader program!\n" );

        GLint logLen;
        gl::GetProgramiv( programHandle, gl::INFO_LOG_LENGTH, &logLen );

        if (logLen > 0) {
            char * log = (char *)malloc(logLen);

            GLsizei written;
            gl::GetProgramInfoLog(programHandle, logLen, &written, log);

            fprintf(stderr, "Program log: \n%s", log);

            free(log);
        }
    } else {
        gl::UseProgram( programHandle );
    }
    
}

void CubeMapScene::update(float t, QuatCamera camera)
{
	float fTime = t / float(1000); //! Divide milliseconds to 1000 to obtain one second.

	robot->Prepare(fTime, m_keyPress);

//	robot.AnimateRobot(m_keyPress,m_key);

}

void CubeMapScene::render(QuatCamera camera)
{
    gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	//Draw robot
	gl::Uniform1i(gl::GetUniformLocation(programHandle, "drawRcube"), true);
	gl::Uniform1i(gl::GetUniformLocation(programHandle, "col"), 2);
	robot->DrawRobot(camera, programHandle, startPosition, fAngle);

	//Room
	gl::Uniform1i(gl::GetUniformLocation(programHandle, "drawRcube"), false);
	setMatrices(camera, ModelMatrix);
	m_Room->Draw();
}

void CubeMapScene::resize(QuatCamera camera,int w, int h)
{
    gl::Viewport(0,0,w,h);
	camera.setAspectRatio(w / h);
}

void CubeMapScene::setMatrices(QuatCamera camera, glm::mat4 model)
{

	MVP = camera.projection() * (camera.view() * model);
	gl::UniformMatrix4fv(gl::GetUniformLocation(programHandle, "MVP"), 1, gl::FALSE_, &MVP[0][0]);
}

void CubeMapScene::keyPress(bool b, char c)
{
	m_keyPress = b;
	m_key = c;
	
	if (c == 'D')
	{
		fAngle -= 0.1f;
	}

	else if (c == 'S')
	{
		fAngle += 0.1f;
	}

	else if (c == 'U')
	{
		startPosition.x += -sin(fAngle) * 0.3f;
		startPosition.z += -cos(fAngle) * 0.3f;
	}
	
	else if (c == 'W')
	{
		startPosition.x -= -sin(fAngle) * 0.3f;
		startPosition.z -= -cos(fAngle) * 0.3f;
	}


}