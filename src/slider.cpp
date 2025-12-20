#include "ui/slider.hpp"

Slider::Slider(Rectangle _main) : main(_main)
{
    slider.height = static_cast<int>(main.height + 20);
    slider.width = static_cast<int>(main.width / 10);
    slider.x = static_cast<int>(main.x + (main.width / 2) - 5);
    slider.y = static_cast<int>(main.y - 10);
}

void Slider::update()
{
    static uint16_t begBorder = main.x;
    static uint16_t endBorder = main.x + main.width - 10;
    static bool holding = false;
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
    {
        holding = false;
    }
    if (CheckCollisionPointRec(GetMousePosition(), slider))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            holding = true;
        }
    }
    int currentX = GetMouseX() - slider.width / 2;
    if (currentX <= begBorder)
    {
        currentX = begBorder;
    }
    else if (currentX >= endBorder)
    {
        currentX = endBorder;
    }
    if (holding && currentX >= begBorder && currentX <= endBorder)
        slider.x = currentX;

    DrawRectangleRec(main, RAYWHITE);
    DrawRectangleRec(slider, BLACK);

    float percentage = static_cast<float>(slider.x - begBorder) / (endBorder - begBorder);

    //* Interpolation formula: min + percentage(max - min)
    currValue = minValue + percentage * (maxValue - minValue);
}