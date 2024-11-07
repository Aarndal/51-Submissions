#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

struct Camera
{
	//Constructor
	Camera(glm::vec3 position, glm::vec3 direction);

	//Getter Methods
	glm::vec3 GetPosition() { return m_position; }
	glm::mat4 GetViewMatrix() { return m_viewMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }

	//Methods
	int Update();

private:
	//Member Variables
	glm::vec3 m_position{};
	glm::vec3 m_forward{};
	glm::vec3 m_up{ 0,1,0 };
	glm::vec3 m_right{};
	glm::vec2 m_sensitivity{ 0.75f,0.5f };
	float m_pitch{ 0.0f }, m_yaw{ -90.0f };
	float m_speed{ 1.0f }, m_sprintSpeed{ 5.0f };
	float m_fieldOfView{ 45.0f };
	float m_nearPlane{ 0.1f }, m_farPlane{ 100.0f };
	int m_screenWidth{}, m_screenHeight{};

	glm::mat4 m_viewMatrix{ 1.0f };
	glm::mat4 m_projectionMatrix{ 1.0f };

	//Setter Methods
	void SetRightVector() { m_right = glm::normalize(glm::cross(m_forward, m_up)); }
	void SetViewMatrix() { m_viewMatrix = { glm::lookAt(m_position,m_position + m_forward, m_up) }; }
	void SetProjectionMatrix() { m_projectionMatrix = { glm::perspective(glm::radians(m_fieldOfView), (float)m_screenWidth / m_screenHeight, m_nearPlane, m_farPlane) }; }
};

#endif //CAMERA_H