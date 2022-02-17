// Header guard
#pragma once

// Macros
#define PXL
#define PXL_PIXELET_HPP
#define PXL_VERSION_MAJOR 0
#define PXL_VERSION_MINOR 3
#define PXL_VERSION_REVISION 0

// Include Pixelet files

// Pixelet namespace
namespace pxl
{
    // Initialize Pixelet
    void init();

    // Terminate Pixelet
    void exit();
}

// Include Pixelet files
#include "window.hpp"
#include "graphics.hpp"


