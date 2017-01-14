#define _USE_MATH_DEFINE
#define PI 3.141592653589793
#define TWOPI 6.2831853071795862
#define TWOPI_F 6.2831853f
#define TO_RADIANS(x) (x * 0.017453292519943295)
#define TO_DEGREES(x) (x * 57.29577951308232)
#include <cmath>
#include "CameraComponent.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>

//World coordinate System Axes
const glm::vec3 WORLDX = glm::vec3(1,0,0);
const glm::vec3 WORLDY = glm::vec3(0,1,0);
const glm::vec3 WORLDZ = glm::vec3(0,0,1);


//!< Default constructor
CameraComponent::CameraComponent(int i)
	{		
		if (i == 0)
		{
			reset(glm::vec3(-2.0f, -27.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		}

		else if (i == 1)
		{
			reset(glm::vec3(2.22959f, -38.30103f, 20.91515f), glm::vec3(0.511735f, 0.00128345f, 0.01129044f));
		}

		else if (i == 2)
		{
			reset(glm::vec3(-20.0f, -37.0f, 31.0f), glm::vec3(-0.0147318f, -0.297431f, -0.00698154f));
		}
	}

//!< Position getter method
glm::vec3 CameraComponent::position() 
	{
		return m_position;
	}

//!< Position setter method
void CameraComponent::setPosition(const glm::vec3& position)
	{
		m_position = position;
	}

//!< FieldOfView getter method
float CameraComponent::fieldOfView() const
	{
		return m_fFieldOfView;
	}

//!< FieldOfView setter method
void CameraComponent::setFieldOfView(float fieldOfView)
	{
		assert(fieldOfView>0.0f && fieldOfView <180.0f);
		m_fFieldOfView = fieldOfView;
	}

//!< AspectRatio getter method
float CameraComponent::aspectRatio() const
	{
		return m_fAspectRatio;
	}

//!< AspectRatio setter method
void CameraComponent::setAspectRatio(float aspectRatio)
	{
		assert(aspectRatio >0.0f);
		m_fAspectRatio = aspectRatio;
	}

//!< NearPlane getter method
float CameraComponent::nearPlane() const
	{
		return m_fNearPlane;
	}

//!< FarPlane getter method
float CameraComponent::farPlane() const
	{
		return m_fFarPlane;
	}

//!< NearPlane and farPLane setter method
void CameraComponent::setNearAndFarPlanes(float nearPlane, float farPlane)
	{
		assert(nearPlane > 0.0f);
		assert(farPlane > nearPlane);
		m_fNearPlane = nearPlane;
		m_fFarPlane = farPlane;
	}

//!< Converts rotation in quaternion
glm::quat CameraComponent::fromAxisAngle(glm::vec3 axis, float angle)
	{
		//conversion from axis-angle
		//GLM must have an angle in degress so convert it
		//Created a quaternion
		glm::quat rotation;
		rotation = glm::angleAxis(glm::degrees(angle), axis);
		return rotation;
	}

//!< Rotate camera
void CameraComponent::rotate(const float yaw, const float pitch)
	{
		m_orientation = glm::normalize(fromAxisAngle(WORLDX, pitch)*m_orientation);
	
		m_orientation = glm::normalize(m_orientation * fromAxisAngle(WORLDY, yaw));	
		update();
	}

//!< Pan camera
void CameraComponent::pan(const float x, const float y)
	{
		
		m_position += m_xaxis * x;
		m_position += m_yaxis * -y;
		update();
	}

//!< Zoom camera
void CameraComponent::zoom(const float z)
	{

		m_position += m_zaxis * z;
		update();
	}

//!< Roll camera
void CameraComponent::roll(const float z)
	{
		m_orientation = glm::normalize(fromAxisAngle(WORLDZ, z) *m_orientation);
		update();
	}

//!< Reset the camera
void CameraComponent::reset(glm::vec3 pos, glm::vec3 ori)
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

		update();
	}

//!< Get the View matrix
glm::mat4 CameraComponent::view()
	{
	
		this->update();
		return m_view;
	}

//!< Get the Projection matrix	
glm::mat4 CameraComponent::projection()
	{
		return m_projection;		
	}

//!< Updates the mvp matrix 
void CameraComponent::updateMVP(glm::mat4 model)
{
	m_MVP = m_projection * (m_view * model);
}
	
//!< Gets the MVP matrix
glm::mat4 CameraComponent::getMVP()
{
	return m_MVP;
}

//!< Gets the view matrix
glm::mat4 CameraComponent::getView()
{
	return m_view;
}

//!< Gets the projection matrix
glm::mat4 CameraComponent::getProjection()
{
	return	m_projection;
}


