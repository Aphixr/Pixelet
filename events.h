// Header guard
#pragma once

// Includes
#include <iostream>
#include <string>

// Include OpenGL stuff
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Check if init.h file was included already
#ifndef INIT_H_INC
#error Include 'init.h' file before including this file
#else

// Namespace
namespace pxl
{
    // Function for processing events
    void pollEvents()
    {
        glfwPollEvents();
    }
}

#endif






