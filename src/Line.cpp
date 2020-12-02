#include "Line.h"

CGL::Line::Line(glm::vec3 A, glm::vec3 B) {
	SetCoords(A, B);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void CGL::Line::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	if (!shader.GetProgram())
		shader = ShaderProgram("res/shaders/line.vert", "res/shaders/line.frag");

	shader.Use();
	shader.SetUniformMatrix4f("model", model);
	shader.SetUniformMatrix4f("view", view);
	shader.SetUniformMatrix4f("projection", projection);

	loadDataToVAO();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CGL::Line::SetCoords(glm::vec3 A, glm::vec3 B) {
	lineVertices[0] = A.x;
	lineVertices[1] = A.y;
	lineVertices[2] = A.z;
	lineVertices[3] = B.x;
	lineVertices[4] = B.y;
	lineVertices[5] = B.z;
}

void CGL::Line::loadDataToVAO() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
