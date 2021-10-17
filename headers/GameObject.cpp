#include "GameObject.h"
using namespace glm;
// -----------------------------------------------------------------------------
// Create game object by generating vao, vbo, and ebo
// -----------------------------------------------------------------------------

void GameObject::CreateObject(std::vector<GLfloat> objects)
{
    GLuint indices[6] = { 0,1,2,0,2,3 };

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects.size(), &objects.front(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
}

// -----------------------------------------------------------------------------
// Return vao for a game object
// -----------------------------------------------------------------------------

GLuint& GameObject::GetVao()
{
    return vao;
}
