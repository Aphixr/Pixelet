// Header guard
#pragma once

// Includes
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

// Include OpenGL stuff
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Check if init.h file was included already
#ifndef PXL_INIT_H_INC_D
#error Include 'init.h' file before including this file
#else

// Successfully included this file
#define PXL_GRAPHICS_H_INC_D_SCF

// Private classes, functions, etc., that should normally not be accessed
namespace pxl::priv
{
    // Read a file
    std::string readFile(const char* fileName)
    {
        std::ifstream in(fileName, std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return contents;
        }
        throw errno;
    }

    // Shader program class
    class Shader
    {
        // Private
        private:
            // Checks for any GLSL compile errors
            void compileErrors(unsigned int shader, const char* type)
            {
                // Variables
                GLint hasCompiled;
                char infoLog[1024];

                if (type != "PROGRAM")
                {
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
                    if (hasCompiled == GL_FALSE)
                    {
                        // Get info
                        glGetShaderInfoLog(shader, 1024, NULL, infoLog);

                        // Print error
                        std::cout << "SHADER COMPILATION " << type << " ERROR\n" << std::endl;
                    }
                }
                else
                {
                    glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
                    if (hasCompiled == GL_FALSE)
                    {
                        // Get info
                        glGetProgramInfoLog(shader, 1024, NULL, infoLog);

                        // Print error
                        std::cout << "SHADER LINKING " << type << " ERROR\n" << std::endl;
                    }
                }
            }

        // Public
        public:
            GLuint id;

            // Constructor
            Shader(const char* vertexSource, const char* fragmentSource)
            {
                // Create vertex shader
                GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertexSource, NULL);
                glCompileShader(vertexShader);
                this->compileErrors(vertexShader, "VERTEX");

                // Create fragment shader
                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
                glCompileShader(fragmentShader);
                this->compileErrors(fragmentShader, "FRAGMENT");

                // Create shader program
                this->id = glCreateProgram();

                // Attach shaders to shader program
                glAttachShader(this->id, vertexShader);
                glAttachShader(this->id, fragmentShader);

                // Wrap up the shader program
                glLinkProgram(this->id);
                compileErrors(this->id, "PROGRAM");

                // Delete shaders
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
            }

            // Activate
            void activate()
            {
                glUseProgram(id);
            }

            // Delete
            void del()
            {
                glDeleteProgram(id);
            }
    };

    // Vertex buffer object class
    class VBO
    {
        // Public
        public:
            GLuint id;

            // Constructor
            VBO(GLfloat* vertices, GLsizeiptr size)
            {
                // Generate buffers
                glGenBuffers(1, &this->id);

                // Specify array buffer
                // glBindBuffer(GL_ARRAY_BUFFER, this->id);
                this->bind();

                // Give vertices to VBO
                glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
            }

            // Bind
            void bind()
            {
                glBindBuffer(GL_ARRAY_BUFFER, this->id);
            }

            // Unbind
            void unbind()
            {
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }

            // Delete
            void del()
            {
                glDeleteBuffers(1, &id);
            }
    };

    // Vertex array object class
    class VAO
    {
        // Public
        public:
            GLuint id;

            // Constructor
            VAO()
            {
                glGenVertexArrays(1, &this->id);
            }

            // Link
            void linkAttrib(pxl::priv::VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
            {
                VBO.bind();

                // Tell OpenGL how to read VBO
                glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
                glEnableVertexAttribArray(layout);

                VBO.unbind();
            }

            // Bind
            void bind()
            {
                glBindVertexArray(this->id);
            }

            // Unbind
            void unbind()
            {
                glBindVertexArray(0);
            }

            // Delete things
            void del()
            {
                glDeleteVertexArrays(1, &this->id);
            }
    };

    // EBO class
    class EBO
    {
        // Public
        public:
            GLuint id;

            // Constructor
            EBO(GLuint* indices, GLsizeiptr size)
            {
                // Generate buffer
                glGenBuffers(1, &this->id);

                // Specify array buffer
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);

                // Give vertices to VBO
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
            }

            // Bind
            void bind()
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
            }

            // Unbind
            void unbind()
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            // Delete
            void del()
            {
                glDeleteBuffers(1, &this->id);
            }
    };
}

// Draw namespace
namespace pxl::graphics
{
    // Stores current color used for coloring shapes
    float curFillColor[4] = {255, 255, 255, 255};
    float curStrokeColor[4] = {0, 0, 0, 0};

    // Draw the background
    void background(float red, float green, float blue, float alpha=1.f)
    {
        glClearColor(red/255, green/255, blue/255, alpha/255);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Set the fill color
    void fill(float red, float green, float blue, float alpha=1.f)
    {
        curFillColor[0] = red;
        curFillColor[1] = green;
        curFillColor[2] = blue;
        curFillColor[3] = alpha;
    }

    // Set the outline color
    void stroke(float red, float green, float blue, float alpha=1.f)
    {
        curStrokeColor[0] = red;
        curStrokeColor[1] = green;
        curStrokeColor[2] = blue;
        curStrokeColor[3] = alpha;
    }

    // Draw a rectangle
    void rect(float x, float y, float width, float height)
    {

    }

    // Draw a triangle
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        // Vertex shader code
        const char* vertexShaderSource =
            "#version 330 core                                        \n"
            "layout (location = 0) in vec3 aPos;                      \n"
            "void main()                                              \n"
            "{                                                        \n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.f);     \n"
            "}                                                        \0";
        
        // Convert the RGBA values from a range of from 0-255 to a range of 0-1
        const std::string glsFillAsStr[4] =
        {
            std::to_string(curFillColor[0] / 255),
            std::to_string(curFillColor[1] / 255),
            std::to_string(curFillColor[2] / 255),
            std::to_string(curFillColor[3] / 255)
        };
        
        // Fragment shader code
        const std::string fragmentShaderSourceAsStdStr =
            "#version 330 core                                  \n"
            "out vec4 FragColor;                                \n"
            "void main()                                        \n"
            "{                                                  \n"
            "    FragColor = vec4(" + glsFillAsStr[0] + "f,     \n"
            "                     " + glsFillAsStr[1] + "f,     \n"
            "                     " + glsFillAsStr[2] + "f,     \n"
            "                     " + glsFillAsStr[3] + "f);    \n"
            "}                                                  \0";
        const char* fragmentShaderSource = fragmentShaderSourceAsStdStr.c_str();

        // Shader
        pxl::priv::Shader shader(vertexShaderSource, fragmentShaderSource);
        
        /*
        // Vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        
        // Fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Shader program
        GLuint shaderProgram = glCreateProgram();

        // Attach shaders to shader program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Delete the now useless shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        */

        // Coordinates of triangle
        GLfloat vertices[9] =
        {
            x1, y1, 0.f,
            x2, y2, 0.f,
            x3, y3, 0.f
        };

        pxl::priv::VAO vao;
        vao.bind();
        
        pxl::priv::VBO vbo(vertices, sizeof(vertices));
        // pxl::priv::EBO ebo(indices, sizeof(indices));

        vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

        vao.unbind();
        vbo.unbind();

        shader.activate();

        vao.bind();

        // glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /*
        // Create vertex array and vertex buffer objects
        GLuint VAO, VBO;

        // Generate the VAO and VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Make the VAO the current VAO
        glBindVertexArray(VAO);

        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Give vertices to VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Configure so it knows how to read VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // Use it
        glEnableVertexAttribArray(0);

        // Prevents accidently modifying them
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);
        */
    }
}

#endif






