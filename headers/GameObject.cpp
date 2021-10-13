#include "GameObject.h"

void GameObject::CreateObject(GLuint shaderProgram, std::vector<GLfloat> objects,int usesTexture)
{
    this->usesTexture = usesTexture;
    GLuint square_indices[6] = { 0,1,2,0,2,3 };

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_DYNAMIC_DRAW);

}

void GameObject::DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects, float r, float g, float b)
{
    auto usesTextureLocation = glGetUniformLocation(shaderProgram,"usesTexture");
    glUniform1i(usesTextureLocation, usesTexture);
    for (int i = 0; i < objects.size(); i++)
    {
        auto vertexColorLocation = glGetUniformLocation(shaderProgram, "u_Color");
        glUniform4f(vertexColorLocation, r, g, b, 1.0f);
        GLuint transformationmat = glGetUniformLocation(shaderProgram, "u_TransformationMat");
        if (r == 0.933f || r == 0.937f)
        {

        translation = translate(mat4(1), vec3( posX, posY, 0));
        }
        else
            translation = translate(mat4(1), vec3(objects[i].first, objects[i].second, 0));

        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(translation));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);

    }
}

void GameObject::GhostMovement(GLFWwindow* window, GLuint shaderProgram, float deltaTime, const std::vector< std::pair<int, int> >& objects, char dir)
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
            if (objects[i].first == roundedPosX &&objects[i].second==roundedPosY) 
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
    void GameObject::ObjectInput(GLFWwindow * window, GLuint shaderProgram, float deltaTime, const std::vector< std::pair<int, int> >& objects)
    {
        glm::mat4 rotation;
        float vt = vel * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            posX += vt;
           
            collision(posX, posY, objects, 'r');

        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            posX -= vt;
            collision(posX, posY, objects, 'l');
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            posY -= vt;
            collision(posX, posY, objects, 'd');
        }
        else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            posY += vt;
            collision(posX, posY, objects, 'u');
        }
    }

    char GameObject::collision(float& X, float& Y, std::vector< std::pair<int, int> > objects , char dir)
    {
        float  distX;
        float  distY;
        for (int i = 0; i < objects.size(); ++i) 
        {
            distX = std::abs(posX - objects[i].first);
            distY = std::abs(posY - objects[i].second);
            if (distX < 0.5f && distY < 0.5f) 
            {
                switch (dir)
                {
                case 'r': 
                    posX -= 0.5f;
                    posX = std::round(posX);
                    break;
                case 'l':
                    posX += 0.5f;
                    posX = std::round(posX);
                    break;
                case 'u':
                    posY -= 0.5f;
                    posY = std::round(posY);
                    break;
                case 'd':
                    posY += 0.5f;
                    posY = std::round(posY);
                    break;
                }
            }
        }
        return dir;
    }

    char GameObject::changeDir(char dir)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 2); // distribution in range [0, 2].
        int dirValue = dist2(rng);
        std::vector <char> directions = { 'l', 'r', 'u', 'd' };
        directions.erase(std::remove(directions.begin(), directions.end(), dir), directions.end());
        return directions[dirValue];
    }

    float GameObject::getPosX()
    {
        return posX;
    }

    float GameObject::getPosY()
    {
        return posY;
    }

    GLuint& GameObject::GetVao()
    {
        return vao;
    }
