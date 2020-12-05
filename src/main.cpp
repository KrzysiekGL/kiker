#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "CGL/ShaderProgram.h"
#include "CGL/Camera.h"
#include "CGL/Model.h"

#define WIDTH 1280
#define HEIGHT 720

// GLFW callback functions
static void framebufferSizeCallback(GLFWwindow*, int, int);
static void glfwErrorCallback(int, const char*);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Time
static float deltaFrame = 0.f;
static float lastFrame = 0.f;

// Free camera
bool freeCam = false;

int main() {
	// Setup glfw - Context and events handler; lib written for OpenGL in mind
	if (!glfwInit()) return EXIT_FAILURE;
	int width = WIDTH, height = HEIGHT;

	// Setup GL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(width, height, "Zbijak", NULL, NULL);
	if (window == NULL) {
		glfwErrorCallback(EXIT_FAILURE, "Window not created");
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Set farmerate highcap (this here is max of 60 fps)

	// Setup GLEW - OpenGL instruction wrapper
	glewExperimental = GL_TRUE;
	glewInit();

	// GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, key_callback);

	// Prevent loosing mouse click information from event stack
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

	// GL global states
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CW);

	// Begin -- Things to draw
	CGL::ShaderProgram shader("res/shaders/shader.vert", "res/shaders/shader.frag");
	CGL::Model plecak = CGL::Model("res/models/backpack/backpack.obj");
	// End -- Things to draw

	// Pre-GL settings
	glViewport(0, 0, width, height);
	glClearColor(0.3f, 0.7f, 0.5f, 1.f);
	std::unique_ptr<CGL::Camera> camera = std::make_unique<CGL::Camera>();
	glfwSetTime(0.0);

	// Game Loop
	while (!glfwWindowShouldClose(window)) {
		// Events
		glfwPollEvents();
		if (freeCam) {
			camera->KeyInputProcess(window, deltaFrame);
			camera->MouseInputProcess(window);
		}

		// Clear Buffers and redraw background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwGetFramebufferSize(window, &width, &height);


		// Begin -- Rendering
		// Model matrix
		glm::mat4 model = glm::mat4(1.f);

		// View matrix (from camera)
		glm::mat4 view = camera->GetViewMatrix();

		// Projection matrix
		glm::mat4 projection = glm::mat4(1.f);
		projection = glm::perspective(glm::radians(45.f), (float)width / (float)height, .1f, 100.f);

		// Drawing
		shader.SetUniformMatrix4f("model", model);
		shader.SetUniformMatrix4f("view", view);
		shader.SetUniformMatrix4f("projection", projection);

		plecak.Draw(shader);

		// End -- Rendering

        //Time
		float currentFrame = (float)glfwGetTime();
		deltaFrame = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// End of loop
		glfwSwapBuffers(window);
	}

	// Termination and deletion
	glfwTerminate();

	return 0;
}

// main.cpp scope function definitions
//
// GLFW callback
static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
static void glfwErrorCallback(int error, const char* description) {
	fprintf(stderr, "ERROR::GLFW::%s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {

	case GLFW_KEY_0:
		if (action == GLFW_RELEASE) {
			freeCam = !freeCam;
			if (freeCam) { 
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				int fbs_x, fbs_y; glfwGetFramebufferSize(window, &fbs_x, &fbs_y);
				glfwSetCursorPos(window, (double)fbs_x / 2.0, (double)fbs_y / 2.0);
			}
			else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		break;

	default:
		break;
	}
}
