/*!
 * @file GameSoundLoader.cpp
 */

#include "SoundLoader.h"
#include <iostream>

//Singleton design pattern
SoundLoader* SoundLoader::m_Instance = NULL;

SoundLoader::SoundLoader()//!< Default constructor
{
	m_sSoundFile.push_back("resources/sounds/bubble.wav");

	for(unsigned int i = 0; i < m_sSoundFile.size(); i++)
	{
		m_SoundBuffer.push_back(new sf::SoundBuffer);
		m_SoundBuffer.at(i) ->loadFromFile(m_sSoundFile.at(i));
		m_Sounds.push_back(new sf::Sound);
		m_Sounds.at(i)->setBuffer(*m_SoundBuffer.at(i));
	}	
}

SoundLoader* SoundLoader::Instance() //!< Instance contructor to ensure that only one GameTextureLoader is created
{
	//if the pointer is pointing to nothing make an instance of a GameSoundLoader
	if (m_Instance == NULL)
	{
		m_Instance = new SoundLoader();
	}

	return m_Instance;
}

sf::Sound* SoundLoader::GetSound(unsigned int iIndex) //!< Gets the sound of the sent index and returns a sound pointer 
{	
	//if guard to protect potential memory leak
	if (iIndex < m_Sounds.size())
		return m_Sounds.at(iIndex);
	
	else
	{
		std::cout<<"Error, the index being sent has no member in the vector";
		return 0;
	}
}
