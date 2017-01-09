
#include "BaseGame.h"
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "CameraComponent.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "tinyxml2.h"
#include <iostream>
using namespace tinyxml2;

//!< Default constructor
BaseGame::BaseGame() {}

//!< Creates objects to be used in the simulation
void BaseGame::createObjects()
{
	std::cout << "Loading Objects into the scene" << std::endl << std::endl;
	//Creating box
    m_box = new MeshComponent("Box Model");
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
	m_man = new MeshComponent("Man Model");
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
	m_cone = new MeshComponent("Cone Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/cone.obj");
	m_cone->setVertrices(m_read->getVertexPoints());
	m_cone->setIndices(m_read->getIndices());
	m_cone->setNormals(m_read->getNormals());
	m_cone->setStartPos(glm::vec3(-20.0, -40.0, -30.0));
	m_cone->Load(m_programHandle);
	m_cone->translateModelMat(m_cone->getStartPos());
	m_cone->scaleModelMat(glm::vec3(2));

	//Creating character
	m_character = new MeshComponent("BB8 Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/bb8.obj");
	m_character->setVertrices(m_read->getVertexPoints());
	m_character->setIndices(m_read->getIndices());
	m_character->setNormals(m_read->getNormals());
	m_character->setStartPos(glm::vec3(0.0, -40.0, -20.0));
	m_character->Load(m_programHandle);
	m_character->translateModelMat(m_character->getStartPos());
	m_character->scaleModelMat(glm::vec3(0.0625));

	//Creating garlic press
	m_garlicpress = new MeshComponent("Garlic Press Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/garlicpress.obj");
	m_garlicpress->setVertrices(m_read->getVertexPoints());
	m_garlicpress->setIndices(m_read->getIndices());
	m_garlicpress->setNormals(m_read->getNormals());
	m_garlicpress->setStartPos(glm::vec3(-20.0, -34.0, 0.0));
	m_garlicpress->Load(m_programHandle);
	m_garlicpress->translateModelMat(m_garlicpress->getStartPos());
	m_garlicpress->scaleModelMat(glm::vec3(0.5));	

	//Making the splash screen 	
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), true);
	m_splashScreenComponent = new UIComponent(m_programHandle);
	m_splashScreenComponent->setTextureUnit(0);
	m_splashScreenComponent->loadTexture("resources/shader/sign.png", "tex");
	m_splashScreenComponent->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_splashScreenComponent->scaleModelMat(glm::vec3(13));
		
	//Making the menu screen
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bMenu"), false);
	m_menuScreenComponent = new UIComponent(m_programHandle);
	m_menuScreenComponent->setTextureUnit(1);
	m_menuScreenComponent->loadTexture("resources/shader/menu.png", "menutexture");
	m_menuScreenComponent->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_menuScreenComponent->scaleModelMat(glm::vec3(13));

	//Making start button
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbuttontexture"), false);
	m_buttonStart = new Button(m_programHandle);
	m_buttonStart->setTextureUnit(2);
	m_buttonStart->loadTexture("resources/shader/button1.png", "buttontex");
	m_buttonStart->translateModelMat(glm::vec3(-2.0, -26.6, 18.0));
	m_buttonStart->scaleModelMat(glm::vec3(3.0f, 1.0f, 0.0f));

	//Making exit button
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bexitButton"), false);
	m_buttonExit = new Button(m_programHandle);
	m_buttonExit->setTextureUnit(3);
	m_buttonExit->loadTexture("resources/shader/button2.png", "exitButtonTex");
	m_buttonExit->translateModelMat(glm::vec3(-2.0, -27.4, 18.0));
	m_buttonExit->scaleModelMat(glm::vec3(3.0f, 1.0f, 0.0f));

	//Making instruction button
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bmoreButton"), false);
	m_buttonInstruction = new Button(m_programHandle);
	m_buttonInstruction->setTextureUnit(4);
	m_buttonInstruction->loadTexture("resources/shader/button3.png", "moreButtonTex");
	m_buttonInstruction->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_buttonInstruction->scaleModelMat(glm::vec3(3.0f, 1.0f, 0.0f));

	//Create the room to hold the scene
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), false);
	m_room = new Cube(m_programHandle);
	m_room->setTextureUnit(5);
	m_room->scaleModelMat(glm::vec3(40));
	m_room->cubeMap("resources/cubemap", "cube_texture");
	
	//Creating box
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawRubix"), false);
	m_box2 = new MeshComponent("Box Model 2");
	m_read->resetData();
	m_read->ReadFile("resources/obj/cube.obj");
	m_box2->setVertrices(m_read->getVertexPoints());
	m_box2->setIndices(m_read->getIndices());
	m_box2->setNormals(m_read->getNormals());
	m_box2->setStartPos(glm::vec3(-20.0, -37.0, 0.0));
	m_box2->Load(m_programHandle);
	m_box2->setTextureUnit(6);
	m_box2->cubeMap("resources/rmap", "cube_texture2");
	m_box2->translateModelMat(m_box2->getStartPos());
	m_box2->scaleModelMat(glm::vec3(3));

	//Creating instructions screen
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bcontrolScreen"), false);
	m_instructionsComponent = new UIComponent(m_programHandle);
	m_instructionsComponent->setTextureUnit(7);
	m_instructionsComponent->loadTexture("resources/shader/controls.png", "controlTex");
	m_instructionsComponent->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_instructionsComponent->scaleModelMat(glm::vec3(13));

	//Creating Back Button
	gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbackbutton"), false);
	m_backButton = new Button(m_programHandle);
	m_backButton->setTextureUnit(8);
	m_backButton->loadTexture("resources/shader/back.png", "buttonBackTex");
	m_backButton->translateModelMat(glm::vec3(-2.0, -27.8, 18.0));
//	m_backButton->scaleModelMat(glm::vec3(.0f));

	//Creating Mickey Mouse
	//gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bPattern"), false);
	m_mouse = new MeshComponent("Mickey Mouse Model");
	m_read->resetData();
	m_read->ReadFile("resources/obj/mouse.obj");
	m_mouse->setVertrices(m_read->getVertexPoints());
	m_mouse->setIndices(m_read->getIndices());
	m_mouse->setNormals(m_read->getNormals());
	m_mouse->setStartPos(glm::vec3(20.0, -40.0, -30.0));
	m_mouse->Load(m_programHandle);
	m_mouse->translateModelMat(m_mouse->getStartPos());
	m_mouse->scaleModelMat(glm::vec3(6));
 
	//Create Robot character
	m_robot = new Robot(m_programHandle);
	m_robot->setSpeed(0.001f);
	m_robot->setAnimationAngle(0.2f);
	m_robot->setStartPos(glm::vec3(0.0, -24.0, 0.0));
	m_robot->setVariableWalkAngle(0.0);

	//Clears the data being read in from OBJ files
	m_read->resetData();

	//Putting the objects into a containter to traverse through
	m_objects.push_back(m_box);
	m_objects.push_back(m_man);
	m_objects.push_back(m_cone);
	//m_objects.push_back(m_box2);
	m_objects.push_back(m_garlicpress);
	m_objects.push_back(m_mouse);	
	m_objects.push_back(m_character);
	m_objects.push_back(m_box);
	//Lighting stuff
	//compileAndLinkShader();
	//Set up the lighting
	//setLightParams(camera);
}

//!< Render mesh objects
void BaseGame::render(CameraComponent camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	switch (m_cGameState)
	{
		//Splash screen state
		case 0:
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), true);
			m_splashScreenComponent->updateModelMatrix(camera, m_programHandle);
			m_splashScreenComponent->draw();
			
		break;
		
		case 1:
			//Menu Screen state
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), false);
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "col"), 3);
			
			//Start Buttons
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbuttontexture"), true);
			m_buttonStart->updateModelMatrix(camera, m_programHandle);
			m_buttonStart->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbuttontexture"), false);

			//Exit Button
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bexitButton"), true);
			m_buttonExit->updateModelMatrix(camera, m_programHandle);
			m_buttonExit->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bexitButton"), false);

			//Instruction Button
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bmoreButton"), true);
			m_buttonInstruction->updateModelMatrix(camera, m_programHandle);
			m_buttonInstruction->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bmoreButton"), false);

			//Menu
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bMenu"), true);
			m_menuScreenComponent->updateModelMatrix(camera, m_programHandle);
			m_menuScreenComponent->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bMenu"), false);
		break;
		
		case 2:		
			//Simulation game state
			//Tells the shader not to render the splash screen or menu screen
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), false);
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bMenu"), false);

		//Room
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), true);
		m_room->updateModelMatrix(camera, m_programHandle);
		m_room->draw();
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), false);


			for (int i = 0; i < m_objects.size(); i++)
			{
				// Draw what is on the objects list
				gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "col"), i);
				m_objects.at(i)->updateModelMatrix(camera, m_programHandle);
				m_objects.at(i)->draw();
			}

			//Draw robot
			m_robot->drawRobot(camera, m_programHandle);	

			//drawing box test to see if textures are working
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawRubix"), true);
			m_box2->updateModelMatrix(camera, m_programHandle);
			m_box2->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawRubix"), false);

			//Drawing mickey in pattern wrapper
			/*gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bPattern"), true);
			m_mouse->updateModelMatrix(camera, m_programHandle);
			m_mouse->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bPattern"), false);*/



					//Setting material properties for the cube
				/*	prog.setUniform("Kd", 0.0f, 1.0f, 0.0f);
					prog.setUniform("Ld", 0.0f, 1.0f, 0.0f);

					prog.setUniform("Ka", 0.0f, 1.0f, 0.0f);
					prog.setUniform("La", 0.0f, 0.1f, 0.0f);

					prog.setUniform("Ks", 1.0f, 1.0f, 1.0f);
					prog.setUniform("Ls", 0.2f, 0.2f, 0.2f);*/					
				
			//gl::PolygonMode(gl::FRONT_AND_BACK, gl::LINE);		

			break;

		case 3:
			//render for game state 3

			//Back button
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbackbutton"), true);
			m_backButton->updateModelMatrix(camera, m_programHandle);
			m_backButton->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbackbutton"), false);

			//Controls screen
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bcontrolScreen"), true);
			m_menuScreenComponent->updateModelMatrix(camera, m_programHandle);
			m_menuScreenComponent->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bcontrolScreen"), false);
			break;
	}

}

//!< Detects when a key is press
void BaseGame::keyPress(bool b, char c)
{
	m_bKeyPress = b;
	m_robot->changeDirection(c);
}

//!< Obtains the current game state
char BaseGame::getGameState()
{
	// 0 = splash screen, 1 = simulation
	return m_cGameState;
}

//!< Changes the game state
void BaseGame::changeGameState(int i)
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
