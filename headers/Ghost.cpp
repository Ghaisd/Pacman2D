#include "Ghost.h"
using namespace glm;
using namespace std;


void Ghost::moveBetweenPellets(const std::vector<std::pair<int, int>>& pellets,
    vector<pair<int, int>>& ghosts, float deltaTime)
{
    for (int i = 0; i < 4; i++) {
        if (dstPellets[i].first == -1)
        {
            findDst(pellets,i);
        }
        if (dstPellets[i].second > srcPellets[i].second)
        {
            dir[i] = 'u';
        }
        else if (dstPellets[i].second < srcPellets[i].second)
        {
            dir[i] = 'd';
        }
        else if (dstPellets[i].first > srcPellets[i].first)
        {
            dir[i] = 'r';
        }
        else if (dstPellets[i].first < srcPellets[i].first)
        {
            dir[i] = 'l';
        }
        float velocity = vel * deltaTime;
        switch (dir[i])
        {
        case 'u':
            ghostY[i] += velocity;
            if (ghostY[i] + (float)ghosts[i].second > (float)dstPellets[i].second)
            {
                ghostY[i] = 0;
                ghosts[i] = dstPellets[i];
                srcPellets[i] = dstPellets[i];
                findDst(pellets,i);
            }
            break;
        case 'd':
            ghostY[i] -= velocity;
            if (ghostY[i] + (float)ghosts[i].second < (float)dstPellets[i].second)
            {
                ghostY[i] = 0;
                ghosts[i] = dstPellets[i];
                srcPellets[i] = dstPellets[i];
                findDst(pellets,i);
            }
            break;
        case 'r':
            ghostX[i] += velocity;
            if (ghostX[i] + (float)ghosts[i].first > (float)dstPellets[i].first)
            {
                ghostX[i] = 0;
                ghosts[i] = dstPellets[i];
                srcPellets[i] = dstPellets[i];
                findDst(pellets,i);
            }
            break;
        case 'l':
            ghostX[i] -= velocity;
            if (ghostX[i] + (float)ghosts[i].first < (float)dstPellets[i].first)
            {
                ghostX[i] = 0;
                ghosts[i] = dstPellets[i];
                srcPellets[i] = dstPellets[i];
                findDst(pellets,i);
            }
            break;
        }
    }
}

void Ghost::findDst(const std::vector<std::pair<int, int>>& pellets, int index)
{
    vector<pair<int, int>> candidtates(4, srcPellets[index]); //srcpallet 5,7
    vector<int> passed;
    candidtates[0].first++; // 6,7
    candidtates[1].first--; //5,7
    candidtates[2].second++; // 6,8
    candidtates[3].second--; //6,5
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < pellets.size(); j++)
        {
            if (candidtates[i].first == pellets[j].first && candidtates[i].second == pellets[j].second)
            {
                if (dir[index] == 'r' && i == 0 ||
                    dir[index] == 'l' && i == 1 ||
                    dir[index] == 'u' && i == 2 ||
                    dir[index] == 'd' && i == 3)
                    
                {
                    dstPellets[index] = candidtates[i];
                    return;
                }
                passed.push_back(i);
            }
        }
    }
    int random = rand();
    random = random % passed.size();
    int randomIndex = passed[random];
    dstPellets[index] = candidtates[randomIndex];
}
void Ghost::DrawObjects(GLuint shaderProgram, std::vector<std::pair<int, int>> objects, float r, float g, float b, std::vector<GLuint> textures, int index)
{
    for (int i = 0; i < 4; i++)
    {
        int n=4;
        glBindTexture(GL_TEXTURE_2D, textures[index]);
        setPos(ghostX[i] + objects[i].first, ghostY[i] + objects[i].second);
        auto vertexColorLocation = glGetUniformLocation(shaderProgram, "u_Color");
        glUniform4f(vertexColorLocation, r, g, b, 1.0f);
        GLuint transformationmat = glGetUniformLocation(shaderProgram, "u_TransformationMat");
        translation = translate(mat4(1), vec3(posX, posY, 0));
        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(translation));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
     
    }
}

float Ghost::ghostPosX()
{
    return posX;
}
float Ghost::ghostPosY()
{
    return posY;
}

void Ghost::setPos(float x, float y)
{
    posX = x;
    posY = y;
}

