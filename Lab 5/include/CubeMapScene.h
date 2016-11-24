#ifndef CubeMapScene_H
#define CubeMapScene_H
#include "Texture.h"
#include <vector>
#include <glm\glm.hpp>
#include "scene.h"
#include "cube.h"
#include "gl_core_4_3.hpp"
#include "Robot.h"
class CubeMapScene : public Scene
{
private:
	int width, height;
	GLuint programHandle;
	Mesh* m_Room;
	Mesh* m_Box;
	glm::mat4 ModelMatrix;
	glm::mat4 model;
	glm::mat4 MVP;
	bool hasDrawn;
	bool m_keyPress;
	char m_key;
	Robot* robot;

	//NEW
	glm::vec3 startPosition;
	float fAngle;


	void linkMe(GLint vertShader, GLint fragShader);

	void setMatrices(QuatCamera camera, glm::mat4 model);
public:
	CubeMapScene();
	
	void initScene(QuatCamera camera);
	void update( float t, QuatCamera camera);
	void render(QuatCamera camera);
	void resize(QuatCamera camera, int, int);
	void keyPress(bool b, char c);
};
#endif  //sceneTexture_H