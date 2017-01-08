/*!
 * @file SoundLoader.h
 * Header file containing the sound loader which loads sounds
 */

#ifndef SoundComponent_H
#define SoundComponent_H

#include <string>
#include <SFML\Audio.hpp>

/*! \class SoundComponent
	\brief The sound loader
*/

class SoundComponent
{
	private:
		SoundComponent(); //!< Default constructor
		std::vector<sf::Sound*> m_Sounds; //!< Vector container of sound pointers
		std::vector<sf::SoundBuffer*> m_SoundBuffer; //!< Vector container of SoundBuffer pointers
	    std::vector<std::string> m_sSoundFile; //!< Vector container of strings containing the names of the sound files
		static SoundComponent* m_Instance; //!< Instance pointer of a GameSoundLoader

	public:
		static SoundComponent* Instance(); //!< Instance contructor to ensure that only one GameTextureLoader is created
		sf::Sound* GetSound(unsigned int iIndex/*!Initial index*/);//!< Gets the sound of the sent index and returns a sound pointer 
};
#endif