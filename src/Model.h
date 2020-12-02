#ifndef MODELH
#define MODELH

#include <assimp/config.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <SOIL2/SOIL2.h>

#include <string>
#include <vector>

#include "ShaderProgram.hpp"
#include "Mesh.h"

unsigned int TextureFromFile(const char* file, const std::string directory, bool gamma = false);

class Model {
public:
	Model(std::string path);
	~Model();

	void Draw(ShaderProgram shader);

private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	// model data
	std::vector<Mesh> meshes;
	std::vector<Texture> textures_loaded;
	std::string directory;
};
#endif // !MODELH
