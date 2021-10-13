#include "headers/Libraries.h"
#include "shaders/GameShader.h"
#include <algorithm>
#include "headers/Application.h"
#include "headers/Map.h"
#include "headers/Pacman.h"
#include "headers/Ghost.h"
#include "headers/Wall.h"
#include "headers/Pellet.h"
#include "headers/Window.h"
#include "headers/Texture.h"    
#include "headers/Shader.h"

Application app;
Map map;
Wall wall;
Pellet pellet;
Pacman pacman;
Ghost ghost;
Window w("Pacman2D", 900, 1157);
Texture texture;
Shader shader(gameVertexShaderSrc, gameFragmentShaderSrc);

// Entry point
int main(void)
{
    glEnable(GL_MULTISAMPLE);
    // Clear the background
    glClearColor(0.f, 0.0f, 0.0f, 1.0f);
    map.LoadMap("level0");
    map.generateGhosts();

    wall.CreateObject(shader.getID(), wall.wallInitPos,0); //0 == false , 1 == true
    pellet.CreateObject(shader.getID(), pellet.pelletInitPos,0);
    pacman.CreateObject(shader.getID(), pacman.pacmanInitPos,1);
    ghost.CreateObject(shader.getID(), ghost.ghostInitPos,1);
    
    map.walkable.push_back(std::make_pair(pacman.getPosX(), pacman.getPosY()));
    pacman.srcPellet = map.v_pacman[0];
    pacman.dstPellet = std::pair<int, int>(-1, -1);
    for (int i = 0; i < 4; i++) {
        ghost.srcPellets[i] = map.v_ghosts[i];
        ghost.dstPellets[i] = std::pair<int, int>(-1, -1);
    }
    float currentTime = 0.0;
    float lastTime = 0.0;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetTime(0.0);
    std::cout << "Debug is disabled! because in some graph cards it gives so many meaningless warnings (use static instead of dynamic) can be enabled from Window.cpp line 62" << std::endl;
    glUseProgram(shader.getID());
    std::vector<GLuint>textures(8);
    /*Load the texture image, create OpenGL texture, and bind it to the current context*/
    textures[3] = texture.load_opengl_texture("textures/PacmanRight1.png", 3);
    textures[1] = texture.load_opengl_texture("textures/PacmanRight2.png", 1);
    textures[2] = texture.load_opengl_texture("textures/PacmanRight3.png", 0);
    textures[0] = texture.load_opengl_texture("textures/PacmanRight.png", 2);
    textures[4] = texture.load_opengl_texture("textures/ghostLeft.png", 4);
    textures[5] = texture.load_opengl_texture("textures/ghostUp.png", 5);
    textures[6] = texture.load_opengl_texture("textures/ghostRight.png", 6);
    textures[7] = texture.load_opengl_texture("textures/ghostDown.png", 7);
    
    float counter = 0.0f;
    float speed = 35; //increament of angle in radian
    float showTexture;
    // Main loop
    int textureNr = 2;
    int textureGhostNr = 4;
    int keyState;
    while(!glfwWindowShouldClose(w.m_Window))
    { 
       // shader.Bind();
        glfwPollEvents();

        keyState = glfwGetKey(w.m_Window, GLFW_KEY_F);
        if (keyState == GLFW_PRESS) {
            w.switchFullScreen(true);
        }
        keyState = glfwGetKey(w.m_Window, GLFW_KEY_H);
        if (keyState == GLFW_PRESS) {
            w.switchFullScreen(false);
        }
        //I used the 4 quadrants of the angular coordinate to select one of the 4 textures.
   //everytime angle exceeds 360 degree, it reset to 0.
   //You can change the speed to slow down or speedup the mouth opening


        counter = counter + speed;
        if (counter > 360.0)
        {
            counter = 0.0;
        }

        showTexture = glm::radians(counter);

      

        if (showTexture < (3.14 / 2) && showTexture > 0)
        {
            textureNr = 0;
            textureGhostNr = 4;
        }
        else if (showTexture < 3.14 && showTexture >(3.14 / 2))
        {
            textureNr = 1;
            textureGhostNr = 5;
        }
        else if (showTexture < (3.14 * (3 / 2)) && showTexture > 3.14)
        {
            textureNr = 2;
            textureGhostNr = 6;
        }
        else if (showTexture > (3.14 * (3 / 2)) && showTexture < (3.14 * 2))
        {
            textureNr = 3;
            textureGhostNr = 7;
        }


        // Time management
        app.Camera(currentTime, shader.getID());
        currentTime = (float)glfwGetTime();
        double deltaTime = (double)(currentTime - lastTime);
        lastTime = currentTime;
        glClear(GL_COLOR_BUFFER_BIT); 

        
        // Draw Walls      
        wall.DrawObjects(shader.getID(), map.walls, 0.352, 0.372, 0.847);
        // Draw Pellets.     
        GLuint isCircleLocation = glGetUniformLocation(shader.getID(), "isCircle");
        glUniform1i(isCircleLocation, 1);
        pellet.DrawObjects(shader.getID(), map.pellets, 0.905, 0.854, 0.615, map.isMagic);
        glUniform1i(isCircleLocation, 0);
        // Draw Pacman
       
        pacman.DrawObjects(shader.getID(), map.v_pacman, 0.933, 0.901, 0.066, textures,textureNr);

        //Draw Ghosts
        ghost.DrawObjects(shader.getID(), map.v_ghosts, 0.937, 0.043, 0.043,textures, textureGhostNr);
        if (pacman.pacGhostsCollision(ghost.ghostX, ghost.ghostY, map.v_ghosts) || pellet.allPelletsEaten(pacman.eatenPellets, map.pellets))
            break;
        glfwSwapBuffers(w.m_Window);
      
        // Exit the loop if escape is pressed
        if (glfwGetKey(w.m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        pacman.PacmanInput(w.m_Window, shader.getID(), deltaTime, map.walkable);
        ghost.moveBetweenPellets(map.walkable, map.v_ghosts, deltaTime);

        pacman.eatPellets(pacman.getPosX(), pacman.getPosY(), map.pellets);
        
    }

    glfwTerminate();

    app.CleanVAO(wall.GetVao());
    app.CleanVAO(pellet.GetVao());
    app.CleanVAO(pacman.GetVao());
    app.CleanVAO(ghost.GetVao());

    return EXIT_SUCCESS;
}




