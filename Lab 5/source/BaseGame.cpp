#include "BaseGame.h"
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "CameraComponent.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/transform.hpp>

//!< Default constructor
BaseGame::BaseGame() {}

//!< Creates objects to be used in the simulation
void BaseGame::createObjects()
{
	std::cout << "Loading objects into the scene" << std::endl << std::endl;

	//Making the splash screen 	
	m_splashScreenComponent = new UIComponent(m_programHandle);
	m_splashScreenComponent->setTextureUnit(0);
	m_splashScreenComponent->loadTexture("resources/textures/sign.png");
	m_splashScreenComponent->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_splashScreenComponent->scaleModelMat(glm::vec3(13));
		
	//Making the menu screen
	m_menuScreenComponent = new UIComponent(m_programHandle);
	m_menuScreenComponent->setTextureUnit(1);
	m_menuScreenComponent->loadTexture("resources/textures/menu.png");
	m_menuScreenComponent->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_menuScreenComponent->scaleModelMat(glm::vec3(13));

	//Making start button
	m_buttonStart = new Button(m_programHandle);
	m_buttonStart->setTextureUnit(2);
	m_buttonStart->loadTexture("resources/textures/button1.png");
	m_buttonStart->translateModelMat(glm::vec3(-2.0, -26.6, 18.0));
	m_buttonStart->scaleModelMat(glm::vec3(3.0f, 1.0f, 0.0f));

	//Making exit button
	m_buttonExit = new Button(m_programHandle);
	m_buttonExit->setTextureUnit(3);
	m_buttonExit->loadTexture("resources/textures/button2.png");
	m_buttonExit->translateModelMat(glm::vec3(-2.0, -27.4, 18.0));
	m_buttonExit->scaleModelMat(glm::vec3(3.0f, 1.0f, 0.0f));

	//Making instruction button
	m_buttonInstruction = new Button(m_programHandle);
	m_buttonInstruction->setTextureUnit(4);
	m_buttonInstruction->loadTexture("resources/textures/button3.png");
	m_buttonInstruction->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_buttonInstruction->scaleModelMat(glm::vec3(3.0f, 1.0f, 0.0f));

	//Creating instructions screen
	m_instructionsComponent = new UIComponent(m_programHandle);
	m_instructionsComponent->setTextureUnit(5);
	m_instructionsComponent->loadTexture("resources/textures/controls.png");
	m_instructionsComponent->translateModelMat(glm::vec3(-2.0, -27.0, 18.0));
	m_instructionsComponent->scaleModelMat(glm::vec3(13));

	//Creating Back Button
	m_backButton = new Button(m_programHandle);
	m_backButton->setTextureUnit(6);
	m_backButton->loadTexture("resources/textures/back.png");
	m_backButton->translateModelMat(glm::vec3(-2.0, -27.8, 18.0));

	m_read->resetData();
	m_read->ReadFile("resources/obj/cube.obj");

	//Create the room to hold the scene
	m_room = new Cube(m_lightingShader->getProgramHandle(), "Room", m_read);
	m_room->setTextureUnit(0);
	m_room->scaleModelMat(glm::vec3(40));
	m_room->loadTexture("resources/textures/robot_left.png");

	//Creating box
	m_rubix = new Cube(m_lightingShader->getProgramHandle(),"Cube", m_read);
	m_rubix->setStartPos(glm::vec3(-20.0, -35.0, 0.0));
	m_rubix->setTextureUnit(1);
	m_rubix->loadTexture("resources/textures/pattern5.png");
	m_rubix->translateModelMat(m_rubix->getStartPos());
	m_rubix->scaleModelMat(glm::vec3(5));

	//Creating box
	m_box = new Cube(m_lightingShader->getProgramHandle(), "Cube", m_read);
	m_box->setStartPos(glm::vec3(-20.0, -35.0, 25.0));
	m_box->setTextureUnit(2);
	m_box->loadTexture("resources/textures/pattern3.png");
	m_box->translateModelMat(m_box->getStartPos());
	m_box->scaleModelMat(glm::vec3(5));
	
	//Creating another box
	m_box2 = new Cube(m_lightingShader->getProgramHandle(), "Cube", m_read);
	m_box2->setStartPos(glm::vec3(18.0, -32.0, -10.0));
	m_box2->translateModelMat(m_box2->getStartPos());
	m_box2->scaleModelMat(glm::vec3(5.0,8.0,5.0));
	m_box2->rotateModelMat(45.0, glm::vec3(0.0, 1.0, 0.0));

	//Create Robot character
	m_robot = new Robot(m_programHandle, m_read);
	m_robot->setTextureUnit(7);
	m_robot->loadTexture("resources/textures/pattern5.png");
	m_robot->setSpeed(0.01f);
	m_robot->setAnimationAngle(0.2f);
	m_robot->setStartPos(glm::vec3(0.0, -24.0, 0.0));
	m_robot->setVariableWalkAngle(0.0);

	//Sphere object 
	m_sphere = new MeshComponent("Sphere");
	m_read->resetData();
	m_read->ReadFile("resources/obj/sphere.obj");
	m_sphere->setVertrices(m_read->getVertexPoints());
	m_sphere->setIndices(m_read->getIndices());
	m_sphere->setNormals(m_read->getNormals());
	m_sphere->setUVs(m_read->getTexPoints());
	m_sphere->setStartPos(glm::vec3(32.0, -34.0, -30.0));
	m_sphere->Load(m_programHandle);
	m_sphere->setTextureUnit(3);
	m_sphere->loadTexture("resources/textures/pattern3.png");
	m_sphere->translateModelMat(m_sphere->getStartPos());
	m_sphere->scaleModelMat(glm::vec3(6));
	m_sphere->rotateModelMat(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	//Sphere object 2
	m_sphere2 = new MeshComponent("Sphere");
	m_sphere2->setVertrices(m_read->getVertexPoints());
	m_sphere2->setIndices(m_read->getIndices());
	m_sphere2->setNormals(m_read->getNormals());
	m_sphere2->setUVs(m_read->getTexPoints());
	m_sphere2->setStartPos(glm::vec3(32.0, -33.0, 0.0));
	m_sphere2->Load(m_programHandle);
	m_sphere2->translateModelMat(m_sphere2->getStartPos());
	m_sphere2->scaleModelMat(glm::vec3(7));
	m_sphere2->rotateModelMat(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	
	//Creating cone
	m_cone = new MeshComponent("Cone");
	m_read->resetData();
	m_read->ReadFile("resources/obj/simplecone.obj");
	m_cone->setVertrices(m_read->getVertexPoints());
	m_cone->setIndices(m_read->getIndices());
	m_cone->setNormals(m_read->getNormals());
	m_cone->setUVs(m_read->getTexPoints());
	m_cone->setStartPos(glm::vec3(30.0, -40.0, 30.0));
	m_cone->Load(m_programHandle);
	m_cone->setTextureUnit(4);
	m_cone->loadTexture("resources/textures/pattern2.png");
	m_cone->translateModelMat(m_cone->getStartPos());
	m_cone->scaleModelMat(glm::vec3(9));

	//Creating torus 
	m_torus = new MeshComponent("Torus");
	m_read->resetData();
	m_read->ReadFile("resources/obj/torus.obj");
	m_torus->setVertrices(m_read->getVertexPoints());
	m_torus->setIndices(m_read->getIndices());
	m_torus->setNormals(m_read->getNormals());
	m_torus->setUVs(m_read->getTexPoints());
	m_torus->setStartPos(glm::vec3(0.0, -31.0, -30.0));
	m_torus->Load(m_programHandle);
	m_torus->setTextureUnit(5);
	m_torus->loadTexture("resources/textures/pattern2.png");
	m_torus->translateModelMat(m_torus->getStartPos());
	m_torus->scaleModelMat(glm::vec3(6));


	//Creating another torus 
	m_torus2 = new MeshComponent("Torus");
	m_torus2->setVertrices(m_read->getVertexPoints());
	m_torus2->setIndices(m_read->getIndices());
	m_torus2->setNormals(m_read->getNormals());
	m_torus2->setUVs(m_read->getTexPoints());
	m_torus2->setStartPos(glm::vec3(10.0, -31.0, 10.0));
	m_torus2->Load(m_programHandle);
	m_torus2->translateModelMat(m_torus2->getStartPos());
	m_torus2->scaleModelMat(glm::vec3(6));

	//Creating cylinder
 	m_cylinder = new MeshComponent("Cylinder");
	m_read->resetData();
	m_read->ReadFile("resources/obj/cylinder.obj");
	m_cylinder->setVertrices(m_read->getVertexPoints());
	m_cylinder->setIndices(m_read->getIndices());
	m_cylinder->setNormals(m_read->getNormals());
	m_cylinder->setUVs(m_read->getTexPoints());
	m_cylinder->setStartPos(glm::vec3(-29.0, -32.0, -28.0));
	m_cylinder->Load(m_programHandle);
	m_cylinder->setTextureUnit(6);
	m_cylinder->loadTexture("resources/textures/pattern5.png");
	m_cylinder->translateModelMat(m_cylinder->getStartPos());
	m_cylinder->scaleModelMat(glm::vec3(8));
	m_cylinder->rotateModelMat(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	//Creating another cylinder
	m_cylinder2 = new MeshComponent("Cylinder");
	m_cylinder2->setVertrices(m_read->getVertexPoints());
	m_cylinder2->setIndices(m_read->getIndices());
	m_cylinder2->setNormals(m_read->getNormals());
	m_cylinder2->setUVs(m_read->getTexPoints());
	m_cylinder2->setStartPos(glm::vec3(0.0, -34.0, 28.0));
	m_cylinder2->Load(m_programHandle);
	m_cylinder2->translateModelMat(m_cylinder2->getStartPos());
	m_cylinder2->scaleModelMat(glm::vec3(6));
	m_cylinder2->rotateModelMat(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	//Creating stars
	m_star = new MeshComponent("Star");
	m_read->resetData();
	m_read->ReadFile("resources/obj/star.obj");
	m_star->setVertrices(m_read->getVertexPoints());
	m_star->setIndices(m_read->getIndices());
	m_star->setNormals(m_read->getNormals());
	m_star->setUVs(m_read->getTexPoints());
	m_star->setStartPos(glm::vec3(-30.0, -35.0, -38.0));
	m_star->Load(m_programHandle);
	m_star->setTextureUnit(8);
	m_star->loadTexture("resources/textures/marble.png");
	m_star->translateModelMat(m_star->getStartPos());
	m_star->scaleModelMat(glm::vec3(0.5,0.5,1));
	m_star->rotateModelMat(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	m_star2 = new MeshComponent("Star");
	m_star2->setVertrices(m_read->getVertexPoints());
	m_star2->setIndices(m_read->getIndices());
	m_star2->setNormals(m_read->getNormals());
	m_star2->setUVs(m_read->getTexPoints());
	m_star2->setStartPos(glm::vec3(32.0, -35.0, -38.0));
	m_star2->Load(m_programHandle);
	m_star2->translateModelMat(m_star2->getStartPos());
	m_star2->scaleModelMat(glm::vec3(0.5, 0.5, 1));
	m_star2->rotateModelMat(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	m_star3 = new MeshComponent("Star");
	m_star3->setVertrices(m_read->getVertexPoints());
	m_star3->setIndices(m_read->getIndices());
	m_star3->setNormals(m_read->getNormals());
	m_star3->setUVs(m_read->getTexPoints());
	m_star3->setStartPos(glm::vec3(-25.0, -35.0, 36.0));
	m_star3->Load(m_programHandle);
	m_star3->translateModelMat(m_star3->getStartPos());
	m_star3->scaleModelMat(glm::vec3(0.5, 0.5, 1));
	m_star3->rotateModelMat(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	m_star4 = new MeshComponent("Star");
	m_star4->setVertrices(m_read->getVertexPoints());
	m_star4->setIndices(m_read->getIndices());
	m_star4->setNormals(m_read->getNormals());
	m_star4->setUVs(m_read->getTexPoints());
	m_star4->setStartPos(glm::vec3(-34.0, -32.0, 30.0));
	m_star4->Load(m_programHandle);
	m_star4->translateModelMat(m_star4->getStartPos());
	m_star4->scaleModelMat(glm::vec3(1, 1, 1));
	m_star4->rotateModelMat(90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	
	//Clears the data being read in from OBJ files
	m_read->resetData();

	//Putting the objects into a containter to traverse through
	m_objects.push_back(m_box);
	m_objects.push_back(m_cone);
	m_objects.push_back(m_cylinder);
	m_objects.push_back(m_rubix);
	m_objects.push_back(m_sphere);
	m_objects.push_back(m_torus);
	m_objects.push_back(m_torus2);
	m_objects.push_back(m_star);
	m_objects.push_back(m_star2);
	m_objects.push_back(m_star3);
	m_objects.push_back(m_star4);
	m_objects.push_back(m_cylinder2);
	m_objects.push_back(m_box2);
	m_objects.push_back(m_sphere2);
}

//!< Render mesh objects
void BaseGame::render(CameraComponent& camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	switch (m_cGameState)
	{
		case 0:
			//Splash screen state
			m_menuShader->setUseShader();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), true);
			m_splashScreenComponent->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE0);
			gl::BindTexture(gl::TEXTURE_2D, m_splashScreenComponent->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "tex"), m_splashScreenComponent->getTextureUnit());
			m_splashScreenComponent->draw();
			
		break;
		
		case 1:
			//Use menu shader
			m_menuShader->setUseShader();

			//Menu Screen state
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bSplashScreenState"), false);

			//Start Buttons
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbuttontexture"), true);
			m_buttonStart->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE2);
			gl::BindTexture(gl::TEXTURE_2D, m_buttonStart->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "buttontex"), m_buttonStart->getTextureUnit());
			m_buttonStart->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbuttontexture"), false);

			//Exit Button
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bexitButton"), true);
			m_buttonExit->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE3);
			gl::BindTexture(gl::TEXTURE_2D, m_buttonExit->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "exitButtonTex"), m_buttonExit->getTextureUnit());
			m_buttonExit->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bexitButton"), false);

			//Instruction Button
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bmoreButton"), true);
			m_buttonInstruction->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE4);
			gl::BindTexture(gl::TEXTURE_2D, m_buttonInstruction->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "moreButtonTex"), m_buttonInstruction->getTextureUnit());
			m_buttonInstruction->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bmoreButton"), false);
			
			//Menu
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bMenu"), true);
			m_menuScreenComponent->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE1);
			gl::BindTexture(gl::TEXTURE_2D, m_menuScreenComponent->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "menutexture"), m_menuScreenComponent->getTextureUnit());
			m_menuScreenComponent->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bMenu"), false);
		break;
		
		case 2:		
		//Simulation game state
		//Tells the shader not to render the splash screen or menu screen
		m_programHandle = m_lightingShader->getProgramHandle();
		m_lightingShader->setUseShader();

		//Setting up lighting sending the program handle and the cameras position
		m_generalLight->setLightingParam(m_programHandle, camera);
		gl::Uniform3f(gl::GetUniformLocation(m_programHandle, "cameraPosition"), camera.position().x, camera.position().y, camera.position().z);
		//The first light is always following the robot
		gl::Uniform3f(gl::GetUniformLocation(m_programHandle, "light[0].position"), m_robot->getStartPos().x, m_robot->getStartPos().y-10, m_robot->getStartPos().z);

		//Room
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), true);
		m_room->updateModelMatrix(camera, m_programHandle);
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, m_room->getTextureObject()->getTextureId());
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "cube_texture"), m_room->getTextureUnit());
		m_room->draw();
		gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "drawRcube"), false);
		
		
		if (m_rubix->isDrawable())
		{
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawRubix"), true);
			m_rubix->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE1);
			gl::BindTexture(gl::TEXTURE_2D, m_rubix->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "cube_texture2"), m_rubix->getTextureUnit());
			m_rubix->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawRubix"), false);
		}
	
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawPattern"), true);
			gl::ActiveTexture(gl::TEXTURE2);
			gl::BindTexture(gl::TEXTURE_2D, m_box->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "cube_texture3"), m_box->getTextureUnit());
			
			if (m_box->isDrawable())
			{
				m_box->updateModelMatrix(camera, m_programHandle);
				m_box->draw();
			}

			if (m_box2->isDrawable()) 
			{
				m_box2->updateModelMatrix(camera, m_programHandle);
				m_box2->draw();
			}

			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bDrawPattern"), false);
				
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bsphere"), true);
			gl::ActiveTexture(gl::TEXTURE3);
			gl::BindTexture(gl::TEXTURE_2D, m_sphere->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "spheretexture"), m_sphere->getTextureUnit());
			
			if (m_sphere->isDrawable())
			{
				m_sphere->updateModelMatrix(camera, m_programHandle);
				m_sphere->draw();
			}

			if (m_cylinder2->isDrawable())
			{
				m_cylinder2->updateModelMatrix(camera, m_programHandle);
				m_cylinder2->draw();
			}

			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bsphere"), false);
		
		 if (m_cone->isDrawable())
		{
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bsphere"), true);
			m_cone->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE4);
			gl::BindTexture(gl::TEXTURE_2D, m_cone->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "spheretexture"), m_cone->getTextureUnit());
			m_cone->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bsphere"), false);
		}
		 	
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "btorus"), true);
			gl::ActiveTexture(gl::TEXTURE5);
			gl::BindTexture(gl::TEXTURE_2D, m_torus->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "torusTexture"), m_torus->getTextureUnit());
			
			if (m_torus->isDrawable())
			{
				m_torus->updateModelMatrix(camera, m_programHandle);
				m_torus->draw();
			}

			if (m_torus2->isDrawable())
			{
				m_torus2->updateModelMatrix(camera, m_programHandle);
				m_torus2->draw();
			}

			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "btorus"), false);
		
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bcylinder"), true);		
			gl::ActiveTexture(gl::TEXTURE6);
			gl::BindTexture(gl::TEXTURE_2D, m_cylinder->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "cylinderTexture"), m_cylinder->getTextureUnit());
			
			if (m_cylinder->isDrawable())
			{
				m_cylinder->updateModelMatrix(camera, m_programHandle);
				m_cylinder->draw();
			}

			if (m_sphere2->isDrawable()) 
			{
				m_sphere2->updateModelMatrix(camera, m_programHandle);
				m_sphere2->draw();
			}

			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bcylinder"), false);
		
			//Draw robot
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bRobot"), true);
			gl::ActiveTexture(gl::TEXTURE7);
			gl::BindTexture(gl::TEXTURE_CUBE_MAP, m_robot->getCubeMapTexture());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "robotTexture"), m_robot->getTextureUnit());
			m_robot->drawRobot(camera, m_programHandle);
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bRobot"), false);

			//Stars
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bStar"), true);
			gl::ActiveTexture(gl::TEXTURE8);
			gl::BindTexture(gl::TEXTURE_2D, m_star->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "starTexture"), m_star->getTextureUnit());

			if (m_star->isDrawable())
			{
				m_star->updateModelMatrix(camera, m_programHandle);
				m_star->draw();
			}
			
			if (m_star2->isDrawable())
			{
				m_star2->updateModelMatrix(camera, m_programHandle);
				m_star2->draw();
			}

			if (m_star3->isDrawable())
			{
				m_star3->updateModelMatrix(camera, m_programHandle);
				m_star3->draw();
			}

			if (m_star4->isDrawable())
			{
				m_star4->updateModelMatrix(camera, m_programHandle);
				m_star4->draw();
				
			}
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bStar"), false);
			break;

		case 3:
			//Controls state
			//Back button
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbackbutton"), true);
			m_backButton->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE6);
			gl::BindTexture(gl::TEXTURE_2D, m_backButton->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "buttonBackTex"), m_backButton->getTextureUnit());
			m_backButton->draw();
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bbackbutton"), false);

			//Controls screen
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "bcontrolScreen"), true);
			m_instructionsComponent->updateModelMatrix(camera, m_programHandle);
			gl::ActiveTexture(gl::TEXTURE5);
			gl::BindTexture(gl::TEXTURE_2D, m_instructionsComponent->getTextureObject()->getTextureId());
			gl::Uniform1i(gl::GetUniformLocation(m_programHandle, "controlTex"), m_instructionsComponent->getTextureUnit());
			m_instructionsComponent->draw();
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