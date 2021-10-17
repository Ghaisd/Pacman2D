#include "Libraries.h"
#include "DynamicObject.h"


class Pacman : public DynamicObject
{
private: 
    glm::mat4 rotation;
    glm::mat4 transformation;
    char dir, inputDir;
    bool canWalk = true;  // frames where pacman can walk
    int passedReg = 0; // passed regularly

public:
    int eatenPellets = 0;
    std::pair<int, int> srcPellet, dstPellet; //src: where pacman is in current frame, dst: where pacman will go in the next frame
    std::vector<GLfloat> pacmanInitPos = {
       -0.20f   ,  -0.20f   ,   0.0f,    1.0f,   1.0f,
       -0.20f   ,  -0.85f   ,   0.0f,    1.0f,   0.0f,
       -0.85f   ,  -0.85f   ,   0.0f,    0.0f,   0.0f,
       -0.85f   ,  -0.20f   ,   0.0f,    0.0f,   1.0f
    };

    void DrawObjects(GLuint shaderProgram, std::vector<std::pair<int, int> > objects, std::vector <GLuint> textures, int index);
    void PacmanInput(GLFWwindow* window, GLuint shaderProgram, float deltaTime,
        std::vector<std::pair<int, int>> pellets);
    void setupAttrib();
    void eatPellets(float x1, float y1, std::vector< std::pair<int, int> >& objects);
    bool pacGhostsCollision(std::vector <float> ghostX, std::vector <float> ghostY, std::vector<std::pair<int, int> > v_ghosts);
    bool CheckCollision(float posX1, float posY1, float posX2, float posY2, float collisionDistance);
    bool findDst(const std::vector<std::pair<int, int>>& pellets);
    glm::mat4 setRotationDir();
};
