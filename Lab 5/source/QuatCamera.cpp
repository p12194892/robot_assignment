#define _USE_MATH_DEFINES
#include <cmath>


#include "QuatCamera.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include "defines.h"
#include <iostream>

//World coordinate System Axes
const glm::vec3 WORLDX = glm::vec3(1,0,0);
const glm::vec3 WORLDY = glm::vec3(0,1,0);
const glm::vec3 WORLDZ = glm::vec3(0,0,1);


/////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////////////
	QuatCamera::QuatCamera() 
	{
		reset(glm::vec3(-2.0f, -27.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//Positions of various cameras
		m_cameraPositions.push_back(glm::vec3(-20.0f, -38.0f, 31.0f));
		m_cameraPositions.push_back(glm::vec3(2.22959f, -38.30103f, -0.91515f));
		m_cameraPositions.push_back(glm::vec3(-2.0f, -27.0f, 20.0f));
		//Orientations of various cameras
		m_cameraOrientations.push_back(glm::vec3(-0.0147318f, -0.323816f, -0.00558566f));
		m_cameraOrientations.push_back(glm::vec3(0.511735f, 0.00128345f, 0.00129044f));
		m_cameraOrientations.push_back(glm::vec3(0.0f, 0.0f, 0.0f));


	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the position
/////////////////////////////////////////////////////////////////////////////////////////////
	const glm::vec3& QuatCamera::position() const
	{
		return _position;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the position
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setPosition(const glm::vec3& position)
	{
		_position = position;
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Get the fieldOfView
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::fieldOfView() const
	{
		return _fieldOfView;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the fieldOfView
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setFieldOfView(float fieldOfView)
	{
		assert(fieldOfView>0.0f && fieldOfView <180.0f);
		_fieldOfView = fieldOfView;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the aspectRatio
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::aspectRatio() const
	{
		return _aspectRatio;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Set the aspectRatio
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setAspectRatio(float aspectRatio)
	{
		assert(aspectRatio >0.0f);
		_aspectRatio = aspectRatio;
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Get the nearPlane
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::nearPlane() const
	{
		return _nearPlane;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Get the far Plane
/////////////////////////////////////////////////////////////////////////////////////////////
	float QuatCamera::farPlane() const
	{
		return _farPlane;
	}

	
/////////////////////////////////////////////////////////////////////////////////////////////
// Set the nearPlane and the farPlane
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::setNearAndFarPlanes(float nearPlane, float farPlane)
	{
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		_nearPlane = nearPlane;
		_farPlane = farPlane;
	}

///////////////////////////////////////////////////////////////////////////////////////////
// Generate a quaternion from axis and rotation angle in radians
//This is to construct the rotation quaternion
////////////////////////////////////////////////////////////////////////////////////////////

	glm::quat fromAxisAngle(glm::vec3 axis, float angle)
	{
		//conversion from axis-angle
		//GLM must have an angle in degress so convert it
		//Created a quaternion
		glm::quat rotation;
		rotation = glm::angleAxis(glm::degrees(angle), axis);
	

		return rotation;

	}

/////////////////////////////////////////////////////////////////////////////////////////////
//Rotate the camera
//Orient according to required pitch and yaw
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::rotate(const float yaw, const float pitch)
	{
		_orientation = glm::normalize(fromAxisAngle(WORLDX, pitch)*_orientation);
	
		_orientation = glm::normalize(_orientation * fromAxisAngle(WORLDY, yaw));	
		std::cout << "orientation x: " << _orientation.x << std::endl << std::endl;
		std::cout << "orientation y: "<< _orientation.y << std::endl << std::endl;
		std::cout << "orientation z: " << _orientation.z << std::endl << std::endl;
		updateView();
	}

	
/////////////////////////////////////////////////////////////////////////////////////////////
// Pan the camera
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::pan(const float x, const float y)
	{
		
		_position += _xaxis * x;
		_position += _yaxis * -y;
		std::cout << "Position x: " << _position.x << std::endl << std::endl;
		std::cout << "Position y: " << _position.y << std::endl << std::endl;
		//Now call update()
		updateView();
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Zoom the camera
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::zoom(const float z)
	{

		_position += _zaxis * z;
		std::cout << "Position z: " << _position.z << std::endl << std::endl;

		//Now call updateView()
		updateView();

	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update the camera view
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::updateView()
	{
		//Construct the view matrix from orientation quaternion and position vector

		//First get the matrix from the 'orientaation' Quaternion
		//This deals with the rotation and scale part of the view matrix
		_view = glm::mat4_cast(_orientation); // Rotation and Scale

		//Extract the camera coordinate axes from this matrix
		_xaxis = glm::vec3(_view[0][0],_view[0][1],_view[0][2]);
		_yaxis = glm::vec3(_view[1][0],_view[1][1],_view[1][2]);
		_zaxis = glm::vec3(_view[2][0],_view[2][1],_view[2][2]);

		//And use this and current camera position to set the translate part of the view matrix
		_view[3][0] = -glm::dot(_xaxis,_position); //Translation x
		_view[3][1] = -glm::dot(_yaxis,_position); //Translation y
		_view[3][2] = -glm::dot(_zaxis,_position); //Translation z
	
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the Up
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::roll(const float z)
	{
		_orientation = glm::normalize(fromAxisAngle(WORLDZ, z) *_orientation);
		updateView();
	}


/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the camera
/////////////////////////////////////////////////////////////////////////////////////////////
	void QuatCamera::reset(glm::vec3 pos, glm::vec3 ori)
	{
		//Initialise camera axes
		_xaxis = WORLDX;
		_yaxis = WORLDY;
		_zaxis = WORLDZ;

		//Initialise camera position 
		_position = pos;

		//Initialise the orientation
		_orientation = glm::quat(1.0,0.0,0.0,0.0);
		_orientation.x = ori.x;
		_orientation.y = ori.y;
		_orientation.z = ori.z;

		//Initialise camera perspective parameters
		_fieldOfView = glm::radians(50.0f);
		_nearPlane = 0.01f;
		_farPlane = 100.0f;
		_aspectRatio = 4.0f/3.0f;

		_projection = glm::perspective(_fieldOfView,_aspectRatio,_nearPlane,_farPlane);

		updateView();
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera View matrix
/////////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 QuatCamera::view() 
	{
	
		this->updateView();
		return _view;
	}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera Projection matrix
/////////////////////////////////////////////////////////////////////////////////////////////
	glm::mat4 QuatCamera::projection() 
	{
		return _projection;		
	}

	void QuatCamera::updateMVP(glm::mat4 model)
	{
		m_MVP = _projection * (_view * model);
	}
	
	glm::mat4 QuatCamera::getMVP()
	{
		return m_MVP;
	}

	std::vector<glm::vec3> QuatCamera::getCameraPositions()
	{
		return m_cameraPositions;
	}

	std::vector<glm::vec3> QuatCamera::getCameraOrientations()
	{
		return m_cameraOrientations;
	}