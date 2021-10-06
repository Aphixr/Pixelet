# Pixelet

## Usage

Example belows shows a blue square bouncing around.
```cpp
// Include Pixelet
#include <pixelet/all.hpp>

// Main
int main()
{
    // Variables
    double x = 0, y = 0, velX = 0.6, velY = 0.4;
    
    // Initialize Pixelet
    pxl::init();

    // Create the window
    pxl::window::Window window(600, 600, "Pixelet Test");

    // Square
    pxl::graphics::Rect square(x, y, 10, 10);
    square.fill(120, 180, 255);

    // Do things while the window is open
    while (window.isOpen())
    {
        // Pxl namespace
        using namespace pxl;

        // Put a dark gray background
        graphics::background(30, 30, 30);

        // Draw the square
        square.draw();

        // Move the square
        square.position(x, y);
        x += velX, y += velY;

        // Change direction of square when it hits edge of window
        if (x <= 0 || x >= window.width - 15) velX = -velX;
        if (y <= 0 || y >= window.height - 15) velY = -velY;

        // Do loop actions
        window.doRegLoopActions();
    }

    // Exit program
    pxl::exit();
    return 0;
}
```





