#ifndef LINEH
#define LINEH

#include "Shape.h"

namespace CGL {
	class Line : public virtual Shape {
	public:
		Line() {}
		Line(glm::vec3 A, glm::vec3 B);

		void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projeciton);
		void SetCoords(glm::vec3 A, glm::vec3 B);
		void SetColor(CGL::COLOR color);

	private:
		void loadDataToVAO();
		GLfloat lineVertices[6];
	};
}

#endif // !LINEH
