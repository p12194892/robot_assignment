#pragma once
/*!
* @file Engine.h
* Header file The game engine 
*/

#include "WindowComponent.h"

/*! \class Engine
\brief The core game engine
*/

class Engine
{
	private:
		bool m_bstartRunning; //!< Starts the engine
		WindowComponent* m_window; //!< Creates the window
		XMLReader* m_read; //!< XML reader to read in init virtual functions (Event Driven)
	public:
		Engine(); //!< Default constructor
		void start(); //!< Starts engine
		void stop(); //!< Stops engine
};