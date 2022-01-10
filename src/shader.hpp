#pragma once

// Include
#include <iostream>

// Include OpenGL stuff
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Shader program
class Shader
{
    private:
        GLuint id;

    public:
        // Default constructor
        Shader() = default;

        // Constructor
        Shader(const char* vertexSource, const char* fragmentSource);

        // Give shader sources
        void setShaderSources(const char* vertexSource, const char* fragmentSource);

        // Activate
        void activate();

        // Delete
        void destroy();

        // Get shader ID
        GLuint getID();
};


