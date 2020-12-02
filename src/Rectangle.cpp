#include "Rectangle.h"

CGL::Rectangle::Rectangle(glm::vec3 origin, glm::vec2 dimensions) {
	float x, y, z, a, b;
	x = origin.x; y = origin.y; z = origin.z; a = dimensions.x; b = dimensions.y;
	elements.push_back(Line(glm::vec3(x, y, z), glm::vec3(x + a, y, z)));
	elements.push_back(Line(glm::vec3(x + a, y, z), glm::vec3(x + a, y - b, z)));
	elements.push_back(Line(glm::vec3(x + a, y - b, z), glm::vec3(x, y - b, z)));
	elements.push_back(Line(glm::vec3(x, y - b, z), glm::vec3(x, y, z)));
}

void CGL::Rectangle::Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
	if (!shader.GetProgram()) {
		shader = ShaderProgram("res/shaders/line.vert", "res/shaders/line.frag");
		for (Line& line : elements)
			line.SetShader(shader);
	}

	for (Line& line : elements)
		line.Draw(model, view, projection);
}
