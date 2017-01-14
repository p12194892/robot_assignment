#pragma once

/*!
* @file CameraComponent.h
* Header file containing the camera attributes
*/

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Entity.h"

/*! \class CameraComponent
\brief The camera component views the scene 
*/

class CameraComponent: public Entity
{
	private:
		float m_fFieldOfView; //!< Field of view
		float m_fNearPlane;//!< Near Plane
		float m_fFarPlane; //!< Far Plane
		float m_fAspectRatio; //!< Aspect Ratio
		//The camera coordinate axes
		glm::vec3 m_xaxis; //!< X Axis
		glm::vec3 m_yaxis; //!< Y Axis
		glm::vec3 m_zaxis; //!< Z Axis
		//Camera position vector and Quaternoin to represent camera orientation
		glm::vec3 m_position; //!< Camera Position
		glm::quat m_orientation; //!< Camera Orientation
		//Camera MVP attributes
		glm::mat4 m_view; //!< View Matix
		glm::mat4 m_projection; //!< Projection Matrix
		glm::mat4 m_MVP; //!< Model * View * Projection

	public:
		CameraComponent(int i); //!< Default constructor
	    glm::vec3 position(); //!< Position getter method
		void setPosition(const glm::vec3& position); //!< Position setter method
		float fieldOfView() const; //!< FieldOfView getter method
		void setFieldOfView(float fieldOfView); //!< FieldOfView setter method
		float aspectRatio() const; //!< AspectRatio getter method
		void setAspectRatio(float aspectRatio); //!< AspectRatio setter method
		float nearPlane() const; //!< NearPlane getter method
		float farPlane() const; //!< FarPlane getter method
		void setNearAndFarPlanes(float nearPlane, float farPlane); //!< NearPlane and farPLane setter method
		void rotate(const float yaw, const float pitch); //!< Rotate camera
		void pan(const float x, const float y); //!< Pan camera
		void roll(const float z); //!< Roll camera
		void zoom(const float z); //!< Zoom camera
		void reset(glm::vec3 pos, glm::vec3 ori); //!< Reset the camera
		glm::mat4 view(); //!< Get the View matrix
		glm::mat4 projection(); //!< Get the Projection matrix	 
		void updateMVP(glm::mat4 model); //!< Updates the mvp matrix 
		glm::mat4 getMVP(); //!< gets the MVP matrix
		glm::quat fromAxisAngle(glm::vec3 axis, float angle); //!< Converts rotation in quaternion
		glm::mat4 getView(); //!< Gets the view matrix
		glm::mat4 getProjection(); //!< Gets the projection matrix

		 //!< Update the camera
		void update() 
		{
			//Construct the view matrix from orientation quaternion and position vector

			//First get the matrix from the 'orientaation' Quaternion
			//This deals with the rotation and scale part of the view matrix
			m_view = glm::mat4_cast(m_orientation); // Rotation and Scale

			//Extract the camera coordinate axes from this matrix
			m_xaxis = glm::vec3(m_view[0][0], m_view[0][1], m_view[0][2]);
			m_yaxis = glm::vec3(m_view[1][0], m_view[1][1], m_view[1][2]);
			m_zaxis = glm::vec3(m_view[2][0], m_view[2][1], m_view[2][2]);

			//And use this and current camera position to set the translate part of the view matrix
			m_view[3][0] = -glm::dot(m_xaxis, m_position); //Translation x
			m_view[3][1] = -glm::dot(m_yaxis, m_position); //Translation y
			m_view[3][2] = -glm::dot(m_zaxis, m_position); //Translation z
		}

};
