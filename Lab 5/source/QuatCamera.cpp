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


//!< Default constructor
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

//!< Position getter method
const glm::vec3& QuatCamera::position() const
	{
		return m_position;
	}

//!< Position setter method
void QuatCamera::setPosition(const glm::vec3& position)
	{
		m_position = position;
	}

//!< FieldOfView getter method
float QuatCamera::fieldOfView() const
	{
		return m_fFieldOfView;
	}

//!< FieldOfView setter method
void QuatCamera::setFieldOfView(float fieldOfView)
	{
		assert(fieldOfView>0.0f && fieldOfView <180.0f);
		m_fFieldOfView = fieldOfView;
	}

//!< AspectRatio getter method
float QuatCamera::aspectRatio() const
	{
		return m_fAspectRatio;
	}

//!< AspectRatio setter method
void QuatCamera::setAspectRatio(float aspectRatio)
	{
		assert(aspectRatio >0.0f);
		m_fAspectRatio = aspectRatio;
	}

//!< NearPlane getter method
float QuatCamera::nearPlane() const
	{
		return m_fNearPlane;
	}

//!< FarPlane getter method
	float QuatCamera::farPlane() const
	{
		return m_fFarPlane;
	}

//!< NearPlane and farPLane setter method
void QuatCamera::setNearAndFarPlanes(float nearPlane, float farPlane)
	{
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		m_fNearPlane = nearPlane;
		m_fFarPlane = farPlane;
	}

//!< Converts rotation in quaternion
	glm::quat QuatCamera::fromAxisAngle(glm::vec3 axis, float angle)
	{
		//conversion from axis-angle
		//GLM must have an angle in degress so convert it
		//Created a quaternion
		glm::quat rotation;
		rotation = glm::angleAxis(glm::degrees(angle), axis);
		return rotation;
	}

//!< Rotate camera
void QuatCamera::rotate(const float yaw, const float pitch)
	{
		m_orientation = glm::normalize(fromAxisAngle(WORLDX, pitch)*m_orientation);
	
		m_orientation = glm::normalize(m_orientation * fromAxisAngle(WORLDY, yaw));	
		std::cout << "orientation x: " << m_orientation.x << std::endl << std::endl;
		std::cout << "orientation y: "<< m_orientation.y << std::endl << std::endl;
		std::cout << "orientation z: " << m_orientation.z << std::endl << std::endl;
		updateView();
	}

//!< Pan camera
void QuatCamera::pan(const float x, const float y)
	{
		
		m_position += m_xaxis * x;
		m_position += m_yaxis * -y;
		std::cout << "Position x: " << m_position.x << std::endl << std::endl;
		std::cout << "Position y: " << m_position.y << std::endl << std::endl;
		updateView();
	}

//!< Zoom camera
void QuatCamera::zoom(const float z)
	{

		m_position += m_zaxis * z;
		std::cout << "Position z: " << m_position.z << std::endl << std::endl;
		updateView();
	}

//!< Update the camera
void QuatCamera::updateView()
	{
		//Construct the view matrix from orientation quaternion and position vector

		//First get the matrix from the 'orientaation' Quaternion
		//This deals with the rotation and scale part of the view matrix
		m_view = glm::mat4_cast(m_orientation); // Rotation and Scale

		//Extract the camera coordinate axes from this matrix
		m_xaxis = glm::vec3(m_view[0][0],m_view[0][1],m_view[0][2]);
		m_yaxis = glm::vec3(m_view[1][0],m_view[1][1],m_view[1][2]);
		m_zaxis = glm::vec3(m_view[2][0],m_view[2][1],m_view[2][2]);

		//And use this and current camera position to set the translate part of the view matrix
		m_view[3][0] = -glm::dot(m_xaxis,m_position); //Translation x
		m_view[3][1] = -glm::dot(m_yaxis,m_position); //Translation y
		m_view[3][2] = -glm::dot(m_zaxis,m_position); //Translation z
	
	}
//!< Roll camera
void QuatCamera::roll(const float z)
	{
		m_orientation = glm::normalize(fromAxisAngle(WORLDZ, z) *m_orientation);
		updateView();
	}

//!< Reset the camera
void QuatCamera::reset(glm::vec3 pos, glm::vec3 ori)
	{
		//Initialise camera axes
		m_xaxis = WORLDX;
		m_yaxis = WORLDY;
		m_zaxis = WORLDZ;

		//Initialise camera position 
		m_position = pos;

		//Initialise the orientation
		m_orientation = glm::quat(1.0,0.0,0.0,0.0);
		m_orientation.x = ori.x;
		m_orientation.y = ori.y;
		m_orientation.z = ori.z;

		//Initialise camera perspective parameters
		m_fFieldOfView = glm::radians(50.0f);
		m_fNearPlane = 1.00f;
		m_fFarPlane = 10000.0f;
		m_fAspectRatio = 4.0f/3.0f;

		m_projection = glm::perspective(m_fFieldOfView,m_fAspectRatio,m_fNearPlane, m_fFarPlane);

		updateView();
	}

//!< Get the View matrix
glm::mat4 QuatCamera::view() 
	{
	
		this->updateView();
		return m_view;
	}

//!< Get the Projection matrix	
glm::mat4 QuatCamera::projection() 
	{
		return m_projection;		
	}
//!< Updates the mvp matrix 
void QuatCamera::updateMVP(glm::mat4 model)
	{
		m_MVP = m_projection * (m_view * model);
	}
	
//!< gets the MVP matrix
glm::mat4 QuatCamera::getMVP()
	{
		return m_MVP;
	}
//!< Gets the camera positions
std::vector<glm::vec3> QuatCamera::getCameraPositions()
	{
		return m_cameraPositions;
	}
//!< gets the camera orientations
std::vector<glm::vec3> QuatCamera::getCameraOrientations()
	{
		return m_cameraOrientations;
	}