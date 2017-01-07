#include "Button.h"

Button::Button()
{
	m_buttonShape.setPosition(10, 10);
	m_buttonShape.setSize(sf::Vector2f(20, 20));
	m_buttonShape.setFillColor(sf::Color::Yellow);
	m_buttonText.setPosition(m_buttonShape.getPosition());
	//m_buttonText.setColor(sf::Color::Red);
	m_buttonText.setCharacterSize(10);
}

Button::Button(float xpos, float ypos, float w, float h)
{
	m_buttonShape.setPosition(xpos, ypos);
	m_buttonShape.setSize(sf::Vector2f(w, h));
	m_buttonShape.setFillColor(sf::Color::Yellow);
	m_buttonText.setPosition(m_buttonShape.getPosition());
//	m_buttonText.setColor(sf::Color::Red);
	m_buttonText.setCharacterSize(10);
}
