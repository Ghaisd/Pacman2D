#include "Libraries.h"
#include "GameObject.h"

class Wall : public GameObject
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