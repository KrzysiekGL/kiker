#ifndef RECTANGLEH
#define RECTANGLEH

#include <vector>

#include "Line.h"

namespace CGL {
    class Rectangle : public Line {
    public:
        Rectangle(glm::vec3 origin, glm::vec2 dimensions);
        void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
    private:
        glm::vec3 origin;
        glm::vec3 dimensions;
        std::vector<Line> elements;
    };
}

#endif // !RECTANGLEH
