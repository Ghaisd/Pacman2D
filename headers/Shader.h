#pragma once
#include "Libraries.h"

class Shader
{
private:
	GLuint ID;

public:
	Shader(const std::string& vertexShaderSrc,
		const std::string& fragmentShaderSrc);
	GLuint getID();
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, glm::vec2 value);
	~Shader();
	
};

