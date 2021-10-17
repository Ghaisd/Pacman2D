#include "DynamicObject.h"
// -----------------------------------------------------------------------------
// Draw the object using translation
// -----------------------------------------------------------------------------
void DynamicObject::DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects)
{
    auto usesTextureLocation = glGetUniformLocation(shaderProgram, "usesTexture");
    glUniform1i(usesTextureLocation, 1);
    for (int i = 0; i < objects.size(); i++)
    {
        GLuint transformationmat = glGetUniformLocation(shaderProgram, "u_TransformationMat");
        translation = translate(mat4(1), vec3(posX, posY, 0));
        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(translation));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
    }
}

// -----------------------------------------------------------------------------
// Change direction for a moving object when collison happens
// -----------------------------------------------------------------------------

char DynamicObject::changeDir(char dir)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 2); // distribution in range [0, 1].
    int dirValue = dist2(rng);
    std::vector <char> directions = { 'l', 'r', 'u', 'd' };
    directions.erase(std::remove(directions.begin(), directions.end(), dir), directions.end());
    return directions[dirValue];
}

// -----------------------------------------------------------------------------
// Return position x for a moving object
// -----------------------------------------------------------------------------

float DynamicObject::getPosX()
{
    return posX;
}

// -----------------------------------------------------------------------------
// Return position y for a moving object
// -----------------------------------------------------------------------------

float DynamicObject::getPosY()
{
    return posY;
}

// -----------------------------------------------------------------------------
// Change positions x and y for a moving object
// -----------------------------------------------------------------------------

void DynamicObject::setPos(float posX, float posY)
{
    this->posX = posX;
    this->posY = posY;
}

// -----------------------------------------------------------------------------
// Ghostmovement and collisoin by using the walkable vector and check for surrounding
// -----------------------------------------------------------------------------
void DynamicObject::GhostMovement(GLFWwindow* window, GLuint shaderProgram, float deltaTime, const std::vector< std::pair<int, int> >& objects, char dir)
{
    float vt = vel * deltaTime;
    this->dir = dir;
    glm::mat4 rotation;
    if (this->dir == 'r')
    {
        posX += vt;
        bool foundApellet = false;
        int roundedPosX = std::round(posX);
        int roundedPosY = std::round(posY);
        for (int i = 0; i < objects.size(); ++i)
        {
            if (objects[i].first == roundedPosX && objects[i].second == roundedPosY)
            {
                translation = glm::translate(glm::mat4(1), glm::vec3(posX, posY, 0.f));
                foundApellet = true;
                break;
            }
        }
        if (!foundApellet)
        {
            posX -= 0.5f;
            posX = std::round(posX);
            this->dir = changeDir('r');
        }
    }
    else  if (this->dir == 'l')
    {
        posX -= vt;
        bool foundApellet = false;
        int roundedPosX = std::round(posX);
        int roundedPosY = std::round(posY);
        for (int i = 0; i < objects.size(); ++i)
        {

            if (objects[i].first == roundedPosX && objects[i].second == roundedPosY)
            {
                translation = glm::translate(glm::mat4(1), glm::vec3(posX, posY, 0.f));
                foundApellet = true;
                break;
            }
        }
        if (!foundApellet)
        {
            posX += 0.5f;
            posX = std::round(posX);
            this->dir = changeDir('l');
        }
    }
    if (this->dir == 'd')
    {
        posY -= vt;
        bool foundApellet = false;
        int roundedPosX = std::round(posX);
        int roundedPosY = std::round(posY);
        for (int i = 0; i < objects.size(); ++i)
        {

            if (objects[i].first == roundedPosX && objects[i].second == roundedPosY)
            {
                translation = glm::translate(glm::mat4(1), glm::vec3(posX, posY, 0.f));
                foundApellet = true;
                break;
            }
        }
        if (!foundApellet) {
            posY += 0.5f;
            posY = std::round(posY);
            this->dir = changeDir('d');
        }
    }
    else if (this->dir == 'u')
    {
        posY += vt;
        bool foundApellet = false;
        int roundedPosX = std::round(posX);
        int roundedPosY = std::round(posY);
        for (int i = 0; i < objects.size(); ++i)
        {

            if (objects[i].first == roundedPosX && objects[i].second == roundedPosY)
            {
                translation = glm::translate(glm::mat4(1), glm::vec3(posX, posY, 0.f));
                foundApellet = true;
                break;
            }
        }
        if (!foundApellet)
        {
            posY -= 0.5f;
            posY = std::round(posY);
            this->dir = changeDir('u');
        }
    }
}

// -----------------------------------------------------------------------------
// Select textures for pacman mouth movement(interpolation)
// -----------------------------------------------------------------------------

void DynamicObject::selectTexture(float& counter, float speed, float showTexture, int& textureNr, int& textureGhostNr)
{
    counter = counter + speed;
    if (counter > 360.0)
    {
        counter = 0.0;
    }

    showTexture = glm::radians(counter);


    if (showTexture < (PI / 2) && showTexture > 0)
    {
        textureNr = 0;
        textureGhostNr = 4;
    }
    else if (showTexture <PI && showTexture >(PI / 2))
    {
        textureNr = 1;
        textureGhostNr = 5;
    }
    else if (showTexture < (PI * (3 / 2)) && showTexture > PI)
    {
        textureNr = 2;
        textureGhostNr = 6;
    }
    else if (showTexture > (PI * (3 / 2)) && showTexture < (PI * 2))
    {
        textureNr = 3;
        textureGhostNr = 7;
    }
}