#include "StaticObject.h"

// -----------------------------------------------------------------------------
// Draw static object using translation
// -----------------------------------------------------------------------------

void StaticObject::DrawObjects(GLuint shaderProgram, std::vector< std::pair<int, int> > objects, float r, float g, float b)
{
    auto usesTextureLocation = glGetUniformLocation(shaderProgram, "usesTexture");
    glUniform1i(usesTextureLocation, 0);
    for (int i = 0; i < objects.size(); i++)
    {
        auto vertexColorLocation = glGetUniformLocation(shaderProgram, "u_Color");
        glUniform4f(vertexColorLocation, r, g, b, 1.0f);
        GLuint transformationmat = glGetUniformLocation(shaderProgram, "u_TransformationMat");
        translation = translate(mat4(1), vec3(objects[i].first, objects[i].second, 0));
        glUniformMatrix4fv(transformationmat, 1, false, glm::value_ptr(translation));
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
    }
}

