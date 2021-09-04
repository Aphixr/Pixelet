// Header guard
#pragma once

// Includes
#include <iostream>
#include <string>

// Include OpenGL stuff
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Check if init.h file was included already
#ifndef PXL_INIT_H_INC_D
#error Include 'init.h' file before including this file
#else

// Successfully included this file
#define PXL_WINDOW_H_INC_D_SCF

// Window namespace
namespace pxl
{
    // Class for creating a window
    class Window
    {
        // Private
        private:
            // GLFW window
            GLFWwindow* window;

        // Public
        public:
            // Attributes
            unsigned int width, height;
            std::string title;

            // Constructor
            Window(unsigned int width, unsigned int height, std::string title)
            {
                // Set the attributes
                this->width = width;
                this->height = height;
                this->title = title;

                // Create the window
                this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

                // Use the window
                glfwMakeContextCurrent(window);

                // Load OpenGL
                gladLoadGL();

                // Tell area of window to render in
                glViewport(0, 0, 600, 600);
            }

            // Returns a boolean indicating if the window is open
            bool isOpen()
            {
                return !glfwWindowShouldClose(window);
            }

            // Does loop actions
            void doRegLoopActions()
            {
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
    };
}

#endif






