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
                glViewport(0, 0, width, height);

                // Window info
                pxl::priv::windowWidth = width;
                pxl::priv::windowHeight = height;
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

    // Get frame rate
    class FrameRate
    {
        // Private
        private:
            double lastTime = glfwGetTime();
            unsigned int numOfFrames = 0;
        
        // Public
        public:
            // Limited FPS
            unsigned int fps;

            // Constructor
            FrameRate(unsigned int fpsLimit=60)
            {
                fps = fpsLimit;
            }

            // Print FPS, put this inside while loop
            int print()
            {
                // Measure
                double currentTime = glfwGetTime();
                numOfFrames++;

                // Give value every second
                if (currentTime - lastTime >= 1.0)
                {
                    std::cout << "fps: " << numOfFrames << "\n";
                    
                    // Reset
                    // const unsigned int tempNOF = numOfFrames;
                    numOfFrames = 0;
                    lastTime += 1.0;

                    // Return FPS
                    // return tempNOF;
                    return 0;
                }

                // Return -1 if cannot give value yet
                return -1;
            }

            // Returns boolean deciding whether to display next frame or not
            bool allowNextFrame()
            {
                // Measure
                double currentTime = glfwGetTime();

                // Checks if reached set FPS limit
                if (currentTime - lastTime >= 1.0 / (double)fps)
                {
                    lastTime += 1.0 / (double)fps;
                    return true;
                }
                else return false;
            }
    };
}

#endif






