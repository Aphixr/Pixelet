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
#define PXL_WINDOW_HPP_INC_D_SCF_Y

// Window namespace
namespace pxl::window
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

            /**
             * Constructor for pxl::window::Window class
             * @param width the width of the window
             * @param height the height of the window
             * @param title the title of the window
             */
            Window(unsigned int width, unsigned int height, std::string title)
            {
                // Set the attributes
                this->width = width;
                this->height = height;
                this->title = title;

                // Create the window
                window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

                // Use the window
                glfwMakeContextCurrent(window);

                // Load OpenGL
                gladLoadGL();

                // Tell area of window to render in
                glViewport(0, 0, width, height);

                // Window info
                pxl::priv::windowWidth = width;
                pxl::priv::windowHeight = height;
            }

            /**
             * If the window is open or not
             * @returns a boolean indicating if the window is open
             */
            bool isOpen()
            {
                return !glfwWindowShouldClose(window);
            }

            /**
             * Does other things that should be handled in the loop
             */
            void doRegLoopActions()
            {
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
    };

    // Get frame rate
    class FrameRate
    {
        // Private
        private:
            double lastTime = glfwGetTime();
            unsigned int numOfFrames = 0;
        
        // Public
        public:
            /**
             * Prints the frame rate into the terminal
             */
            void print()
            {
                // Measure
                double currentTime = glfwGetTime();
                numOfFrames++;

                // Give value every second
                if (currentTime - lastTime >= 1.0)
                {
                    // Print framerate
                    std::cout << "fps: " << numOfFrames << "\n";
                    
                    // Reset
                    numOfFrames = 0;
                    lastTime += 1.0;
                }
            }
    };
}

#endif






