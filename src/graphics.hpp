// Header guard
#pragma once

// Includes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Include things for OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Include Pixelet files
#include "shader.hpp"

// Pixelet namespace
namespace pxl
{
    // Private
    namespace priv
    {
        // Read file
        std::string readFile(const char* fileName);
    }

    // Triangle
    class Triangle
    {
        private:
            // Vertex shader code
            const char* vertexShaderSource =
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "uniform vec2 scale;\n"
                "void main() {\n"
                "  gl_Position = vec4(aPos.x*scale.x, aPos.y*scale.y, aPos.z, 1.f);\n"
                "}\0";
            
            // Fragment shader code
            const char* fragmentShaderSource =
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "uniform vec4 color;\n"
                "void main() {\n"
                "  FragColor = color;\n"
                "}\0";
            
            // Vertices
            GLfloat vertices[9];

            // Objects
            GLuint VAO, VBO;
            Shader shader = Shader(vertexShaderSource, fragmentShaderSource);

            // Other values
            GLfloat fillColor[4] = {1.f, 1.f, 1.f, 1.f};
            GLfloat scale[2] = {1.f, 1.f};
            bool setPosYet = false;

            // Uniforms
            GLint colorLoc = glGetUniformLocation(shader.getID(), "color");
            GLint scaleLoc = glGetUniformLocation(shader.getID(), "scale");

        public:
            // Constructor with initial positions
            Triangle(float x1, float y1, float x2, float y2, float x3, float y3);

            // Constructor without initializing anything
            Triangle();

            // Destructor
            ~Triangle();

            // Set position
            void setPosition(float x1, float y1, float x2, float y2, float x3, float y3);

            // Set fill color
            void setFill(float red, float green, float blue);

            // Set scale
            void setScale(float x, float y);

            // Draw the triangle
            void draw();
    };

    // Quadrilateral
    class Quad
    {
        private:
            // Vertex shader code
            const char* vertexShaderSource =
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "uniform vec2 scale;\n"
                "void main() {\n"
                "  gl_Position = vec4(aPos.x*scale.x, aPos.y*scale.y, aPos.z, 1.f);\n"
                "}\0";
            
            // Fragment shader code
            const char* fragmentShaderSource =
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "uniform vec4 color;\n"
                "void main() {\n"
                "  FragColor = color;\n"
                "}\0";
            
            // Vertices
            GLfloat vertices[12];
            GLuint indices[6] = {0, 1, 2, 3, 2, 1};

            // Objects
            GLuint VAO, VBO, EBO;
            Shader shader = Shader(vertexShaderSource, fragmentShaderSource);

            // Other values
            GLfloat fillColor[4] = {1.f, 1.f, 1.f, 1.f};
            GLfloat scale[2] = {1.f, 1.f};
            bool setPosYet = false;

            // Uniforms
            GLint colorLoc = glGetUniformLocation(shader.getID(), "color");
            GLint scaleLoc = glGetUniformLocation(shader.getID(), "scale");

        public:
            // Constructor with initial positions
            Quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

            // Constructor without initializing anything
            Quad();

            // Destructor
            // ~Quad();

            // Set position
            void setPosition(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

            // Set fill color
            void setFill(float red, float green, float blue);

            // Set scale
            void setScale(float x, float y);

            // Draw the quadrilateral
            void draw();
    };

    // Rectangle
    class Rect
    {
        private:
            // Vertex shader code
            const char* vertexShaderSource =
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "uniform vec2 scale;\n"
                "void main() {\n"
                "  gl_Position = vec4(aPos.x*scale.x, aPos.y*scale.y, aPos.z, 1.f);\n"
                "}\0";
            
            // Fragment shader code
            const char* fragmentShaderSource =
                "#version 330 core\n"
                "out vec4 FragColor;\n"
                "uniform vec4 color;\n"
                "void main() {\n"
                "  FragColor = color;\n"
                "}\0";
            
            // Vertices and indices
            GLfloat vertices[12];
            GLuint indices[6] = {0, 1, 2, 3, 2, 1};

            // Objects
            GLuint VAO, VBO, EBO;
            Shader shader = Shader(vertexShaderSource, fragmentShaderSource);

            // Other values
            GLfloat fillColor[4] = {1.f, 1.f, 1.f, 1.f};
            GLfloat scale[2] = {1.f, 1.f};
            bool setPosYet = false, setSizeYet = false;

            // Uniforms
            GLint colorLoc = glGetUniformLocation(shader.getID(), "color");
            GLint scaleLoc = glGetUniformLocation(shader.getID(), "scale");

        public:
            // Constructor with initial position and size
            Rect(float x, float y, float width, float height);

            // Constructor without initializing anything
            Rect();

            // Destructor
            ~Rect();

            // Set position
            void setPosition(float x, float y);

            // Set size
            void setSize(float width, float height);

            // Set fill color
            void setFill(float red, float green, float blue);

            // Set scale
            void setScale(float x, float y);
            
            // Draw the rectangle
            void draw();
    };
}


