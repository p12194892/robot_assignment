#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
Camera::Camera()
{
	camDirectionX = 0.0f;
	camDirectionY = 0.0f;

	camRotateX = 0.0f;
	camRotateY = 0.0f;
}

void Camera::setPerspective(float a, float b, float c, float d)
{
	m_projection = glm::perspective(glm::radians(a), b / b, c, d);
}

void Camera::setView(glm::vec3 a /*position of the camera*/, glm::vec3 b /*direction of the camera*/, glm::vec3 c /*represent the positivex - axis of camera space*/)
{
	m_cameraPos = a;
	m_direction = b;
	m_axis = c;
	m_view = glm::lookAt(a, b, c);
}

void Camera::setModel(glm::vec3 translate, glm::vec3 scale, glm::vec3 rotate, float angle)
{
	m_translation = translate;
	m_scale = scale;
	m_rotate = rotate;
	m_angle = angle;

	m_model = glm::rotate(glm::radians(m_angle), m_rotate) * glm::scale(m_scale) * glm::translate(m_translation);
}

glm::mat4 Camera::getTransformationMatrix()
{
	m_mvp = m_projection * m_view * m_model;
	return m_mvp;
}

void Camera::updateMovement(char c)
{
	switch (c) {

	case 'U':
		m_cameraPos.z = m_cameraPos.z - 0.1;
		m_direction.z = m_direction.z - 0.1;
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);

		break;

	case 'D':
		m_cameraPos.z = m_cameraPos.z + 0.1;
		m_direction.z = m_direction.z + 0.1;
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;
	

	case 'L':
		m_cameraPos.x = m_cameraPos.x - 0.1;
		m_direction.x = m_direction.x - 0.1;
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;

	case 'R':
		m_cameraPos.x = m_cameraPos.x + 0.1;
		m_direction.x = m_direction.x + 0.1;
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;

	case 'A':
		m_cameraPos.y = m_cameraPos.y + 0.1;
		m_direction.y = m_direction.y + 0.1;
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;

	case 'B':
		m_cameraPos.y = m_cameraPos.y - 0.1;
		m_direction.y = m_direction.y - 0.1;
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;

	case 'Q':
		camRotateX = camRotateX + 0.1;
		m_rotate = glm::vec3(camRotateX, camRotateY, 0.0);
		m_model = glm::rotate(glm::radians(camRotateX), m_rotate) * glm::scale(m_scale) * glm::translate(m_translation);
		break;

	case 'W':
		camRotateX = camRotateX - 0.1;
		m_rotate = glm::vec3(camRotateX, camRotateY, 0.0);
		m_model = glm::rotate(glm::radians(camRotateX), m_rotate) * glm::scale(m_scale) * glm::translate(m_translation);
		break;

	case 'E':
		camRotateY = camRotateY + 0.1;
		m_rotate = glm::vec3(camRotateX, camRotateY, 0.0);
		m_model = glm::rotate(glm::radians(camRotateY), m_rotate) * glm::scale(m_scale) * glm::translate(m_translation);
		break;

	case 'T':
		camRotateY = camRotateY - 0.1;
		m_rotate = glm::vec3(camRotateX, camRotateY, 0.0);
		m_model = glm::rotate(glm::radians(camRotateY), m_rotate) * glm::scale(m_scale) * glm::translate(m_translation);
		break;

	case '1':
		camDirectionX = camDirectionX + 0.1f;
		m_direction = glm::vec3(camDirectionX, camDirectionY, 0.0);
		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);		
		break;

	case '2':
		camDirectionX = camDirectionX - 0.1f;
		m_direction = glm::vec3(camDirectionX, camDirectionY, 0.0);

		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;

	case '3':
		camDirectionY = camDirectionY + 0.1f;
		m_direction = glm::vec3(camDirectionX, camDirectionY, 0.0);

		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;

	case '4':
		camDirectionY = camDirectionY - 0.1f;
		m_direction = glm::vec3(camDirectionX, camDirectionY, 0.0);

		m_view = glm::lookAt(m_cameraPos, m_direction, m_axis);
		break;
	}



}