#include "Shader.h"

// -----------------------------------------------------------------------------
// compile the shader
// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------
// RETURN THE SHADER ID
// -----------------------------------------------------------------------------
GLuint Shader::getID()
{
	return ID;
}


Shader::~Shader()
{
	glDeleteShader(ID);
}