#include "pixelet.hpp"

// Initialize Pixelet
void pxl::init()
{
    // Initialize GLFW
    glfwInit();

    // Version of OpenGL (3.3 core)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// Terminate Pixelet
void pxl::exit()
{
    glfwTerminate();
}


