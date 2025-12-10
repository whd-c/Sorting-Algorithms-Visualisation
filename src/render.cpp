#include "render.hpp"

void Render::resizeElementsRect(std::vector<Element> &elements)
{
    // TODO: Fix elements not showing if elements > 8155
    float currentX = WINDOW_WIDTH / 2.0f - (WINDOW_WIDTH / 5.75f);
    for (int i = 0; i < sortManager.numElements; i++)
    {
        const float height = MAX_RECTANGLE_HEIGHT * ((float)(elements[i].val) / sortManager.numElements);
        const float width = MAX_RECTANGLE_HEIGHT / sortManager.numElements * 2;
        const float x = currentX;
        const float y = WINDOW_HEIGHT / 2.0f - height;
        elements[i].rect = {
            x,
            y,
            width,
            height,
        };
        currentX += width;
    }
}