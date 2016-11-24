#pragma once
#include <glm\glm.hpp>

class Camera
{
	private:
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 m_mvp;
	glm::vec3 m_cameraPos;
	glm::vec3 m_direction;
	glm::vec3 m_axis;

	glm::vec3 m_translation;
	glm::vec3 m_scale;
	glm::vec3 m_rotate;
	float m_angle;

	float camDirectionX;
	float camDirectionY;

	float camRotateX;
	float camRotateY;


	public:
		Camera();
		void setPerspective(float a, float b, float c, float d);
		void setView(glm::vec3 a /*position of the camera*/, glm::vec3 b /*direction of the camera*/, glm::vec3 c /*represent the positivex - axis of camera space*/);
		void setModel(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float angle);
		glm::mat4 getTransformationMatrix();
		void updateMovement(char c);

};