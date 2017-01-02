/*!
 * @file SoundLoader.h
 * Header file containing the sound loader which loads sounds
 */

#ifndef SOUNDLOADER_H
#define SOUNDLOADER_H

#include <string>
#include <SFML\Audio.hpp>

/*! \class GameSoundLoader
	\brief The sound loader
*/

class SoundLoader
{
	private:
		SoundLoader(); //!< Default constructor
		std::vector<sf::Sound*> m_Sounds; //!< Vector container of sound pointers
		std::vector<sf::SoundBuffer*> m_SoundBuffer; //!< Vector container of SoundBuffer pointers
	    std::vector<std::string> m_sSoundFile; //!< Vector container of strings containing the names of the sound files
		static SoundLoader* m_Instance; //!< Instance pointer of a GameSoundLoader

	public:
		static SoundLoader* Instance(); //!< Instance contructor to ensure that only one GameTextureLoader is created
		sf::Sound* GetSound(unsigned int iIndex/*!Initial index*/);//!< Gets the sound of the sent index and returns a sound pointer 
};
#endif