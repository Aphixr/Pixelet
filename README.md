# Pixelet

## Usage

Example:
```cpp
// Include
#include <pixelet/all.h>

// Main function
int main()
{
    // Initialize
    pxl::init();

    // Create the window
    pxl::Window window(600, 600, "Example");

    // Main loop
    while (window.isOpen())
    {
        using namespace pxl;

        // Set background
        graphics::background(30, 30, 30);

        // Draw a triangle
        graphics::fill(30, 90, 248);
        graphics::triangle(-1, -1, 1, -1, 0, 1);

        // Handle other loop actions
        window.doLoopRegActions();
    }

    // End of program
    pxl::exit();
    return 0;
}
```





