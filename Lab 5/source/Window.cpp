#include "Window.h"

//!< Default constructor
Window::Window()
{
	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;

	//Creates the scene
	m_scene = new GameLogic();

	//SFML window
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Robot Simulation", sf::Style::Default, sf::ContextSettings(64));
	m_bifRunning = true;	
}

//!< Initialize the window
void Window::initWindow()
{

	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
	//Claen up and abort
	glfwTerminate();
	exit(EXIT_FAILURE);
	}

	gl::Enable(gl::DEPTH_TEST);
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	
	m_scene->initScene(m_camera);

}
 
 //!< Resizes the camera based on the size of window
 void Window::resizeGL(int w, int h)
 {
	 m_scene->resize(m_camera, w, h);
 }

 //!< Main loop of the program
 void Window::mainLoop()
 {
	 while (m_bifRunning)
	 {
		 //Update the gameloop
		 update((float)glfwGetTime());

		 //render 
		 m_scene->render(m_camera);
		 
		 //Swap buffers
		 m_window->display();

		 //poll events
		 sfEventPoll();
	 }
 }

 //!< Poll events
 void Window::sfEventPoll()
 {
	 while (m_window->pollEvent(m_event))
	 {
		 switch (m_event.type)
		 {
		 case sf::Event::Closed:
			 // end the program
			 m_bifRunning = false;
			 m_window->close();
			 exit(EXIT_SUCCESS);
			 break;

		 case sf::Event::Resized:
			 // adjust the viewport when the window is resized
			 gl::Viewport(0, 0, m_event.size.width, m_event.size.height);
			 break;
		 }

		 //Key Presses
		 if (m_event.type == sf::Event::KeyPressed)
		 {
			 if (m_event.key.code == sf::Keyboard::E)
			 {
				 if (m_scene)
					 m_scene->animate(!(m_scene->animating()));
			 }

			 //Moving Robot Up
			 else if (m_event.key.code == sf::Keyboard::Up)
			 {
				 m_scene->keyPress(true, 'U');
			 }

			 //Moving Robot Down
			 else if (m_event.key.code == sf::Keyboard::Down)
			 {
				 m_scene->keyPress(true, 'W');
			 }

			 //Moving Robot Right
			 else if (m_event.key.code == sf::Keyboard::Right)
			 {
				 m_scene->keyPress(true, 'D');
			 }

			 //Moving Robot Left
			 else if (m_event.key.code == sf::Keyboard::Left)
			 {
				 m_scene->keyPress(true, 'S');
			 }

			 else if (m_event.key.code == sf::Keyboard::Space)
			 {
				 if (m_scene->getGameState() == 0)
				 {
					 m_scene->changeGameState(1);
				 }
			 }

			 //Resets the camera
			 else if (m_event.key.code == sf::Keyboard::R)
			 {
				 m_camera.reset(m_camera.getCameraPositions().at(2), m_camera.getCameraOrientations().at(2));
			 }

			 //Sets the camera to a low position
			 else if (m_event.key.code == sf::Keyboard::Num1)
			 {
				 m_camera.reset(m_camera.getCameraPositions().at(0), m_camera.getCameraOrientations().at(0));
			 }

			 //Sets the camera to have a top down view
			 else if (m_event.key.code == sf::Keyboard::Num2)
			 {
				 m_camera.reset(m_camera.getCameraPositions().at(1), m_camera.getCameraOrientations().at(1));
			 }
		 }

		 else if (m_event.type == sf::Event::KeyReleased)
		 {
			 if (m_event.key.code == sf::Keyboard::Right)
			 {
				 m_scene->keyPress(false, 'D');
			 }

			 else if (m_event.key.code == sf::Keyboard::Left)
			 {
				 m_scene->keyPress(false, 'S');
			 }

			 else if (m_event.key.code == sf::Keyboard::Up)
			 {
				 m_scene->keyPress(false, 'U');
			 }

			 else if (m_event.key.code == sf::Keyboard::Down)
			 {
				 m_scene->keyPress(false, 'W');
			 }
		 }

		 if (m_event.type == sf::Event::MouseWheelMoved)
		 {
			 m_camera.zoom((float)m_event.mouseWheel.delta*0.5f);
		 }


		 if (m_event.type == sf::Event::MouseButtonPressed)
		 {
			 if (m_event.mouseButton.button == sf::Mouse::Left)
			 {
				 m_ckeyPress = 'L';
			 }

			 else if (m_event.mouseButton.button == sf::Mouse::Right)
			 {
				 m_ckeyPress = 'R';
			 }

			 else if (m_event.mouseButton.button == sf::Mouse::Middle)
			 {
				 m_ckeyPress = 'M';
			 }
		 }

		 if (m_event.type == sf::Event::MouseButtonReleased)
		 {
			 if (m_event.mouseButton.button == sf::Mouse::Left)
			 {
				 m_ckeyPress = '/';
			 }

			 else if (m_event.mouseButton.button == sf::Mouse::Right)
			 {
				 m_ckeyPress = '/';
			 }

			 else if (m_event.mouseButton.button == sf::Mouse::Middle)
			 {
				 m_ckeyPress = '/';
			 }
		 }
	 }
 }
 