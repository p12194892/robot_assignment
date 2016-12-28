#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include "scene.h"
#include "CubeMapScene.h"
#include "QuatCamera.h"
#include "splashScreen.h"
#include <string>

//MAC Includes & Linux //Cannot test due to the emulator not working on my laptop
#ifdef __APPLE__
#include <GLFW/glfw3.h>
#else
#ifdef _WIN32
#include <windows.h>
#include <GLFW/glfw3.h>
#endif
#endif

using std::string;

#define MOVE_VELOCITY 0.01f
#define ROTATE_VELOCITY 0.00001f

//The Scene
CubeMapScene *scene;

//The GLFW Window
GLFWwindow *window;

//The camera
QuatCamera camera;

//Splash Screen
//SplashScreen *ss;

//To keep track of cursor location
double lastCursorPositionX, lastCursorPositionY, cursorPositionX, cursorPositionY;

/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function for keypress use to toggle animate (not used at the moment)
// and to check for R to reset camera
/////////////////////////////////////////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int cancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_RELEASE)
		if (scene)
			scene->animate(!(scene->animating()));
	//Resets the camera
	if (key == 'R' && action == GLFW_RELEASE)
		camera.reset();

	//Start button for use of the splash screen
	if (scene->getGameState() == 0)
	{
		if (key == GLFW_KEY_SPACE == GLFW_PRESS)
		{
			scene->changeGameState(1);
		}
	}

	if (scene->getGameState() == 1)
	{
		//Controls for the robot (up, down, right and left)
		if (key == GLFW_KEY_UP == GLFW_PRESS) {
			scene->keyPress(true, 'U');
		}

		if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
			scene->keyPress(false, 'U');
		}

		if (key == GLFW_KEY_DOWN == GLFW_PRESS) {
			scene->keyPress(true, 'W');
		}

		if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
			scene->keyPress(false, 'W');
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
			scene->keyPress(true, 'D');
		}

		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
			scene->keyPress(false, 'D');
		}

		//Turn the robot around 
		if (key == GLFW_KEY_LEFT == GLFW_PRESS) {
			scene->keyPress(true, 'S');
		}

		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
			scene->keyPress(false, 'S');
		}

		//Second fixed camera that follows the robot around
		if (key == GLFW_KEY_F && action == GLFW_RELEASE) {

		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function when mouse wheel is scrolled
/////////////////////////////////////////////////////////////////////////////////////////////
void scroll_callback(GLFWwindow *window, double x, double y)
{
	camera.zoom((float)y*0.5f);
}



////////////////////////////////////////////////////////
//////  Create the scene and initialise ////////////////
////////////////////////////////////////////////////////
void initializeGL() {
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;

	//Creates the scene
	scene = new CubeMapScene();

	//Creates the camera
	scene->initScene(camera);

}


/////////////////////////////////////////////////////////////////////////////////////////////
// Update
/////////////////////////////////////////////////////////////////////////////////////////////
void update(float t)
{

	//Get the current cursor position
	glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);

	//See how much the cursor has moved
	float deltaX = (float)(lastCursorPositionX - cursorPositionX);
	float deltaY = (float)(lastCursorPositionY - cursorPositionY);
	
	//Find out where the user is clicking on the window 
	//scene->buttonPress(cursorPositionX, cursorPositionY);

	//Need to disable the camera features when in the splash screen state
	if (scene->getGameState() == 1)
	{
		//Using a different way (i.e. instead of callback) to check for LEFT mouse button
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			//std::cout << "Left button \n";
			//Rotate the camera. The 0.001f is a velocity mofifier to make the speed sensible

			//	std::cout <<"deltaX " << deltaX << " deltaY " << deltaY << "\n";

			camera.rotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY);

		}

		//Using a different way (i.e. instead of callback) to check for RIGHT mouse button
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			//std::cout << "Right button \n";
			//Rotate the camera. The 0.01f is a velocity mofifier to make the speed sensible
			camera.pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY);

		}
		//To adjust Roll with MIDDLE mouse button
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
		{

			camera.roll(deltaX*ROTATE_VELOCITY);

		}

		//Store the current cursor position
		lastCursorPositionX = cursorPositionX;
		lastCursorPositionY = cursorPositionY;
		scene->update((float)glfwGetTime(), camera);
	}
}


////////////////////////////////////////////////////////
/////// Main loop  /////////////////////////////////////
////////////////////////////////////////////////////////
void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {

		//Initialize the splash scree here through states

		update((float)glfwGetTime());
		scene->render(camera);
		glfwSwapBuffers(window); //time!
		glfwPollEvents();
	}
}

///////////////////////////////////////////////////////
//// resize ///////////////////////////////////////////
///////////////////////////////////////////////////////
void resizeGL(QuatCamera camera,int w, int h) {
	scene->resize(camera, w, h);
}

///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char *argv[])
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
	string title = "Interpolation Shader";
	window = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);



	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Initialization
	initializeGL();
	resizeGL(camera, 800, 600);

	//Key control
	glfwSetKeyCallback(window, key_callback);

	// Enter the main loop for the program
	mainLoop();



	//Disable camera
	if (scene->getGameState() == 1)
	{
		//Scroll callback
		glfwSetScrollCallback(window, scroll_callback);//Set callback}

	}

	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}

