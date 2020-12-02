#include "Shape.h"

CGL::Shape::Shape() {
	shader = ShaderProgram();
}

CGL::Shape::~Shape() {
}

void CGL::Shape::CreateShader(const char* vertFile, const char* fragFile) {
	shader = ShaderProgram(vertFile, fragFile);
}

void CGL::Shape::SetShader(ShaderProgram shader) {
	this->shader = shader;
}
