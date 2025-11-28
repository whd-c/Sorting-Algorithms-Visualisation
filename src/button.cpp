#include "button.hpp"

void Button::update()
{
    btnPressed = false;
    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = 2;
        else
            btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnPressed = true;
    }
    else
    {
        btnState = 0;
    }
    DrawRectangleRec(rect, RAYWHITE);
}