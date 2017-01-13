#include "WindowComponent.h"

//!< Default constructor
WindowComponent::WindowComponent()
{
	m_textReport = new sf::Text();
	sf::Font* font = new sf::Font();

	if (!font->loadFromFile("./resources/font/arial.ttf"))
	{
		std::cout<<"Error loading font";
	}

	m_textReport->setCharacterSize(30);
	m_textReport->setOutlineColor(sf::Color::Green);
	m_textReport->setPosition(50, 50);
	m_textReport->setFont(*font);
	m_textReport->setStyle(sf::Text::Bold);
	
}

//!< Main loop of the program
 void WindowComponent::mainLoop(XMLReader* s)
 {
	 //Update text reports
	 if (m_baseGame->objectIsErased() == true)
	 {
		 //Returning the string so draw the string to the screen
	/*	 std::string sobjectName = m_baseGame->objectPickedUp();
		 m_textReport->setString(sobjectName);
		 m_window->pushGLStates();
		 m_window->draw(*m_textReport);
		 //Draw the text report to the screen under a timer (maybe 20 seconds?)
		 //Push and pop openGl to draw to the window
		 //m_time = m_clock.getElapsedTime();
		 //After elapsed time set it back to false:

	/*	 sf::Clock clock;
		 clock.restart();

		 sf::Time timer = clock.getElapsedTime();
		 while (timer.asSeconds() != sf::seconds(5).asSeconds())
		 {
			 //do nothing
		 }*/


		
		/* m_window->popGLStates();
		 m_window->display();
		 m_window->setActive();
		 m_baseGame->eraseOject(false);*/
	 }

	//Update the gameloop
	update((float)glfwGetTime());

	//render 
	//Clears the buffer when rendering
	if (m_cameraChangeState == 0)
	{
		m_baseGame->render(*m_Cameras.at(m_cameraChangeState));
	}

	else if (m_cameraChangeState == 1)
	{
		m_baseGame->render(*m_Cameras.at(m_cameraChangeState));
	}
	
	else if (m_cameraChangeState == 2)
	{
		m_baseGame->render(*m_Cameras.at(m_cameraChangeState));
	}
	//Swap buffers
	m_window->display();

	//poll events
	sfEventPoll();

	//Event Driven programming
	//Changes window name and size during run time
	if (s->getData().size() != 0)
	{
		m_window->setTitle(s->getData().at(0));
		m_window->setSize(sf::Vector2u(std::stoi(s->getData().at(1)), std::stoi(s->getData().at(2))));
	}
 }
 //test
 //!< Poll events
 void WindowComponent::sfEventPoll()
 {
	 while (m_window->pollEvent(m_event))
	 {
		 switch (m_event.type)
		 {
		 case sf::Event::Closed:
			 // end the program
			 std::cout << "Closing window" << std::endl << std::endl;
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
			 //Moving Robot Up
			 if (m_event.key.code == sf::Keyboard::Up)
			 {
				 m_baseGame->keyPress(true, 'U');
			 }

			 //Moving Robot Down
			 else if (m_event.key.code == sf::Keyboard::Down)
			 {
				 m_baseGame->keyPress(true, 'W');
			 }

			 //Moving Robot Right
			 else if (m_event.key.code == sf::Keyboard::Right)
			 {
				 m_baseGame->keyPress(true, 'D');
			 }

			 //Moving Robot Left
			 else if (m_event.key.code == sf::Keyboard::Left)
			 {
				 m_baseGame->keyPress(true, 'S');
			 }

			 else if (m_event.key.code == sf::Keyboard::Space)
			 {
				 if (m_baseGame->getGameState() == 0)
				 {
					 m_baseGame->changeGameState(1);
				 }
			 }

			 //Sets the camera to a low position
			 else if (m_event.key.code == sf::Keyboard::Num1)
			 {
				 //activate camera 1
				 if (m_baseGame->getGameState() == 2)
				 {
					 m_cameraChangeState = 2;
				 }
			 }

			 //Sets the camera to have a top down view
			 else if (m_event.key.code == sf::Keyboard::Num2)
			 {
				 if (m_baseGame->getGameState() == 2)
				 {
					 //activate camera 2
					 m_cameraChangeState = 1;
				 }
			 }
			 //Resets the camera
			 else if (m_event.key.code == sf::Keyboard::R)
			 {
				 if (m_baseGame->getGameState() == 2)
				 {
					 m_cameraChangeState = 0;
				 }
			 }
		 }

		 else if (m_event.type == sf::Event::KeyReleased)
		 {
			 if (m_event.key.code == sf::Keyboard::Right)
			 {
				 m_baseGame->keyPress(false, 'D');
			 }

			 else if (m_event.key.code == sf::Keyboard::Left)
			 {
				 m_baseGame->keyPress(false, 'S');
			 }

			 else if (m_event.key.code == sf::Keyboard::Up)
			 {
				 m_baseGame->keyPress(false, 'U');
			 }

			 else if (m_event.key.code == sf::Keyboard::Down)
			 {
				 m_baseGame->keyPress(false, 'W');
			 }
		 }

		 if (m_event.type == sf::Event::MouseWheelMoved)
		 {
			 if (m_baseGame->getGameState() == 2)
			 {
				 m_Cameras.at(m_cameraChangeState)->zoom((float)m_event.mouseWheel.delta*0.5f);
			 }
		 }

		 if (m_event.type == sf::Event::MouseButtonPressed)
		 {
			 if (m_baseGame->getGameState() == 1)
			 {
				 //Setting the state of the game here
				 if (m_event.mouseButton.x > 300 && m_event.mouseButton.x < 500
					 && m_event.mouseButton.y > 140 && m_event.mouseButton.y < 200)
				 {
					 m_baseGame->changeGameState(2);
				 }

				 else if (m_event.mouseButton.x > 300 && m_event.mouseButton.x < 500
					 && m_event.mouseButton.y > 270 && m_event.mouseButton.y < 330)
				 {
					 //Go to the control screen
					 m_baseGame->changeGameState(3);
				 }

				 else if (m_event.mouseButton.x > 300 && m_event.mouseButton.x < 500
					 && m_event.mouseButton.y > 400 && m_event.mouseButton.y < 460)
				 {
					 // end the program - need to stop the engine!
					 std::cout << "Closing window" << std::endl << std::endl;
					 m_bifRunning = false;
					 m_window->close();
					 exit(EXIT_SUCCESS);
				 }
			 }

			else if (m_baseGame->getGameState() == 2)
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

			else if (m_baseGame->getGameState() == 3)
			{
				//Controls menu
				if (m_event.mouseButton.x > 367 && m_event.mouseButton.x < 432
					&& m_event.mouseButton.y > 527 && m_event.mouseButton.y < 590)
				{
					m_baseGame->changeGameState(1);
				}
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

 //! If the window is running 
 bool WindowComponent::isRunning()
 {
	 return m_bifRunning;
 }

 //!< Destructor
 WindowComponent::~WindowComponent()
 {

 }

 //!< Sets if the window is running
 void WindowComponent::setRunning(bool run)
 {
	 m_bifRunning = run;
 }

 //!< Gets the render window
 sf::RenderWindow* WindowComponent::getRenderWindow()
 {
	 return m_window;
 }