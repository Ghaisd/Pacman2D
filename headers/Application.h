class Application
{
public:



    // -----------------------------------------------------------------------------
    // Clean VAO
    // -----------------------------------------------------------------------------
    void CleanVAO(GLuint& vao)
    {
        GLint nAttr = 0;
        std::set<GLuint> vbos;

        GLint eboId;
        glGetVertexArrayiv(vao, GL_ELEMENT_ARRAY_BUFFER_BINDING, &eboId);
        glDeleteBuffers(1, (GLuint*)&eboId);

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttr);
        glBindVertexArray(vao);

        for (int iAttr = 0; iAttr < nAttr; ++iAttr)
        {
            GLint vboId = 0;
            glGetVertexAttribiv(iAttr, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &vboId);
            if (vboId > 0)
            {
                vbos.insert(vboId);
            }

            glDisableVertexAttribArray(iAttr);
        }

        for (auto vbo : vbos)
        {
            glDeleteBuffers(1, &vbo);
        }

        glDeleteVertexArrays(1, &vao);
    }



    // -----------------------------------------------------------------------------
    // Code handling the camera
    // -----------------------------------------------------------------------------
    void Camera(const float time, const GLuint shaderprogram)
    {

        //Matrix which helps project our 3D objects onto a 2D image. Not as relevant in 2D projects
        //The numbers here represent the aspect ratio. Since our window is a square, aspect ratio here is 1:1, but this can be changed.
        glm::mat4 projection = glm::ortho(0.0f, 28.0f, 0.0f, 36.0f);

        //Matrix which defines where in the scene our camera is
        //                           Position of camera     Direction camera is looking     Vector pointing upwards
        glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        //Get unforms to place our matrices into
        GLuint projmat = glGetUniformLocation(shaderprogram, "u_ProjectionMat");
        // GLuint viewmat = glGetUniformLocation(shaderprogram, "u_ViewMat");

         //Send data from matrices to uniform
        glUniformMatrix4fv(projmat, 1, false, glm::value_ptr(projection));
        //glUniformMatrix4fv(viewmat, 1, false, glm::value_ptr(view));
    }

};