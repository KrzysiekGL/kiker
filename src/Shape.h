#ifndef SHAPEH
#define SHAPEH

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <memory>

#include "ShaderProgram.hpp"

namespace CGL {
	enum COLOR {
		RED,
		GREEN,
		BLUE,
		YELLOW,
		WHITE,
		BLACK,
		GRAY,
		MAGENTA,
		CYAN
	};

	class Shape {
	public:
		Shape();
		virtual ~Shape();

		virtual void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projeciton) = 0;
		void SetColor(CGL::COLOR color);
		void CreateShader(const char* vertFile, const char* fragFile);
		void SetShader(ShaderProgram shader);
	protected:
		virtual void loadDataToVAO() = 0;

		CGL::COLOR color;
		ShaderProgram shader;
		GLuint VAO, VBO;
	};
}

#endif // !SHAPEH
