#include "Engine.h"

Engine::Engine()
{
	std::cout << "Starting Engine" << std::endl << std::endl;

	m_bstartRunning = false;
	m_window = new WindowComponent();
	std::cout << "Window Loaded" << std::endl << std::endl;
}

void Engine::start()
{
	m_bstartRunning = true;

	m_window->init();

	m_window->setRunning(m_bstartRunning);
	
	while (m_window->isRunning())
	{
		m_window->mainLoop();
	}

	if (!m_window->isRunning())
	{
		stop();
	}
}

void Engine::stop()
{
	delete m_window;
	m_bstartRunning = false;
}