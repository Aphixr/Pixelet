# Pixelet

## Usage

Example belows shows a blue square in the center
```cpp
// Include Pixelet
#include <pixelet/pixelet.hpp>

// Main
int main()
{
    // Initialize Pixelet
    pxl::init();

    // Create the window
    pxl::Window window(60, 90, 600, 600, "Pixelet Example");

    // Square
    pxl::Rect square(-0.5f, 0.5f, 0.5f, -0.5f);
    square.fill(120, 180, 255);

    // Do things while the window is open
    while (window.whileOpen())
    {
        // Put a dark gray background
        window.setBackground(30, 30, 30);

        // Draw the square
        square.draw();
    }

    // End of program
    pxl::exit();
    return 0;
}
```





