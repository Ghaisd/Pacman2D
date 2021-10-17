#include "Libraries.h"
#include "DynamicObject.h"

class Ghost : public DynamicObject
{
private:
    std::vector <char> dir = { 'r','r','r','r' };
public:
    std::vector <float> ghostX = { 0,0,0,0 };
    std::vector <float> ghostY = { 0,0,0,0 };
    std::vector<GLfloat> ghostInitPos = {
       -0.20f   ,  -0.20f   ,  0.0f,      0.0f, 0.0f,
       -0.20f   ,  -0.85f   ,  0.0f,      0.0f, 1.0f,
       -0.85f   ,  -0.85f   ,  0.0f,      1.0f, 1.0f,
       -0.85f   ,  -0.20f   ,  0.0f,      1.0f, 0.0f
    };
    std::vector <std::pair<int, int>> srcPellets = std::vector<std::pair<int, int>>(4);//src: where ghost is in current frame, 
    std::vector <std::pair<int, int>> dstPellets = std::vector<std::pair<int, int>>(4);//dst: Where ghost will go in the next frame
    void DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects, float r, float g, float b, std::vector <GLuint> textures, int index);
    void moveBetweenPellets(const std::vector<std::pair<int, int>>& pellets,
        std::vector<std::pair<int, int>>& ghosts,float deltaTime);
    void findDst(const std::vector<std::pair<int, int>>& pellets, int index);

};