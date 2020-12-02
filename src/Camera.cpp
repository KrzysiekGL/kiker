#include "Camera.h"

Camera::Camera() : cameraSpeed(2.f), cameraSensitivity(.1f), pitch(0.f), yaw(-90.f), cameraPos(glm::vec3(0.f, 0.f, 2.f)) {
	// Initialize camera vectors
	// camera reverse direction - assume that camera initially is looking at the origin of the world
	glm::vec3 target = glm::vec3(0.f);
	cameraRevDir = glm::normalize(cameraPos - target);
	// camera right
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	cameraRight = glm::normalize(glm::cross(worldUp, cameraRevDir));
	// camera up
	cameraUp = glm::normalize(glm::cross(cameraRevDir, cameraRight));
}

Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() {
	glm::vec3 target = cameraPos - cameraRevDir;
	glm::mat4 view = glm::lookAt(cameraPos, target, cameraUp);
	return view;
}

void Camera::KeyInputProcess(GLFWwindow* window, float deltaTime) {
	// Forward, Backward and strafe
	// forward
	if (glfwGetKey(window, GLFW_KEY_W))
		cameraPos -= deltaTime * cameraSpeed * cameraRevDir;
	// backward
	if (glfwGetKey(window, GLFW_KEY_S))
		cameraPos += deltaTime * cameraSpeed * cameraRevDir;
	// right
	if (glfwGetKey(window, GLFW_KEY_D))
		cameraPos += deltaTime * cameraSpeed * cameraRight;
	// left
	if (glfwGetKey(window, GLFW_KEY_A))
		cameraPos -= deltaTime * cameraSpeed * cameraRight;
	// up
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		cameraPos += deltaTime * cameraSpeed * cameraUp;
	// down
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL))
		cameraPos -= deltaTime * cameraSpeed * cameraUp;
}

void Camera::MouseInputProcess(GLFWwindow* window) {
	int fbs_x, fbs_y; glfwGetFramebufferSize(window, &fbs_x, &fbs_y);
	double crs_x, crs_y; glfwGetCursorPos(window, &crs_x, &crs_y);
	glfwSetCursorPos(window, (double)fbs_x / 2.0, (double)fbs_y / 2.0);

	float dx = (float)(crs_x - (double)fbs_x / 2.0);
	float dy = (float)((double)fbs_y / 2.0 - crs_y);

	yaw += dx * cameraSensitivity;
	pitch += dy * cameraSensitivity;
	// camera vertical lock
	if (pitch >= 89.f) pitch = 89.f;
	else if (pitch <= -89.f) pitch = -89.f;

	glm::vec3 newDirection;
	newDirection.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	newDirection.y = glm::sin(glm::radians(pitch));
	newDirection.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	cameraRevDir = glm::normalize(-newDirection);
	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	// camera right
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	cameraRight = glm::normalize(glm::cross(worldUp, cameraRevDir));
	// camera up
	cameraUp = glm::normalize(glm::cross(cameraRevDir, cameraRight));
}
