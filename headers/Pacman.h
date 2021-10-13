#include "Libraries.h"
#include "GameObject.h"

class Pacman : public GameObject
{
private:

    float const PI = glm::pi<float>();
    glm::mat4 rotation;
    glm::mat4 transformation;
    char dir, inputDir;
    bool canWalk = true;
    int passedReg = 0; //passed regularly
 
public:
    int eatenPellets = 0;
    std::pair<int, int> srcPellet, dstPellet;
    std::vector<GLfloat> pacmanInitPos = {
       -0.20f   ,  -0.20f   ,   0.0f,   1.0f,1.0f,
       -0.20f   ,  -0.85f   ,   0.0f,   1.0f,0.0f,
       -0.85f   ,  -0.85f   ,   0.0f,   0.0f,0.0f,
       -0.85f   ,  -0.20f   ,   0.0f,   0.0f,1.0f
    };
   
    void PacmanInput(GLFWwindow* window, GLuint shaderProgram, float deltaTime,
        std::vector<std::pair<int, int>> pellets);
    bool findDst(const std::vector<std::pair<int, int>>& pellets);
    void setupAttrib();
    void DrawObjects(GLuint shaderProgram, std::vector<std::pair<int, int> > objects, float r, float g, float b, std::vector <GLuint> textures,int index);
    void setPos(float pacmanX, float pacmanY);
    glm::mat4 setRotationDir();
    bool CheckCollision(float posX1, float posY1, float posX2, float posY2, float collisionDistance);
    void eatPellets(float x1, float y1, std::vector< std::pair<int, int> >& objects);
    bool pacGhostsCollision(std::vector <float> ghostX, std::vector <float> ghostY, std::vector<std::pair<int, int> > v_ghosts);
};