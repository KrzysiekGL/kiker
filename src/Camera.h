#ifndef CAMERAH
#define CAMERA

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CGL {
	class Camera {
	public:
		Camera();
		~Camera();

		glm::mat4 GetViewMatrix();
		void KeyInputProcess(GLFWwindow* window, float deltaTime);
		void MouseInputProcess(GLFWwindow* window);

	private:
		void updateCameraVectors();

		float
			cameraSpeed,
			cameraSensitivity,
			pitch,
			yaw;

		glm::vec3
			cameraPos,
			cameraRevDir,
			cameraRight,
			cameraUp;
	};
} // namespace CGL

#endif // !CAMERAH 
