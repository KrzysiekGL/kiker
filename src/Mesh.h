#ifndef MESHH
#define MESHH

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "ShaderProgram.hpp"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	void Draw(ShaderProgram shader);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};

#endif // !MESHH 
