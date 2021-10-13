#pragma once
#include "Libraries.h"
using namespace glm;
class GameObject
{
protected:
    GLuint vao;
    glm::mat4 translation;
    char dir;
    int usesTexture;
public:
float posX = 1, posY = 18, posZ, vel = 5.0f;
    void CreateObject(GLuint shaderProgram,  std::vector<GLfloat>  objects ,int usesTexture);
    void DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects, float r, float g, float b);
    void ObjectInput(GLFWwindow* window, GLuint shaderProgram, float deltaTime,const  std::vector< std::pair<int, int> > &objects);
    char collision(float& X, float& Y, std::vector< std::pair<int, int> > objects, char dir);
    void GhostMovement(GLFWwindow* window, GLuint shaderProgram, float deltaTime, const std::vector< std::pair<int, int> >& objects,  char dir);
    char changeDir(char dir);
    float getPosX();
    float getPosY();
    GLuint& GetVao();

}; 