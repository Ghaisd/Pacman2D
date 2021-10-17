#include "headers/Libraries.h"
#include "shaders/GameShader.h"
#include "headers/Application.h"
#include "headers/Window.h"
#include "headers/Texture.h"    
#include "headers/Shader.h"
#include "headers/Map.h"
#include "headers/Pacman.h"
#include "headers/Ghost.h"
#include "headers/Wall.h"
#include "headers/Pellet.h"

Application app;
Map map("level0");
Wall wall;
Pellet pellet;
Pacman pacman;
Ghost ghost;
Window w("Pacman2D", 900, 1157);
Texture texture;
Shader shader(gameVertexShaderSrc, gameFragmentShaderSrc);

int main(void)
{

    wall.CreateObject(wall.wallInitPos);
    pellet.CreateObject(pellet.pelletInitPos);
    pacman.CreateObject(pacman.pacmanInitPos);
    ghost.CreateObject(ghost.ghostInitPos);

    pacman.srcPellet = map.v_pacman[0];
    pacman.dstPellet = std::pair<int, int>(-1, -1);
    for (int i = 0; i < 4; i++) {
        ghost.srcPellets[i] = map.v_ghosts[i];
        ghost.dstPellets[i] = std::pair<int, int>(-1, -1);
    }

    glfwSetTime(0.0);
    std::vector<GLuint>textures(8);
    double currentTime = 0.0,
        lastTime = 0.0;
    float showTexture = 0,
        counter = 0.0f,
        speed = 35;    //increament of angle in radian
    int textureNr = 2,
        textureGhostNr = 4;

    texture.loadAlltextures(textures);
    // Game loop
    while (!glfwWindowShouldClose(w.m_Window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader.getID());
      
        w.changeFullScreen();
        pacman.selectTexture(counter, speed, showTexture, textureNr, textureGhostNr);
        // Time management
        app.Camera(currentTime, shader.getID());
        currentTime = (float)glfwGetTime();
        double deltaTime = (double)(currentTime - lastTime);
        lastTime = currentTime;
        // Draw Walls      
        wall.DrawObjects(shader.getID(), map.walls, 0.352, 0.372, 0.847);
        // Draw Pellets.     
        GLuint isCircleLocation = glGetUniformLocation(shader.getID(), "isCircle");
        glUniform1i(isCircleLocation, 1);
        pellet.DrawObjects(shader.getID(), map.pellets, 0.905, 0.854, 0.615, map.isMagic);
        glUniform1i(isCircleLocation, 0);
        // Draw Pacman
        pacman.DrawObjects(shader.getID(), map.v_pacman, textures, textureNr);
        //Draw Ghosts
        ghost.DrawObjects(shader.getID(), map.v_ghosts, 1.0, 0.0, 0.0, textures, textureGhostNr);
        if ((glfwGetKey(w.m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) || pacman.pacGhostsCollision(ghost.ghostX, ghost.ghostY, map.v_ghosts)
            || pellet.allPelletsEaten(pacman.eatenPellets, map.pellets))
            break;
        pacman.PacmanInput(w.m_Window, shader.getID(), deltaTime, map.walkable);
        ghost.moveBetweenPellets(map.walkable, map.v_ghosts, deltaTime);
        pacman.eatPellets(pacman.getPosX(), pacman.getPosY(), map.pellets);

        glfwSwapBuffers(w.m_Window);
        glfwPollEvents();
    }
    glfwTerminate();

    app.CleanVAO(wall.GetVao());
    app.CleanVAO(pellet.GetVao());
    app.CleanVAO(pacman.GetVao());
    app.CleanVAO(ghost.GetVao());

    return EXIT_SUCCESS;
}

