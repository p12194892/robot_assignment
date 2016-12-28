#pragma once

/*!
* @file Controller.h
* Header file containing the controller class which controls the state of the simulation
*/

/*! \class Robot
\brief  The controller class which controls the state of the simulation
*/

class Controller
{
	private:
	
	public:
	Controller();
	void init();
	void loadSplash();
	void loadMenu();
	void loadGame();
	//create into a virtual draw for everything
	void draw();
};