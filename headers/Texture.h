#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:

    GLuint load_opengl_texture(const std::string& filepath, GLuint slot)
    {
        /**
         *  - Use the STB Image library to load a texture in here
         *  - Initialize the texture into an OpenGL texture
         *    - This means creating a texture with glGenTextures or glCreateTextures (4.5)
         *    - And transferring the loaded texture data into this texture
         *    - And setting the texture format
         *  - Finally return the valid texture
         */

         /** Image width, height, bit depth */
        int w, h, bpp;
        auto pixels = stbi_load(filepath.c_str(), &w, &h, &bpp, STBI_rgb_alpha);

        /*Generate a texture object and upload the loaded image to it.*/
        GLuint tex;
        glGenTextures(1, &tex);
        //glActiveTexture(GL_TEXTURE0 + slot);//Texture Unit
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        /** Set parameters for the texture */
        //Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //Filtering 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /** Very important to free the memory returned by STBI, otherwise we leak */
        if (pixels)
            stbi_image_free(pixels);

        return tex;
    }

// -----------------------------------------------------------------------------
// Load the texture image, create OpenGL texture, and bind it to the current context
// -----------------------------------------------------------------------------
    void loadAlltextures(std::vector<GLuint>& textures)
    {
        textures[0] = load_opengl_texture("textures/PacmanRight.png", 2);
        textures[1] = load_opengl_texture("textures/PacmanRight2.png", 1);
        textures[2] = load_opengl_texture("textures/PacmanRight3.png", 0);
        textures[3] = load_opengl_texture("textures/PacmanRight1.png", 3);
        textures[4] = load_opengl_texture("textures/ghostLeft.png", 4);
        textures[5] = load_opengl_texture("textures/ghostUp.png", 5);
        textures[6] = load_opengl_texture("textures/ghostRight.png", 6);
        textures[7] = load_opengl_texture("textures/ghostDown.png", 7);
    }

};

