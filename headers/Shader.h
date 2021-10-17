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
	~Shader();
};

