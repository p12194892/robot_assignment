#include "Engine.h"

//!< Default constructor
Engine::Engine()
{
	std::cout << "Starting Engine" << std::endl << std::endl;

	m_bstartRunning = false;
	m_window = new WindowComponent();
	//Work on this in the labs
	m_read = new XMLReader();
	m_read->readWindowAttributes("resources/xml/data.xml");
}

//!< Starts engine
void Engine::start()
{
	m_bstartRunning = true;
	
	//Initiate data here from XML reader using the overload virtual function
	m_window->init(m_read);
	m_window->setRunning(m_bstartRunning);
	while (m_window->isRunning())
	{
		m_read->readWindowAttributes("resources/xml/data.xml");
		m_window->mainLoop(m_read);
		m_read->resetData();
	}

	if (!m_window->isRunning())
	{
		stop();
	}
}

//!< Stops engine
void Engine::stop()
{
	delete m_window;
	m_bstartRunning = false;
}