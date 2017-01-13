/*!
* @file main.cpp
\brief The entry for the program
*/
#include "XMLReader.h"
#include "Engine.h"

int main(int argc, char *argv[])
{
	//Create and initalize the engine	
	Engine* m_coreEngine = new Engine();

	//Start the Engine
	m_coreEngine->start();
}

