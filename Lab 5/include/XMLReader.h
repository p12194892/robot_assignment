#pragma once
/*!
* @file XMLReader.h
* Header file containing tinyXML library elements to read in XML files
*/

#define _CRT_SECURE_NO_DEPRECATE
enum SuccessEnum { FAILURE, SUCCESS };
#include <tinyxml.h>
#include <vector>

/*! \class XMLReader
\brief Reads in data in an XML format
*/

//Making the project data driven
class XMLReader
{
	private:
		std::vector<std::string> m_xmlData; //!< Vector which pushes the read in data
	public:
		XMLReader();//!< Default Constructor
		SuccessEnum readGameObjectAttributes(const char* cfile); //!< Reader for Game Objects attributes *TO-DO*
		SuccessEnum readWindowAttributes(const char* cfile); //!< Reader for Window attributes
		void parseData(); //!< Intelligent data parser which sorts through the data in appropriate formats *TO-DO*
		std::vector<std::string> getData(); //!< Returns the xml data 
		void resetData(); //!< Resets the data stored in the xml
};