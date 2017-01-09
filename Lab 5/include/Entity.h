#pragma once
/*!
* @file Entity.h
* Header file An object that includes virtual functions where components can inherit from
*/

/*! \class Entity
\brief An object that includes virtual functions where components can inherit from
*/
class Entity
{
	public:
		virtual void init() {} //!< Initalize function
		virtual void update(float t) {} //!< Update function
		virtual void update() {} //!< Overload of the update function

		//virtual void render(CameraComponent camera);
};