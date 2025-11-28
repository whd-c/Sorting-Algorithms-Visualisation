#pragma once
#include <raylib.h>
#include "common.hpp"

class Button
{
public:
    Button(Rectangle _rect) : rect(_rect) {};
    bool btnPressed = false;
    void update();

private:
    uint16_t width;
    Rectangle rect;
    uint8_t btnState = 0; // 0 - normal, 1 - hovered, 2 - pressed
};