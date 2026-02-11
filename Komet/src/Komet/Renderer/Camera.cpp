#include "kmpch.h"
#include "Camera.h"

namespace Komet {
	Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
		m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM)
	{
		m_Position = position;
		m_WorldUp = up;
		m_Yaw = yaw;
		m_Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	glm::mat4 Camera::GetProjectionMatrix(float aspectRatio, float nearPlane, float farPlane) const
	{
		return glm::perspective(glm::radians(m_Zoom), aspectRatio, nearPlane, farPlane);
	}

	void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = m_MovementSpeed * deltaTime;
		switch (direction)
		{
		case FORWARD:
			m_Position += m_Front * velocity;
			break;
		case BACKWARD:
			m_Position -= m_Front * velocity;
			break;
		case LEFT:
			m_Position -= m_Right * velocity;
			break;
		case RIGHT:
			m_Position += m_Right * velocity;
			break;
		case UP:
			m_Position += m_Up * velocity;
			break;
		case DOWN:
			m_Position -= m_Up * velocity;
			break;
		default:
			break;
		}
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	{
		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw += xoffset;
		m_Pitch += yoffset;

		if (constrainPitch)
		{
			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;
		}
		updateCameraVectors();
	}

	void Camera::ProcessMouseScroll(float yoffset)
	{
		m_Zoom -= yoffset;

		if (m_Zoom < 1.0f)
			m_Zoom = 1.0f;
		if (m_Zoom > 45.0f)
			m_Zoom = 45.0f;
	}

	void Camera::updateCameraVectors()
	{
		glm::vec3 front;

		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}
}