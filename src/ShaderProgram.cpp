#include "ShaderProgram.hpp"
namespace CGL {

	ShaderProgram::ShaderProgram() {
		ID = 0;
	#ifdef _DEBUG
		std::cout << "ShaderProgram instansiated, but shader program itself not compiled and created.\n";
	#endif // _DEBUG
	}

	ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
		this->ID = glCreateProgram();

		addShaderToProgram(vertexFile, ShaderType::VERTEX);
		addShaderToProgram(fragmentFile, ShaderType::FRAGMENT);

		glLinkProgram(this->ID);
	#ifdef _DEBUG
	// Debugging
		int success;
		glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
			std::cout << "ERROR::GL::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			std::cout << "Program created, but could not be linked\n";
		}
	#endif // _DEBUG
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(this->ID);
	}

	std::string ShaderProgram::readFileToSource(const char* filePath) {
		std::ifstream file(filePath);
		if (file) {
			std::stringstream text;
			text << file.rdbuf();
			file.close();
			return text.str();
		}
		else {
	#ifdef _DEBUG
			std::cout << "ERRORR::IFSTREAM::Coudl not open file " << filePath << std::endl;
	#endif // _DEBUG
			file.close();
			return 0;
		}
	}

	void ShaderProgram::addShaderToProgram(const char* filePath, ShaderType type) {
		GLuint shader;
		std::string string_source = readFileToSource(filePath);
		const char* source = string_source.c_str();

		if (type == ShaderType::VERTEX)
			shader = glCreateShader(GL_VERTEX_SHADER);
		else // ShaderType::FRAGMENT
			shader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);

		int success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
	#ifdef _DEBUG
				std::cout << "ERROR::GL::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	#endif // _DEBUG
				glDeleteShader(shader);
			}
			else {
				glAttachShader(this->ID, shader);
				glDeleteShader(shader);
			}
	}

	void ShaderProgram::SetUniform1i(std::string name, int value) {
		int	location = glGetUniformLocation(ID, name.c_str());
		glUniform1i(location, value);
	}

	void ShaderProgram::SetUniformMatrix4f(std::string name, glm::mat4 mat) {
		int location = glGetUniformLocation(this->ID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
	}
} // namespace CGL
