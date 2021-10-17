#pragma once
#include "Libraries.h"
#include "GameObject.h"
class StaticObject : public GameObject
{

public:
   void DrawObjects(GLuint shaderProgram, std::vector<std::pair<int, int> > objects, float r, float g, float b);
};