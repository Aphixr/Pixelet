// Header guard
#pragma once

// Includes
#include <iostream>

// Include OpenGL
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Pixelet namespace
namespace pxl
{
    // List of keys
    enum class Key
    {
        leftShift = 340, leftCtrl, leftAlt, rightShift = 344, rightCtrl, rightAlt,

        capsLock = 280, escape = 256, enter, tab, backspace, insert, /* delete <- already a keyword */

        right = 262, left, down, up, pageUp, pageDown, home, end,

        a = 65, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,

        one = 49, two, three, four, five, six, seven, eight, nine, zero,

        space = 32, comma = 44, hyphen, period, slash,
        semicolon = 59, apostrophe = 39,
        leftBracket = 91, backslash, rightBracket, equal = 61,

        f1 = 290, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,

        none = -1
    };
    
    // List of mouse events
    enum class Mouse
    {
        left, right, middle
    };

    // Type definitions for callback functions
    typedef void (*keyPressCb)(pxl::Key);
    // typedef void (*mousePressCb)(pxl::Mouse);
}


