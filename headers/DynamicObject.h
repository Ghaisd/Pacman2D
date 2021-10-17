#pragma once
#include "Libraries.h"
#include "GameObject.h"
class DynamicObject : public GameObject
{
protected:
    float posX = 1, posY = 18, posZ, vel = 5.0f;
    float const PI = glm::pi<float>();
    char dir;
public:
   
    void DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects);
    void GhostMovement(GLFWwindow* window, GLuint shaderProgram, float deltaTime, const std::vector< std::pair<int, int> >& objects, char dir);
    char changeDir(char dir);
    float getPosX();
    float getPosY();
    void setPos(float posX, float posY);
    void selectTexture(float& counter, float speed, float showTexture, int& textureNr, int& textureGhostNr);
};