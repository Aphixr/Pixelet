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

// Private stuff
namespace pxl::priv
{
    // Test function
    void test(const char* msg="test")
    {
        std::cout << msg << "\n";
    }
    
    // Window size
    unsigned int windowWidth, windowHeight;

    // Error class
    class Error
    {
        // Public
        public:
            // Constructors
            Error(const char* msg, bool isAuthErr=false)
            {
                if (!isAuthErr)
                    std::cout << "pxl error: " << msg << "\n";
                else
                    std::cout << "pxl author error: " << msg << "\n";
            }
            Error(std::string msg, bool isAuthErr=false)
            {
                if (!isAuthErr)
                    std::cout << "pxl error: " << msg << "\n";
                else
                    std::cout << "pxl author error: " << msg << "\n";
            }
    };

    // Global log
    int globalLog(std::string msg="test")
    {
        std::cout << msg << "\n";
        return 0;
    }
}

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






