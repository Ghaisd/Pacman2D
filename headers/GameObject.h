#pragma once
#include "Libraries.h"

class GameObject
{
protected:
    glm::mat4 translation;
    GLuint vao;
public:
    void CreateObject(std::vector<GLfloat> vertices);
    GLuint& GetVao();

};