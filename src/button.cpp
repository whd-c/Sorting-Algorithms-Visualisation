#include "ui/button.hpp"

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
    Color drawColor = (btnState == 2 ? cPress : btnState == 1 ? cHover
                                                              : cNormal);
    DrawRectangleRec(rect, drawColor);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    DrawTextEx(GetFontDefault(), text, {rect.x + (rect.width - textSize.x) / 2, rect.y + (rect.height - textSize.y) / 2}, fontSize, 1, BLACK);
}