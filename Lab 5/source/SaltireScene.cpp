#include <vector>
#include"SaltireScene.h"
#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
using std::string;


//#define SINGLE_BUFFER

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

SaltireScene::SaltireScene() { }

void SaltireScene::initScene()
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

	/////////////////// Create the view/projection/model matrices ////////////////////

	//Camera attributes
	projection = glm::perspective(glm::radians(45.0f), 500.00f/500.00f, 0.1f, 100.0f);
	//Setting rotate
	m_frotate = 0.0f;

	/////////////////// Create the VBO /////////////////////
	//Vertex data to draw the flag
	vertices.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));//0 V0
	vertices.push_back(glm::vec3(-0.75f, 1.0f, 0.0f));//1 V1
	vertices.push_back(glm::vec3(-0.75f, 1.0f, 0.0f));//2 V1
	vertices.push_back(glm::vec3(0.75f, 1.0f, 0.0f));//3 V2
	vertices.push_back(glm::vec3(0.75f, 1.0f, 0.0f));//4 V2
	vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0f));//5 V3
	vertices.push_back(glm::vec3(-1.0f, 0.75f, 0.0f));//6 V4
	vertices.push_back(glm::vec3(-1.0f, 0.75f, 0.0f));//7 V4
	vertices.push_back(glm::vec3(1.0f, 0.75f, 0.0f));//8 V5
	vertices.push_back(glm::vec3(1.0f, 0.75f, 0.0f));//9 V5
	vertices.push_back(glm::vec3(0.0f, 0.25f, 0.0f));//10 V6
	vertices.push_back(glm::vec3(0.0f, 0.25f, 0.0f));//11 V6
	vertices.push_back(glm::vec3(-0.25f, 0.0f, 0.0f));//12 V7
	vertices.push_back(glm::vec3(-0.25f, 0.0f, 0.0f));//13 V7
	vertices.push_back(glm::vec3(0.25f, 0.0f, 0.0f));//14 V8
	vertices.push_back(glm::vec3(0.25f, 0.0f, 0.0f));//15 V8
	vertices.push_back(glm::vec3(0.0f, -0.25f, 0.0f));//16 V9
	vertices.push_back(glm::vec3(0.0f, -0.25f, 0.0f));//17 V9
	vertices.push_back(glm::vec3(-1.0f, -0.75f, 0.0f));//18 V10
	vertices.push_back(glm::vec3(-1.0f, -0.75f, 0.0f));//19 V10
	vertices.push_back(glm::vec3(1.0f, -0.75f, 0.0f));//20 V11
	vertices.push_back(glm::vec3(1.0f, -0.75f, 0.0f));//21 V11
	vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));//22 V12
	vertices.push_back(glm::vec3(-0.75f, -1.0f,0.0f));//23 V13
	vertices.push_back(glm::vec3(-0.75f, -1.0f, 0.0f));//24 V13
	vertices.push_back(glm::vec3(0.75f, -1.0f, 0.0f));//25 V14
	vertices.push_back(glm::vec3(0.75f, -1.0f, 0.0f));//26 V14
	vertices.push_back(glm::vec3(1.0f, -1.0f, 0.0f));//27 V15


	indices = {
	2,4,11,
	9,21,15,
	24,26,17,
	7,19,13,

	0,1,6,
	3,5,8,
	20,27,25,
	18,22,23,

	3,14,10,
	3,8,14,
	20,25,14,
	25,16,14,
	23,16,18,
	18,12,16,
	1,6,12,
	1,10,12,

	12,10,14,
	12,16,14
	
	
	};
	
	//Colour data to display the RGBA cube		 
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//0 V0 
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//1 V1
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//2 V1
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//3 V2
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//4 v2
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//5 V3
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//6 V4
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//7 V4
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//8 V5
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//9 V5
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//10 V6
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//11 V6
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//12 V7
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//13 V7
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//14 V8
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//15 V8
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//16 V9
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//17 V9
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//18 V10
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//19 V10
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//20 V11
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//21 V11
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//22 V12
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//23 V13
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//24 V13
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//25 V14
	colour.push_back(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));//26 V14
	colour.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));//27 V15

	 //The camera position looking in the Z axis
	view = glm::lookAt(glm::vec3(0.0, 0.0, 11.0)/*position of the camera*/,glm::vec3(0.0, 0.0, 0.0)/*direction of the camera*/, glm::vec3(0.0, 1.0, 0.0)/*represent the positivex-axis of camera space*/);
	 

#ifdef SINGLE_BUFFER
	// Create and set-up the vertex array object using an interlaced buffer
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	//Create and load buffer
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, 3 * 6 * sizeof(GLfloat), NULL, gl::STATIC_DRAW);
	gl::BufferSubData(gl::ARRAY_BUFFER, 0, 3 * 3 * sizeof(GLfloat), positionData);
	gl::BufferSubData(gl::ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), 3 * 3 * sizeof(GLfloat), colourData);


	//Get the VertexPosition attrib handle
	GLuint loc1;
	loc1 = gl::GetAttribLocation(programHandle, "VertexPosition");
	gl::EnableVertexAttribArray(loc1);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc1, 3, gl::FLOAT, FALSE, 0, 0);

	//Get the VertexColour attrib handle
	GLuint loc2;
	loc2 = gl::GetAttribLocation(programHandle, "VertexColour");
	gl::EnableVertexAttribArray(loc2);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc2, 3, gl::FLOAT, FALSE, 0, BUFFER_OFFSET(3 * 3 * sizeof(GLfloat)));

#else

	//Create and populate the buffer objects using separate buffers
	 //index buffer
	gl::GenBuffers(1, &index_buffer);

	//vertex buffer
	gl::GenBuffers(1, &vertex_buffer);

	//colour buffer
	gl::GenBuffers(1, &colour_buffer);

	//Create and set-up the vertex array object
	//Holds the vbos
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	//Binds to the buffer
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, index_buffer);//activates the buffer for the indicies //Putting the data into the buffer
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], gl::STATIC_DRAW);//finds how big the buffer needs to be

	//Binds to the buffer
	gl::BindBuffer(gl::ARRAY_BUFFER, vertex_buffer);//activates the buffer for the verticies
	gl::BufferData(gl::ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], gl::STATIC_DRAW);//finds how big the buffer needs to be

	//Colour buffer
	gl::BindBuffer(gl::ARRAY_BUFFER, colour_buffer);//activates the buffer for the colours													
	gl::BufferData(gl::ARRAY_BUFFER, colour.size() * sizeof(glm::vec4), &colour[0], gl::STATIC_DRAW);//finds how big the buffer needs to be

	 //gets the ID variable in the shader (if not found, is a -1)
	GLuint locl = gl::GetAttribLocation(programHandle, "vertPosition");
	gl::EnableVertexAttribArray(locl);  //Enables the array for vertex

	//gets the ID variable in the shader (if not found, is a -1)
	GLuint locl2 = gl::GetAttribLocation(programHandle, "vertColour");
	gl::EnableVertexAttribArray(locl2);  //Enables the array for colour

	gl::BindBuffer(gl::ARRAY_BUFFER, vertex_buffer);
	//Specifies where the data values for the vertex attribute with location index can be accessed
	gl::VertexAttribPointer(locl, 3, gl::FLOAT, FALSE, sizeof(glm::vec3), (GLubyte *)NULL);

	gl::BindBuffer(gl::ARRAY_BUFFER, colour_buffer);	
	//Specifies where the data values for the colour attribute with location index can be accessed
	gl::VertexAttribPointer(locl2, 4, gl::FLOAT, FALSE, sizeof(glm::vec4), (GLubyte *)NULL);
	
	//binds the array object
	gl::BindVertexArray(0); 
 

#endif

}

void SaltireScene::linkMe(GLint vertShader, GLint fragShader)
{


	// Create the program object
	programHandle = gl::CreateProgram();
	if (0 == programHandle) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}


	// Attach the shaders to the program object
	gl::AttachShader(programHandle, vertShader);
	gl::AttachShader(programHandle, fragShader);

	// Link the program
	gl::LinkProgram(programHandle);

	// Check for successful linking
	GLint status;
	gl::GetProgramiv(programHandle, gl::LINK_STATUS, &status);
	if (FALSE == status) {

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		gl::GetProgramiv(programHandle, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetProgramInfoLog(programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	else {
		gl::UseProgram(programHandle);
	}

}

void SaltireScene::update(float t)
{
	//Increments the rotate variable
	if (m_frotate >= 0)
	{
		if (m_frotate == 360)
		{
			m_frotate = 0;
		}
		m_frotate += 1.0f;
	}
	
	//Rotate in the Y axis
	glm::vec3 rotationY = { 0.0,1.0,0.0 };
	//Rotate * scale * translate
	model = glm::rotate((glm::radians(m_frotate)), rotationY) * glm::scale(glm::vec3(2, 1, 1)) * glm::translate(glm::vec3(1, 0, 0));
	//Modelviewprojection matrix
	mvp = projection  * view * model;
	
	//Get the reference of the MVP matrix in the shader and send mvp
	MatrixID = gl::GetUniformLocation(programHandle, "MVP");
	gl::UniformMatrix4fv(MatrixID, 1, gl::FALSE_, glm::value_ptr(mvp));
}


void SaltireScene::render()
{

	gl::Clear(gl::COLOR_BUFFER_BIT);
	gl::BindVertexArray(vaoHandle);
	gl::DrawElements(gl::TRIANGLES, (GLsizei)indices.size(), gl::UNSIGNED_INT, NULL);
	}

void SaltireScene::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
}
