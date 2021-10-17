#include "Libraries.h"
#include "StaticObject.h"

class Wall : public StaticObject
{

public:
    std::vector <GLfloat> wallInitPos =
    {
       0.0f ,   0.0f,        0.0f,   0.0f, 0.0f,
       0.0f ,  -1.0f,        0.0f,   0.0f, 0.0f,
      -1.0f,   -1.0f,        0.0f,   0.0f, 0.0f,
      -1.0f,    0.0f,        0.0f,   0.0f, 0.0f
    };

};