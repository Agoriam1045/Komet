#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




namespace Komet 
{
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	class Camera
	{
	public:
		// Constructor with vectors
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW, float pitch = PITCH);

		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix(float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.0f) const;

		void ProcessKeyboard(Camera_Movement direction, float deltaTime);
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
		void ProcessMouseScroll(float yoffset);

		const glm::vec3& GetPosition() const { return m_Position; }

	private:
		void updateCameraVectors();

	public:
		// Camera Attributes
		glm::vec3	m_Position;
		glm::vec3	m_Front;
		glm::vec3	m_Up;
		glm::vec3	m_Right;
		glm::vec3	m_WorldUp;

		// Euler Angles
		float		m_Yaw;
		float		m_Pitch;

		// Camera options
		float		m_MovementSpeed;
		float		m_MouseSensitivity;
		float		m_Zoom;
	};
}
