// Header guard
#pragma once

// Defines
#ifndef PXL
#define PXL
#endif
#define PXL_WINDOW_HPP

// Includes
#include <iostream>
#include <chrono>
#include <thread>

// Includes for OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Pixelet namespace
namespace pxl
{
    // Window class
    class Window
    {
        private:
            GLFWwindow* window;
            
        public:
            // Constructor
            Window(int x, int y, unsigned int width, unsigned int height, const char* title);

            // Get width of window
            unsigned int getWidth();

            // Get height of window
            unsigned int getHeight();

            // Set position of window
            void setPosition(int x, int y);

            // Set size of window
            void setSize(unsigned int width, unsigned int height);

            // Set size limits of the window
            void setSizeLimit(unsigned int minWidth, unsigned int minHeight, unsigned int maxWidth, unsigned int maxHeight);
            
            // Set background color of the window
            void setBackground(float red, float green, float blue);

            // Returns a boolean indicating whether the window is open or not
            bool isOpen();

            // Put this inside main loop
            bool whileOpen();
    };
}


