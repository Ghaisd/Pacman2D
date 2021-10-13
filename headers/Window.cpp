#include "Window.h"
Window::Window(const char* title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height) {
    auto GLFWErrorCallback = [](int code, const char* description)
    {
        std::cerr << "Error " << "0x" << std::hex << code << ':' << description << "\n";
    };

    glfwSetErrorCallback(GLFWErrorCallback);

    // Initialization of glfw.
    if (!glfwInit())
    {
        std::cin.get();

     //   return EXIT_FAILURE;
        return;
    }

    // Create a window
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    if (m_Window == nullptr)
    {

        glfwTerminate();

        std::cin.get();

        //return EXIT_FAILURE;
        return;
    }
    glfwSetWindowSizeCallback(m_Window, Window::handleResize);
    monitor = glfwGetPrimaryMonitor();
    videoMode = glfwGetVideoMode(monitor);
    //Set the OpenGL context
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
       // return EXIT_FAILURE;
        return;
    }

    // Error function for OpenGL
    auto GLAPIENTRY
        MessageCallback = [](GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
    {
        // std::cerr << "GL CALLBACK:" << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
        //     "type = 0x" << type <<
        //     ", severity = 0x" << severity <<
        //     ", message =" << message << "\n";
    };

    //  // Eanable capture of debug output.
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);


    // Enable capture of debug output.
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    glfwGetFramebufferSize(m_Window, &frameWidth, &frameHeight);

    //return 1;
    return;
}


void Window::handleResize(GLFWwindow* window, int height, int width) {
    int h, w;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
}
void Window::switchFullScreen(bool fullScreen) {
    if (fullScreen == true) {
        glfwSetWindowMonitor(m_Window, monitor, 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
        glViewport(0, 0, videoMode->width, videoMode->height);
    }
    else {
        glfwSetWindowPos(m_Window, 50, 50);
        glfwSetWindowMonitor(m_Window, nullptr, 30, 30,frameWidth,frameHeight, videoMode->refreshRate);
        glViewport(0, 0, frameWidth, frameHeight);
    }
}
