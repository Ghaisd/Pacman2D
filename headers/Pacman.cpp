#include "Pacman.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace std;
void Pacman::PacmanInput(GLFWwindow* window, GLuint shaderProgram, float deltaTime,
    std::vector<std::pair<int, int>> pellets)
{
   
    float velocity = vel * deltaTime;
    if (dstPellet.first == -1)
    {
        findDst(pellets);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        inputDir = 'r';
        rotation = glm::rotate(mat4(1.0f), PI, glm::vec3(0, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        inputDir = 'l';
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        inputDir = 'd';
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        inputDir = 'u';
    }
    if (!canWalk)
    {
        velocity = 0;
        canWalk = findDst(pellets);
    }
    switch (dir)
    {
    case 'r':

        posX += velocity;
        if (posX > (float)dstPellet.first)
        {
            posX = dstPellet.first;
            posY = dstPellet.second;
            srcPellet = dstPellet;
            canWalk = findDst(pellets);
        }

        break;
    case 'l':

        posX -= velocity;
        if (posX < (float)dstPellet.first)
        {
            posX = dstPellet.first;
            posY = dstPellet.second;
            srcPellet = dstPellet;
            canWalk = findDst(pellets);
        }

        break;
    case 'u':

        posY += velocity;
        if (posY > (float)dstPellet.second)
        {
            posX = dstPellet.first;
            posY = dstPellet.second;
            srcPellet = dstPellet;
            canWalk = findDst(pellets);
        }

        break;
    case 'd':

        posY -= velocity;
        if (posY < (float)dstPellet.second)
        {
            posX = dstPellet.first;
            posY = dstPellet.second;
            srcPellet = dstPellet;
            canWalk = findDst(pellets);
        }

        break;
    }
}
bool Pacman::findDst(const std::vector<std::pair<int, int>>& pellets)
{
    vector<pair<int, int>> candidtates(4, srcPellet); //srcpallet 5,7
    candidtates[0].first++;                           // 6,7
    candidtates[1].first--;                           //5,7
    candidtates[2].second++;                          // 6,8
    candidtates[3].second--;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < pellets.size(); j++)
        {
            if (candidtates[i].first == pellets[j].first && candidtates[i].second == pellets[j].second)
            {
                if (inputDir == 'r' && i == 0 ||
                    inputDir == 'l' && i == 1 ||
                    inputDir == 'u' && i == 2 ||
                    inputDir == 'd' && i == 3)
                {
                    dir = inputDir;
                    dstPellet = candidtates[i];
                    return true;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < pellets.size(); j++)
        {
            if (candidtates[i].first == pellets[j].first && candidtates[i].second == pellets[j].second)
            {
                if (dstPellet.first == -1)
                {
                    dstPellet = candidtates[i];
                    switch (i)
                    {
                    case 0:
                        dir = 'r';
                        break;
                    case 1:
                        dir = 'l';
                    case 2:
                        dir = 'u';
                    case 3:
                        dir = 'd';
                    }
                    inputDir = dir;
                    return true;
                }
                if (dir == 'r' && i == 0 ||
                    dir == 'l' && i == 1 ||
                    dir == 'u' && i == 2 ||
                    dir == 'd' && i == 3)
                {
                    dstPellet = candidtates[i];
                    passedReg++;
                    if (passedReg == 2)
                    {
                        inputDir = dir;
                        passedReg = 0;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
void Pacman::setupAttrib() {
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
}

void Pacman::DrawObjects(GLuint shaderProgram, std::vector<std::pair<int, int>> objects, float r, float g, float b, std::vector<GLuint> textures,int index)
{
    auto usesTextureLocation = glGetUniformLocation(shaderProgram, "usesTexture");
    glUniform1i(usesTextureLocation, usesTexture);
        glBindTexture(GL_TEXTURE_2D, textures[index]);
        setPos(posX , posY);
        auto vertexColorLocation = glGetUniformLocation(shaderProgram, "u_Color");
        glUniform4f(vertexColorLocation, r, g, b, 1.0f);
        GLuint transformationmat = glGetUniformLocation(shaderProgram, "u_TransformationMat");
        translation = translate(mat4(1), vec3(posX, posY, 0));
        rotation = setRotationDir();
        transformation = translation* rotation;
        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(transformation));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
     
   
}

void Pacman::setPos(float pacmanX, float pacmanY)
{
    posX = pacmanX;
    posY = pacmanY;
}

glm::mat4 Pacman::setRotationDir()
{
    glm::mat4 translateBeforeRotation;

    glm::mat4 rotation;
    switch (dir)
    {
    case 'l':
        translateBeforeRotation = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        rotation = glm::rotate(glm::mat4(1.0f), PI, glm::vec3(0, 0, 1)) * translateBeforeRotation;
        break;
    case 'u':
        translateBeforeRotation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(glm::mat4(1.0f), PI / 2, glm::vec3(0, 0, 1)) * translateBeforeRotation;
        break;
    case 'd':
        translateBeforeRotation = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(glm::mat4(1.0f), -PI / 2, glm::vec3(0, 0, 1)) * translateBeforeRotation;
        break;
    default:
        rotation = mat4(1.0f);
        break;
    }
    return rotation;
}

bool Pacman::CheckCollision(float posX1, float posY1, float posX2, float posY2, float collisionDistance)
{
    vec2 A(posX1, posY1);
    vec2 B(posX2, posY2);
    float length = glm::length(A - B);
    return length < collisionDistance;
}

void Pacman::eatPellets(float x1, float y1, std::vector<std::pair<int, int> >& objects)
{

    for (int i = 0; i < objects.size(); i++)
    {
        float pelletsX = objects[i].first;
        float pelletsY = objects[i].second;

        if (CheckCollision(x1, y1, pelletsX, pelletsY, 0.4f))
        {
            objects[i].first = -2;
            objects[i].second = -2;
            eatenPellets++;
        }
    }
}

bool Pacman::pacGhostsCollision(std::vector <float> ghostX, std::vector <float> ghostY, std::vector<std::pair<int, int> > v_ghosts)
{
    if (CheckCollision(posX, posY, ghostX[0] + v_ghosts[0].first, ghostY[0] + v_ghosts[0].second, 0.5f))
    {
        return true;
    }
    if (CheckCollision(posX, posY, ghostX[1] + v_ghosts[1].first, ghostY[1] + v_ghosts[1].second, 0.5f))
    {
        return true;
    }
    if (CheckCollision(posX, posY, ghostX[2] + v_ghosts[2].first, ghostY[2] + v_ghosts[2].second, 0.5f))
    {
        std::cout << "Collison " << std::endl;
        return true;
    }
    if (CheckCollision(posX, posY, ghostX[3] + v_ghosts[3].first, ghostY[3] + v_ghosts[3].second, 0.5f))
    {
        std::cout << "Collison " << std::endl;
        return true;
    }
    return false;
}