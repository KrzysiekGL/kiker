#include "Model.h"

Model::Model(std::string path) {
	loadModel(path);
}

Model::~Model() {
	for (Mesh& mesh : meshes)
		mesh.~Mesh();
	meshes.clear();
	textures_loaded.clear();
	directory.clear();
}

void Model::Draw(ShaderProgram shader) {
	for (Mesh& mesh : meshes)
		mesh.Draw(shader);
}

void Model::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(
		path,
		aiProcess_Triangulate |
//		aiProcess_FlipUVs |
		aiProcess_GenSmoothNormals |
		aiProcess_CalcTangentSpace
	);

	if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !scene->mRootNode) {
#ifdef _DEBUG
		std::cout << "ERROR:ASSIMP::" << importer.GetErrorString() << std::endl;
#endif //_DEBUG
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		// position
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		// texture coordinates
		if (mesh->mTextureCoords[0]) {
			glm::vec2 vector;
			vector.x = mesh->mTextureCoords[0][i].x;
			vector.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vector;
		}
		else vertex.TexCoords = glm::vec2(0.f, 0.f);

		vertices.push_back(vertex);
	}

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName) {
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString fileName;
		material->GetTexture(type, i, &fileName);

		// check if this texture with a given path isn't already loaded
		bool skip = false;
		for (Texture& texture : textures_loaded)
			if (std::strcmp(texture.path.c_str(), fileName.C_Str()) == 0) {
				textures.push_back(texture);
				skip = true;
				break;
			}

		// if texture hasn't been loaded already, load it
		if (!skip) {
			Texture texture;
			texture.id = TextureFromFile(fileName.C_Str(), directory);
			texture.type = typeName;
			texture.path = fileName.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return textures;
}

unsigned int TextureFromFile(const char* file, const std::string directory, bool gamma) {
	std::string path = directory + '/' + std::string(file);

	unsigned int textureID = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS |
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		SOIL_FLAG_INVERT_Y |
#endif
		SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT
	);

#ifdef _DEBUG
	if (textureID == 0) {
		printf("ERROR::SOIL2::LOADING: '%s'\n", SOIL_last_result());
		return textureID;
	}
#endif // _DEBUG
	if (!textureID) {
		glBindTexture(GL_TEXTURE_2D, textureID);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	return textureID;
}
