// Header guard
#pragma once

// Includes
#include <iostream>
#include <string>
#include <optional>
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
    // NOTICE: Does not work; need to fix
    std::string readFile(const char* fileName)
    {
        std::string line, conts;
        std::ifstream file(fileName);
        std::cout << "1.";
        // if (file.is_open())
        {
            std::cout << "2.";
            while (std::getline(file, line))
            {
                std::cout << "3.";
                conts += line;
            }
            file.close();
            return conts;
        }
        // else
        {
            pxl::priv::Error("unable to open file", true);
            return "";
        }
        /*
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
        */
    }

    // Convert our form of coords to OpenGL's
    std::optional<float> convertCoords(char type, float coord)
    {
        // Check the type
        if (type == 'x')
        {
            return coord / pxl::priv::windowWidth * 2 - 1;
        }
        else if (type == 'y')
        {
            return -(coord / pxl::priv::windowHeight * 2 - 1);
        }
        return std::nullopt;
    }

    // Shader program class
    // NOTICE: Commented out printing out error lines
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
                        pxl::priv::Error("shader compilation " + std::string(type), true);
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
                        pxl::priv::Error("shader linking " + std::string(type), true);
                    }
                }
            }

        // Public
        public:
            GLuint id;

            // Default constructor
            Shader() = default;

            // Constructor
            Shader(const char* vertexSource, const char* fragmentSource)
            {
                this->giveShaderSources(vertexSource, fragmentSource);
                /*
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
                this->compileErrors(this->id, "PROGRAM");

                // Delete shaders
                glDeleteShader(vertexShader);
                glDeleteShader(fragmentShader);
                */
            }

            // Give shader sources
            void giveShaderSources(const char* vertexSource, const char* fragmentSource)
            {
                // Create vertex shader
                GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexShader, 1, &vertexSource, NULL);
                glCompileShader(vertexShader);
                this->compileErrors(vertexShader, "vertex");

                // Create fragment shader
                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
                glCompileShader(fragmentShader);
                this->compileErrors(fragmentShader, "fragment");

                // Create shader program
                this->id = glCreateProgram();

                // Attach shaders to shader program
                glAttachShader(this->id, vertexShader);
                glAttachShader(this->id, fragmentShader);

                // Wrap up the shader program
                glLinkProgram(this->id);
                this->compileErrors(this->id, "PROGRAM");

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

            // Constructor without setting
            VBO() = default;

            // Constructor with setting vertices and size
            VBO(GLfloat* vertices, GLsizeiptr size)
            {
                this->set(vertices, size);
            }

            // Set
            void set(GLfloat* vertices, GLsizeiptr size)
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

            // Default constructor
            EBO() = default;

            // Constructor with init'n indices and size
            EBO(GLuint* indices, GLsizeiptr size)
            {
                this->set(indices, size);
            }

            // Set
            void set(GLuint* indices, GLsizeiptr size)
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

    // Frame rate
    unsigned int frameRate = 60;

    // Draw the background
    void background(float red, float green, float blue, float alpha=1.f)
    {
        glClearColor(red/255, green/255, blue/255, alpha/255);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Set the fill color
    void fill(float red, float green, float blue, float alpha=255.f)
    {
        curFillColor[0] = red;
        curFillColor[1] = green;
        curFillColor[2] = blue;
        curFillColor[3] = alpha;
    }

    // Set the outline color
    void stroke(float red, float green, float blue, float alpha=255.f)
    {
        curStrokeColor[0] = red;
        curStrokeColor[1] = green;
        curStrokeColor[2] = blue;
        curStrokeColor[3] = alpha;
    }

    // Rectangle
    class Rect
    {
        // Private
        private:
            // Vertex shader code
            // /*
            const char* vertexShaderSource =
                "#version 330 core                                      \n"
                "layout (location = 0) in vec3 aPos;                    \n"
                "void main()                                            \n"
                "{                                                      \n"
                "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.f);   \n"
                "}                                                      \0";
            // const char* vertexShaderSource =
                // pxl::priv::readFile("vert-shdrs/default.glsl").c_str();
            
            // Fragment shader code
            // /*
            const char* fragmentShaderSource =
                "#version 330 core                           \n"
                "out vec4 FragColor;                         \n"
                "uniform vec4 color;                         \n"
                "void main()                                 \n"
                "{                                           \n"
                "    FragColor = color;                      \n"
                "}                                           \0";
            // const char* fragmentShaderSource = fragmentShaderSourceAsStdStr.c_str();
            // const char* fragmentShaderSource =
                // pxl::priv::readFile("frag-shdrs/default.glsl").c_str();

            // Coordinates of the rectangle
            GLfloat vertices[12];

            // Indices
            GLuint indices[6] = {0, 1, 2, 3, 2, 1};

            // Define other things
            pxl::priv::Shader shader;
            pxl::priv::VAO vao;
            pxl::priv::VBO vbo;
            pxl::priv::EBO ebo;

            // Set items of vertices
            void setVerticesItems(float x, float y, float width, float height)
            {
                // Set variables
                this->x = x;
                this->y = y;
                this->width = width;
                this->height = height;

                // Set the elements of the vertices
                for (int i = 0; i < 12; i++)
                {
                    switch (i)
                    {
                        case 0: case 6:
                            vertices[i] = *pxl::priv::convertCoords('x', x);
                            break;
                        case 1: case 4:
                            vertices[i] = *pxl::priv::convertCoords('y', y);
                            break;
                        case 3: case 9:
                            vertices[i] = *pxl::priv::convertCoords('x', x + width);
                            break;
                        case 7: case 10:
                            vertices[i] = *pxl::priv::convertCoords('y', y + height);
                            break;
                        default:
                            vertices[i] = 0.f;
                            break;
                    }
                }

                // Set position and size
                setPosYet = true;
                setSizeYet = true;
            }

            // Update shape
            void update()
            {
                // Bind VAO
                vao.bind();
                
                // VBO and EBO
                vbo.set(vertices, sizeof(vertices));
                ebo.set(indices, sizeof(indices));

                // Link VBO to VAO
                vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 0, (void*)0);

                // Unbind VAO, VBO, and EBO
                vao.unbind(), vbo.unbind(), ebo.unbind();
            }

            // Position and size
            float x, y, width, height;
            bool setPosYet = false, setSizeYet = false;

            // Color
            float fillColor[4] = {1.f, 1.f, 1.f, 1.f};
            float strokeColor[4] = {0.f, 0.f, 0.f, 0.f};
            GLfloat glFillColor[4] = {1.f, 1.f, 1.f, 1.f};
            GLfloat glStrokeColor[4] = {0.f, 0.f, 0.f, 0.f};

        // Public
        public:
            // Constructor with no arguments
            Rect()
            {
                // Give shader sources
                shader.giveShaderSources(vertexShaderSource, fragmentShaderSource);

                // Put zero for some items in vertices array because this is 2D
                for (int i = 2; i < 12; i += 3)
                {
                    vertices[i] = 0.f;
                }
            }

            // Constructor with initialized position and size
            Rect(float x, float y, float width, float height)
            {
                // Give shader sources
                shader.giveShaderSources(vertexShaderSource, fragmentShaderSource);

                // Set the elements of the vertices
                setVerticesItems(x, y, width, height);

                // Update
                update();
            }

            // Set the position
            void position(float xPos, float yPos)
            {
                // Set attributes
                x = xPos, y = yPos;

                // Set the items of vertices array
                vertices[0] = *pxl::priv::convertCoords('x', x);
                vertices[6] = *pxl::priv::convertCoords('x', x);
                vertices[1] = *pxl::priv::convertCoords('y', y);
                vertices[4] = *pxl::priv::convertCoords('y', y);
                
                // If set size yet, change those values too
                if (this->setSizeYet)
                {
                    vertices[3] = *pxl::priv::convertCoords('x', x + width);
                    vertices[9] = *pxl::priv::convertCoords('x', x + width);
                    vertices[7] = *pxl::priv::convertCoords('y', y + height);
                    vertices[10] = *pxl::priv::convertCoords('y', y + height);
                }

                // Update
                update();

                // Set position
                setPosYet = true;
            }

            // Set the size
            void size(float width, float height)
            {
                // Set attributes
                this->width = width, this->height = height;

                // Set the items of vertices array
                vertices[3] = *pxl::priv::convertCoords('x', x + width);
                vertices[9] = *pxl::priv::convertCoords('x', x + width);
                vertices[7] = *pxl::priv::convertCoords('y', y + height);
                vertices[10] = *pxl::priv::convertCoords('y', y + height);

                // Update
                update();

                // Set size
                setSizeYet = true;
            }

            // Draw the rectangle
            void draw()
            {
                // Check if set position and size yet
                if (!setPosYet && !setSizeYet)
                {
                    pxl::priv::Error("cannot draw rectangle without setting position and size first");
                    return;
                }

                // Shader
                shader.activate();

                // Bind the VAO
                vao.bind();

                // Color
                GLint colorLoc = glGetUniformLocation(shader.id, "color");
                glUniform4fv(colorLoc, 1, glFillColor);

                // Draw the rectangle
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }

            // Set the fill color
            void fill(int red, int green, int blue, int alpha=255)
            {
                // Set fill color variable
                fillColor[0] = red / 255;
                fillColor[1] = green / 255;
                fillColor[2] = blue / 255;
                fillColor[3] = alpha / 255;

                // Do the same for gl colors
                for (int i = 0; i < 4; ++i)
                    glFillColor[i] = fillColor[i];
            }
    };

    // Draw a rectangle
    void rect(float x, float y, float width, float height)
    {
        // Vertex shader code
        const char* vertexShaderSource =
            pxl::priv::readFile("vert-shdrs/default.glsl").c_str();
        
        // Fragment shader code
        const std::string fragmentShaderSourceAsStdStr =
            "#version 330 core                                                     \n"
            "out vec4 FragColor;                                                   \n"
            "void main()                                                           \n"
            "{                                                                     \n"
            "    FragColor = vec4(" + std::to_string(curFillColor[0]/255) + "f,    \n"
            "                     " + std::to_string(curFillColor[1]/255) + "f,    \n"
            "                     " + std::to_string(curFillColor[2]/255) + "f,    \n"
            "                     " + std::to_string(curFillColor[3]/255) + "f);   \n"
            "}                                                                     \0";
        const char* fragmentShaderSource = fragmentShaderSourceAsStdStr.c_str();

        // Shader
        pxl::priv::Shader shader(vertexShaderSource, fragmentShaderSource);

        // Coordinates of the rectangle
        GLfloat vertices[12] =
        {
            *pxl::priv::convertCoords('x', x),
            *pxl::priv::convertCoords('y', y),
            0.f,
            *pxl::priv::convertCoords('x', x + width),
            *pxl::priv::convertCoords('y', y),
            0.f,
            *pxl::priv::convertCoords('x', x),
            *pxl::priv::convertCoords('y', y + height),
            0.f,
            *pxl::priv::convertCoords('x', x + width),
            *pxl::priv::convertCoords('y', y + height),
            0.f
        };

        // Indices
        GLuint indices[6] =
        {
            0, 1, 2,
            3, 2, 1
        };
        
        // VAO
        pxl::priv::VAO vao;
        vao.bind();
        
        // VBO and EBO
        pxl::priv::VBO vbo(vertices, sizeof(vertices));
        // vbo.set(vertices, sizeof(vertices));
        pxl::priv::EBO ebo(indices, sizeof(indices));
        // ebo.set(indices, sizeof(indices));

        // Link VBO to VAO
        vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 0, (void*)0);

        // Unbind VAO, VBO, and EBO
        vao.unbind(), vbo.unbind(), ebo.unbind();

        // Shader
        shader.activate();

        // Bind the VAO
        vao.bind();

        // Draw the square
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    // Draw a triangle
    void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        // Vertex shader code
        const char* vertexShaderSource =
            pxl::priv::readFile("vert-shdrs/default.glsl").c_str();
        
        // Fragment shader code
        const std::string fragmentShaderSourceAsStdStr =
            "#version 330 core                                                     \n"
            "out vec4 FragColor;                                                   \n"
            "void main()                                                           \n"
            "{                                                                     \n"
            "    FragColor = vec4(" + std::to_string(curFillColor[0]/255) + "f,    \n"
            "                     " + std::to_string(curFillColor[1]/255) + "f,    \n"
            "                     " + std::to_string(curFillColor[2]/255) + "f,    \n"
            "                     " + std::to_string(curFillColor[3]/255) + "f);   \n"
            "}                                                                     \0";
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

        // VAO
        pxl::priv::VAO vao;
        vao.bind();
        
        // VBO
        pxl::priv::VBO vbo;
        vbo.set(vertices, sizeof(vertices));

        // Link VBO to VAO
        vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
        
        // Unbind VAO and VBO
        vao.unbind(), vbo.unbind();

        // Shader
        shader.activate();

        // Bind vao
        vao.bind();

        // Draw the triangle
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






