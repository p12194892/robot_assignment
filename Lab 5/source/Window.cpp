#include "Window.h"

//!< Default constructor
Window::Window()
{
	//gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;

	//Creates the scene
	m_scene = new GameLogic();
	m_camera = new QuatCamera();
}

//!< Initialize the window
void Window::initWindow()
{
	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);

	// Open the window
	std::string title = "Interpolation Shader";
	m_window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);

	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	//Creates the camera
	m_scene->initScene(*m_camera);
	
	glfwSetWindowUserPointer(m_window, this);

	//Key control
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

}

//!< Keyboard key press user control
void Window::keyPress(int key, int action, int mods, int cancode)
{
	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		if (m_scene)
			m_scene->animate(!(m_scene->animating()));
	//Resets the camera
	if (key == 'R' && action == GLFW_RELEASE)
		m_camera->reset(m_camera->getCameraPositions().at(2), m_camera->getCameraOrientations().at(2));

	//Start button for use of the splash screen
	if (m_scene->getGameState() == 0)
	{
		if (key == GLFW_KEY_SPACE == GLFW_PRESS)
		{
			m_scene->changeGameState(1);
		}
	}

	if (m_scene->getGameState() == 1)
	{
		//Controls for the robot (up, down, right and left)
		if (key == GLFW_KEY_UP == GLFW_PRESS) {
			m_scene->keyPress(true, 'U');
		}

		if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
			m_scene->keyPress(false, 'U');
		}

		if (key == GLFW_KEY_DOWN == GLFW_PRESS) {
			m_scene->keyPress(true, 'W');
		}

		if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
			m_scene->keyPress(false, 'W');
		}
		/*if (key == GLFW_KEY_P == GLFW_PRESS) {
		scene->keyPress(true, 'P');
		}

		if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
		scene->keyPress(false, 'p');
		}

		if (key == GLFW_KEY_O == GLFW_PRESS) {
		scene->keyPress(true, 'O');
		}

		if (key == GLFW_KEY_O && action == GLFW_RELEASE) {
		scene->keyPress(false, 'O');
		}*/

		//Turn the robot around 
		if (key == GLFW_KEY_RIGHT == GLFW_PRESS) {
			m_scene->keyPress(true, 'D');
		}

		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
			m_scene->keyPress(false, 'D');
		}

		//Turn the robot around 
		if (key == GLFW_KEY_LEFT == GLFW_PRESS) {
			m_scene->keyPress(true, 'S');
		}

		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
			m_scene->keyPress(false, 'S');
		}

		//Sets the camera to a low position
		if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
			m_camera->reset(m_camera->getCameraPositions().at(0), m_camera->getCameraOrientations().at(0));
		}

		//Sets the camera to have a top down view
		if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
			m_camera->reset(m_camera->getCameraPositions().at(1), m_camera->getCameraOrientations().at(1));
		}

		//Sets the camera to have a low view
		if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {

		}
	}

}

//!< Scroll mouse user control
void Window::scrollPress(double x, double y)
{
	if (m_scene->getGameState() == 1)
	{
		m_camera->zoom((float)y*0.5f);
	}
}

//!< Keyboard callback 
 void Window::key_callback(GLFWwindow* window, int key, int cancode, int action, int mods)
{
	void* data = glfwGetWindowUserPointer(window);
	Window *test =  static_cast<Window *>(data);
	test->keyPress(key, action, mods, cancode);
}

 //!< Scroll mouse callback
 void Window::scroll_callback(GLFWwindow* window, double x, double y)
 {
	 void* data = glfwGetWindowUserPointer(window);
	 Window *test = static_cast<Window *>(data);
	 test->scrollPress(x, y);
 }
 
 //!< Resizes the camera based on the size of window
 void Window::resizeGL(int w, int h)
 {
	 m_scene->resize(*m_camera, w, h);
 }

 //!< Main loop of the program
 void Window::mainLoop()
 {
	 while (!glfwWindowShouldClose(m_window) && !glfwGetKey(m_window, GLFW_KEY_ESCAPE)) {

		 //Initialize the splash screen here through states

		 update((float)glfwGetTime());
		 m_scene->render(*m_camera);
		 glfwSwapBuffers(m_window); //time!
		 glfwPollEvents();
	 }
 }

 //!< Termination of the program
 void Window::terminate()
 {
	 // Close window and terminate GLFW
	 glfwTerminate();

	 // Exit program
	 exit(EXIT_SUCCESS);
 }

 //!< Obtain the window
 GLFWwindow* Window::getWindow()
 {
	 return m_window;
 }
