#include "window.hpp"

// Window constructor
pxl::Window::Window(int x, int y, unsigned int width, unsigned int height, const char* title)
{
    // Create the window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    // Put error if could not initialize window
    if (!window)
    {
        std::cerr << "pxl error: failed to initialize window";
        return;
    }

    // Set window position
    glfwSetWindowPos(window, x, y);

    // Use the window
    glfwMakeContextCurrent(window);

    // Load OpenGL
    gladLoadGL();

    // Tell area of window to render in
    glViewport(0, 0, width, height);

    // Anti aliasing (FIX!)
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
}

// Get the width
unsigned int pxl::Window::getWidth()
{
    int res;
    glfwGetWindowSize(window, &res, nullptr);
    return res;
}

// Get the height
unsigned int pxl::Window::getHeight()
{
    int res;
    glfwGetWindowSize(window, nullptr, &res);
    return res;
}

// Set the position
void pxl::Window::setPosition(int x, int y)
{
    glfwSetWindowPos(window, x, y);
}

// Set the size
void pxl::Window::setSize(unsigned int width, unsigned int height)
{
    glfwSetWindowSize(window, width, height);
}

// Set size limit
void pxl::Window::setSizeLimit(unsigned int minWidth, unsigned int minHeight, unsigned int maxWidth, unsigned int maxHeight)
{
    glfwSetWindowSizeLimits(window, minWidth, minHeight, maxWidth, maxHeight);
}

// Set the background
void pxl::Window::setBackground(float red, float green, float blue)
{
    glClearColor(red / 255.f, green / 255.f, blue / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

// Indicate whether the window is open
bool pxl::Window::isOpen()
{
    return !glfwWindowShouldClose(window);
}

// Goes in the main loop
bool pxl::Window::whileOpen()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}

// Array of keys currently being pressed
static bool keysPressed[346];

// Listen for key press events
static pxl::keyPressCb callback;
static void setKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    callback(static_cast<pxl::Key>(key));
}

void pxl::Window::onKeyPress(pxl::keyPressCb callback)
{
    ::callback = callback;
    glfwSetKeyCallback(this->window, setKey);
}


