#include "Shader.h"

Shader::Shader(const std::string& vertexShaderSrc,
	const std::string& fragmentShaderSrc)
{
	auto vertexSrc = vertexShaderSrc.c_str();
	auto fragmentSrc = fragmentShaderSrc.c_str();

	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);

	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);

	auto shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	ID = shaderProgram;

}

GLuint Shader::getID()
{
	return ID;
}


void Shader::SetUniform(const std::string& name, int value)
{
	auto uniformID = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformID, value);
}

void Shader::SetUniform(const std::string& name, float value)
{
	auto uniformID = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformID, value);
}

void Shader::SetUniform(const std::string& name, glm::vec2 value)
{
	auto uniformID = glGetUniformLocation(ID, name.c_str());
	glUniform1f(uniformID, (value.x, value.y));
}

Shader::~Shader()
{
	glDeleteShader(ID);
}