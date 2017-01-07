/*!
* @file Scene.h
* Header file abstract scene class
*/

#ifndef SCENE_H
#define SCENE_H
#include "QuatCamera.h"

/*! \class Scene
\brief virtual scene for rendering, animating and updating the main simulation
*/
class Scene
{
protected:
	bool m_animate; //!< If the scene is animating

public:
	Scene() : m_animate(true) { }

	/**
	Load textures, initialize shaders, etc.
	*/
	virtual void initScene(QuatCamera camera) = 0;

	/**
	This is called prior to every frame.  Use this
	to update your animation.
	*/
	virtual void update(float t, QuatCamera camera) = 0;

	/**
	Draw your scene.
	*/
	virtual void render(QuatCamera camera) = 0;

	/**
	Called when screen is resized
	*/
	virtual void resize(QuatCamera camera, int, int) = 0;

	void animate(bool value) { m_animate = value; }
	bool animating() { return m_animate; }

};

#endif // SCENE_H
