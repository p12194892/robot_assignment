#ifndef sceneTexture_H
#define sceneTexture_H
#include "Texture.h"
#include <vector>
#include <glm\glm.hpp>

#include "scene.h"

#include "gl_core_4_3.hpp"

class sceneTexture : public Scene
{
private:
	int width, height;
	GLuint vboHandles[2];
	GLuint vbo;
	GLuint vaoHandle;
	GLuint programHandle;
	Texture *gTexture;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> uvData;
	GLuint index_buffer;
	GLuint vertex_buffer;
	GLuint uv_buffer;
	void linkMe(GLint vertShader, GLint fragShader);

public:
	sceneTexture();

	void initScene();
	void update( float t);
	void render();
	void resize(int, int);

};
#endif  //sceneTexture_H