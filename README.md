# Pixelet

## Usage

Example belows shows a square bouncing around
```cpp
// Include Pixelet
#include <pixelet/all.h>

// Main
int main()
{
    // Variables
    int x = 0, y = 0, velX = 4, velY = 2;
    
    // Initialize Pixelet
    pxl::init();

    // Create the window
    pxl::Window window(600, 600, "Pixelet Example");

    // Do things while the window is open
    while (window.isOpen())
    {
        // Pxl namespace
        using namespace pxl;

        // Put a dark gray background
        graphics::background(30, 30, 30);

        // Draw the square
        graphics::fill(48, 90, 224);
        graphics::rect(x, y, 15, 15);

        // Move the square
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
```





