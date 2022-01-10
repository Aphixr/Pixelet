#include "graphics.hpp"



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
    std::cerr << "*ERR: could not open file '" << fileName << "'\n";
    return "";
}



// Triangle constructor with initial positions
pxl::Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    setPosition(x1, y1, x2, y2, x3, y3);

    // vvv remove?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

// Triangle constructor without initializing anything
pxl::Triangle::Triangle()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

// Destructor
pxl::Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.destroy();
}

// Set position of vertices of triangle
void pxl::Triangle::setPosition(float x1, float y1, float x2, float y2, float x3, float y3)
{
    vertices[0] = x1, vertices[1] = y1;
    vertices[3] = x2, vertices[4] = y2;
    vertices[6] = x3, vertices[7] = y3;
    vertices[2] = vertices[5] = vertices[8] = 0.f;

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    if (!setPosYet)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    setPosYet = true;
}

// Set fill color
void pxl::Triangle::setFill(float red, float green, float blue)
{
    fillColor[0] = red / 255.f;
    fillColor[1] = green / 255.f;
    fillColor[2] = blue / 255.f;
}

// Set scale
void pxl::Triangle::setScale(float x, float y)
{
    scale[0] = x;
    scale[1] = y;
}

// Draw triangle
void pxl::Triangle::draw()
{
    if (!setPosYet) return;
    
    shader.activate();
    
    glBindVertexArray(VAO);

    glUniform4fv(colorLoc, 1, fillColor);
    glUniform2fv(scaleLoc, 1, scale);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}



// Quadrilateral constructor with initial positions
pxl::Quad::Quad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertices items
    for (int i = 2; i < 12; i += 3) vertices[i] = 0.f;
    setPosition(x1, y1, x2, y2, x3, y3, x4, y4);
}

// Quadrilateral constructor without initializing anything
pxl::Quad::Quad()
{
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    for (int i = 2; i < 12; i += 3) vertices[i] = 0.f;
}

// Set position
void pxl::Quad::setPosition(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    vertices[0] = x1, vertices[ 1] = y1;
    vertices[3] = x2, vertices[ 4] = y2;
    vertices[9] = x3, vertices[10] = y3;
    vertices[6] = x4, vertices[ 7] = y4;

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    if (!setPosYet)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    setPosYet = true;
}

// Set fill color
void pxl::Quad::setFill(float red, float green, float blue)
{
    fillColor[0] = red / 255.f;
    fillColor[1] = green / 255.f;
    fillColor[2] = blue / 255.f;
}

// Set scale of rectangle
void pxl::Quad::setScale(float x, float y)
{
    scale[0] = x;
    scale[1] = y;
}

// Draw the quadrilateral
void pxl::Quad::draw()
{
    if (!setPosYet) return;    

    shader.activate();

    glBindVertexArray(VAO);

    glUniform4fv(colorLoc, 1, fillColor);
    glUniform2fv(scaleLoc, 1, scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}



// Rectangle constructor with initializing
pxl::Rect::Rect(float x, float y, float width, float height)
{
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    setPosition(x, y);
    setSize(width, height);

    for (int i = 2; i < 12; i += 3) vertices[i] = 0.f;
}

// Rectangle constructor without initializing anything
pxl::Rect::Rect()
{
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    for (int i = 2; i < 12; i += 3) vertices[i] = 0.f;
}

// Rectangle destructor
pxl::Rect::~Rect()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.destroy();
}

// Set the position of the rectangle
void pxl::Rect::setPosition(float x, float y)
{
    vertices[0] = vertices[6] = x;
    vertices[1] = vertices[4] = y;

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    if (!setPosYet)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    setPosYet = true;
}

// Set the size of the rectangle
void pxl::Rect::setSize(float width, float height)
{
    vertices[3] = vertices[ 9] = vertices[0] + width;
    vertices[7] = vertices[10] = vertices[1] + height;

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    if (!setSizeYet)
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    setSizeYet = true;
}

// Set fill color of the rectangle
void pxl::Rect::setFill(float red, float green, float blue)
{
    fillColor[0] = red / 255.f;
    fillColor[1] = green / 255.f;
    fillColor[2] = blue / 255.f;
}

// Set scale of the rectangle
void pxl::Rect::setScale(float x, float y)
{
    scale[0] = x;
    scale[1] = y;
}

// Draw the rectangle
void pxl::Rect::draw()
{
    if (!setPosYet || !setSizeYet) return;    

    shader.activate();

    glBindVertexArray(VAO);

    glUniform4fv(colorLoc, 1, fillColor);
    glUniform2fv(scaleLoc, 1, scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


