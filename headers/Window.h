#include "Libraries.h"

class Window
{
public:
    GLFWwindow* m_Window = NULL;
    GLFWmonitor* monitor = NULL;
    const GLFWvidmode* videoMode;
    GLuint m_Width, m_Height;
    const char* m_Title;
    int frameWidth, frameHeight,
    keyState = 0;
public:

    Window(const char* title, int width, int height);
    static void handleResize(GLFWwindow* window, int height, int width);
    void switchFullScreen(bool fullScreen);
    void changeFullScreen();

};