#include "Libraries.h"
#include "GameObject.h"

class Ghost : public GameObject
{
private:
    float PI = glm::pi<float>();   
    std::vector <char> dir={'r','r','r','r'};
public:
    std::vector <float> ghostX = { 0,0,0,0 };
    std::vector <float> ghostY = { 0,0,0,0 };
    std::vector<GLfloat> ghostInitPos = {     

       -0.20f   ,  -0.20f   ,  0.0f,      0.0f, 0.0f,
       -0.20f   ,  -0.85f   ,  0.0f,      0.0f, 1.0f,
       -0.85f   ,  -0.85f   ,  0.0f,      1.0f, 1.0f,
       -0.85f   ,  -0.20f   ,  0.0f,      1.0f, 0.0f

    };
    std::vector <std::pair<int, int>> srcPellets=std::vector<std::pair<int,int>>(4);
    std::vector <std::pair<int, int>> dstPellets=std::vector<std::pair<int,int>>(4);
    void moveBetweenPellets(const std::vector<std::pair<int, int>>& pellets,
        std::vector<std::pair<int, int>>& ghosts,
        float deltaTime);
    void findNewSrc();
    void findDst(const std::vector<std::pair<int, int>>& pellets,int index);
    void DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects, float r, float g, float b , std::vector <GLuint> textures, int index);
    float ghostPosX();
    float ghostPosY();
    void setPos(float ghostX, float ghostY);
};