#include "Libraries.h"
#include "StaticObject.h"

class Pellet : public StaticObject
{
public:

    std::vector <GLfloat> pelletInitPos =
    {
       0.0f  ,    0.0f    ,    0.0f,        0.0f, 0.0f,
       0.0f  ,   -1.0f    ,    0.0f,        0.0f, 0.0f,
      -1.0f  ,   -1.0f    ,    0.0f,        0.0f, 0.0f,
      -1.0f  ,    0.0f    ,    0.0f,        0.0f, 0.0f
    };
    void DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects, float r, float g, float b, std::vector<int> isMagic);
    bool allPelletsEaten(int eatenPellets, std::vector< std::pair<int, int> > objects);


};