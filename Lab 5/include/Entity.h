#pragma once
/*!
* @file Entity.h
* Header file An object that includes virtual functions where components can inherit from
*/

#include "XMLReader.h"
#include <string>
#include <vector>

/*! \class Entity
\brief An object that includes virtual functions where components can inherit from
*/

class Entity
{
	public:
		virtual void init(XMLReader* s) {} //!< Takes an XML reader which reads in object data for components
		virtual void init() {} //!< Initalize function
		virtual void update(float t) {} //!< Update function
		virtual void update() {} //!< Overload of the update function
};