#include "program.hpp"
#include <iostream> //DEBUG

Program::Program()
{
    srand(time(0));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
}

Program::~Program()
{
    CloseWindow();
}

void Program::resizeRectVector(std::vector<Rectangle> &rectangles)
{
    // TODO: Fix elements not showing if elements > 8161
    if (elements <= 0)
        return;
    rectangles.resize(elements);

    float currentX = WINDOW_WIDTH / 2.0f - (WINDOW_WIDTH / 16);
    for (int i = 1; i <= elements; i++)
    {
        const float height = MAX_RECTANGLE_HEIGHT * ((float)(rand() % elements + 1) / elements);
        const float width = MAX_RECTANGLE_HEIGHT / elements;
        const float x = currentX;
        const float y = WINDOW_HEIGHT / 2.0f - height;
        rectangles[i - 1] = {
            x,
            y,
            width,
            height,
        };
        currentX += width;
    }
}

void Program::run()
{
    elements = 1500;
    resizeRectVector(rectangles);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Sorting Algorithms Visualisation", 10, 10, 32, RAYWHITE);
        for (const auto &rect : rectangles)
        {
            DrawRectangleGradientEx(rect, GREEN, DARKGREEN, DARKGREEN, GREEN);
        }
        ClearBackground(Color({36, 36, 36}));
        EndDrawing();
    }
}