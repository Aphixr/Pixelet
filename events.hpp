// Header guard
#pragma once

// Includes
#include <iostream>
#include <string>

// Include OpenGL stuff
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Check if init.h file was included already
#ifndef PXL_INIT_HPP_INC_D_SCF_Y
#error Include 'init.hpp' file before including this file
#else

// Successfully included this file
#define PXL_EVENTS_HPP_INC_D_SCF_Y

// Namespace
namespace pxl
{
    /**
     * Function for processing events
     */
    void pollEvents()
    {
        glfwPollEvents();
    }
}

#endif






