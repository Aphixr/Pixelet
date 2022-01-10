#include "shader.hpp"

Shader::Shader(const char* vertexSource, const char* fragmentSource)
{
    setShaderSources(vertexSource, fragmentSource);
}

// Give shader sources
void Shader::setShaderSources(const char* vertexSource, const char* fragmentSource)
{
    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    id = glCreateProgram();

    // Attach shaders to shader program
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);

    // Wrap up the shader program
    glLinkProgram(id);

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Activate
void Shader::activate()
{
    glUseProgram(id);
}

// Delete
void Shader::destroy()
{
    glDeleteProgram(id);
}

// Get ID
GLuint Shader::getID()
{
    return id;
}


