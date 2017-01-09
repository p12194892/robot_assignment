#include "ShaderLinkerComponent.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>

ShaderLinkerComponent::ShaderLinkerComponent(std::string svertexshader, std::string sfragmentshader)
{
	m_svertexShader = svertexshader;
	m_sfragmentShader = sfragmentshader;

	createShaders();
}

//!< Creates the fragment and vertex shaders
void ShaderLinkerComponent::createShaders()
{

	//////////////////////////////////////////////////////
	/////////// Vertex shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file
	ifstream inFile(m_svertexShader);
	if (!inFile) {
		fprintf(stderr, "Error opening file: resources/shader/basic.vert\n");
		exit(1);
	}


	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	std::string codeStr(code.str());

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
	ifstream fragFile(m_sfragmentShader);
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

	linkShaders(vertShader, fragShader);
}

//!< Links the shader
void ShaderLinkerComponent::linkShaders(GLint vertShader, GLint fragShader)
{
	// Create the program object
	m_programHandle = gl::CreateProgram();
	if (0 == m_programHandle) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}
	// Attach the shaders to the program object
	gl::AttachShader(m_programHandle, vertShader);
	gl::AttachShader(m_programHandle, fragShader);

	// Link the program
	gl::LinkProgram(m_programHandle);

	// Check for successful linking
	GLint status;
	gl::GetProgramiv(m_programHandle, gl::LINK_STATUS, &status);
	if (FALSE == status) {

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		gl::GetProgramiv(m_programHandle, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetProgramInfoLog(m_programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	//else {
		//gl::UseProgram(m_programHandle);
	//}
}

GLuint ShaderLinkerComponent::getProgramHandle()
{
	return m_programHandle;
}

void ShaderLinkerComponent::setUseShader()
{
	gl::UseProgram(m_programHandle);
}