#ifndef SHADERHPP
#define SHADERHPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

enum class ShaderType {
	VERTEX,
	FRAGMENT
};

class ShaderProgram {
public:
	// Constructors & Destructors
	ShaderProgram();
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	~ShaderProgram();

	//Methods
	GLuint GetProgram() { return this->ID; }
	void Use() { glUseProgram(this->ID); }

	void SetUniform1i(std::string name, int v);
	void SetUniformMatrix4f(std::string name, glm::mat4 mat);

private:
	// Fields
	GLuint ID;

	// Methods
	void addShaderToProgram(const char* filePath, ShaderType type);
	std::string readFileToSource(const char* filePath);
};

#endif // !SHADERHPP
