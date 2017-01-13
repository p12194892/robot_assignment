#include "XMLReader.h"
#include <iostream>
#include <string>

//!< Default Constructor
XMLReader::XMLReader()
{
}

//!< Reader for Window attributes
SuccessEnum XMLReader::readWindowAttributes(const char* cfile)
{
	//Creating storage container to store XML data
	TiXmlDocument doc(cfile);
	bool eResult = doc.LoadFile();

	//If the parser didn't load the file properly 
	if (eResult == false)
	{
		//std::cout << "Error loading XML file" << std::endl;
		return FAILURE;
	}

	//doc holds all the xml data
	TiXmlElement *root = doc.FirstChildElement();
	if (root == NULL)
	{
		std::cout << "No root element" << std::endl;
		doc.Clear();
		return FAILURE;
	}

	//Loops over the elements which are children of the root
	TiXmlElement *l_pPeople = root->FirstChildElement("Window");
	if( NULL != l_pPeople)
	{
		TiXmlElement  *l_pPerson = l_pPeople->FirstChildElement("Size");
		while (l_pPerson)
		{
			TiXmlElement  *name = l_pPerson->FirstChildElement("Name");
			if (NULL != name)
			{
				std::string s(name->GetText());
				m_xmlData.push_back(s);
			}

			TiXmlElement  *height = l_pPerson->FirstChildElement("Height");
			if (NULL != height)
			{
				std::string s(height->GetText());
				m_xmlData.push_back(s);
			}
			TiXmlElement  *width = l_pPerson->FirstChildElement("Width");
			if (NULL != width)
			{
				std::string s(width->GetText());
				m_xmlData.push_back(s);
			}
			l_pPerson = l_pPerson->NextSiblingElement("Size");
		}
	}
	doc.Clear();
	return SUCCESS;	
}

//!< Intelligent data parser which sorts through the data in appropriate formats *TO-DO*
void XMLReader::parseData()
{
	//Parse the data depending on the type?
	//Would we have floats? ints? string arrays?
	//Unsure of this to make it generic 
	//????
}

//!< Returns the xml data 
std::vector<std::string> XMLReader::getData()
{
	return m_xmlData;
}

//!< Resets the data stored in the xml
void XMLReader::resetData()
{
	m_xmlData.clear();
}

//!< Reader for Game Objects attributes *TO-DO*
SuccessEnum XMLReader::readGameObjectAttributes(const char* cfile)
{

}

	


	

