// Header guard
#pragma once

// Macro for seeing if this file was included first
#define PXL_INIT_H_INC_D

// Includes
#include <iostream>
#include <string>

// Include OpenGL stuff
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Namespace
namespace pxl
{
    // Initialize everything
    void init()
    {
        // Initialize GLFW
        glfwInit();

        // Tell GLFW which version of OpenGL to use (3.3) and profile (core)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    // Exit program; call this function when program is going to end
    void exit()
    {
        glfwTerminate();
    }

    // Hold info that can be used in different functions
    class InfoHolder
    {
        // Public
        public:
            // Constructor
            InfoHolder()
            {
                
            }
    };
}






