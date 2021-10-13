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
   
};




//
//#ifndef __GAMESHADER_H_
//#define __GAMESHADER_H_
//
//#include <string>
//
//static const std::string gameVertexShaderSrc = R"(
//#version 430 core
//
//layout(location = 0) in vec3 a_Position;
//
////We specify our uniforms. We do not need to specify locations manually, but it helps with knowing what is bound where.
////layout(location=0) uniform mat4 u_TransformationMat = mat4(1);
//layout(location=1) uniform mat4 u_ViewMat           = mat4(1);
//layout(location=2) uniform mat4 u_ProjectionMat     = mat4(1);
///** Inputs */
//in vec2 aPosition;
//in vec3 aColor;
//in vec2 aTexcoord;
//
//
///** Outputs */
//out vec3 vsColor;
//out vec2 vsTexcoord;
//
//
//
//
//void main()
//{
//vsColor = aColor;
//vsTexcoord = aTexcoord;
////We multiply our matrices with our position to change the positions of vertices to their final destinations.
//gl_Position = u_ProjectionMat * u_ViewMat * /*u_TransformationMat **/ vec4(a_Position, 1.0f);
//}
//)";
//
//static const std::string gameFragmentShaderSrc = R"(
//#version 430 core
//
///** Inputs */
//in vec3 vsColor;
//in vec2 vsTexcoord;
//
//out vec4 color;
//out vec4 outColor;
//
//uniform vec4 u_Color;
///** Binding specifies what texture slot the texture should be at (in this case TEXTURE0) */
//uniform sampler2D uTextureA;
//void main()
//{
//vec4 textColorA = texture(uTextureA, vsTexcoord);
//color = u_Color;
//if (textColorA.x > 0.95 && textColorA.y > 0.95 && textColorA.z > 0.95)
//{
//discard;
//}
//
//   outColor =  textColorA /** vec4(vsColor, 1.0)*/;
//}
//)";
//
//
//#endif 