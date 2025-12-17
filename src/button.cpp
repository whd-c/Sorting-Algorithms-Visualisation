#include "ui/button.hpp"

void Button::update()
{
    btnPressed = false;

    if (CheckCollisionPointRec(GetMousePosition(), rect))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            btnState = (selected) ? SELECTED_PRESS : PRESSED;
        else
            btnState = (selected) ? SELECTED_HOVER : HOVERED;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnPressed = true;
    }
    else
    {
        btnState = (selected) ? SELECTED : NORMAL;
    }

    static const std::unordered_map<State, Color> cMap = {
        {NORMAL, cNormal},
        {HOVERED, cHover},
        {PRESSED, cPress},
        {SELECTED, cSelected},
        {SELECTED_HOVER, cSelectedHover},
        {SELECTED_PRESS, cSelectedPress},
    };
    Color drawColor = cMap.at(btnState);
    DrawRectangleRec(rect, drawColor);

    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
    DrawTextEx(GetFontDefault(), text, {rect.x + (rect.width - textSize.x) / 2, rect.y + (rect.height - textSize.y) / 2}, fontSize, 1, BLACK);
}