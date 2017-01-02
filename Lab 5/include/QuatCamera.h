#pragma once
/*!
* @file QuatCamera.h
* Header file containing the camera attributes
*/
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

/*! \class QuatCamera
\brief The camera
*/

class QuatCamera 
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
		//Set glm vectors to view the simulation with different cameras
		std::vector<glm::vec3> m_cameraPositions; //!< Stores different camera positions depending on the type of view
		std::vector<glm::vec3> m_cameraOrientations; //!< Stores different camera orientations depending on the type of view

	public:
		QuatCamera(); //!< Default constructor
		const glm::vec3& position() const; //!< Position getter method
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
		void updateView();  //!< Update the camera
		void reset(glm::vec3 pos, glm::vec3 ori); //!< Reset the camera
		glm::mat4 view(); //!< Get the View matrix
		glm::mat4 projection(); //!< Get the Projection matrix	 
		void updateMVP(glm::mat4 model); //!< Updates the mvp matrix 
		glm::mat4 getMVP(); //!< gets the MVP matrix
		std::vector<glm::vec3> getCameraPositions(); //!< Gets the camera positions
		std::vector<glm::vec3> getCameraOrientations(); //!< gets the camera orientations
		glm::quat fromAxisAngle(glm::vec3 axis, float angle); //!< Converts rotation in quaternion

};
