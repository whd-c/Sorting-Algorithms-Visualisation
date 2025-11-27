#include "program.hpp"
#include "textbox.hpp"
#include <iostream> //DEBUG

Program::Program()
{
    srand(time(0));
    SetTargetFPS(144);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
}

Program::~Program()
{
    CloseWindow();
}

void Program::resizeRectVector(std::vector<Rectangle> &rectangles)
{
    // TODO: Fix elements not showing if elements > 8155
    if (elements <= 0)
        return;
    rectangles.resize(elements);

    float currentX = WINDOW_WIDTH / 2.0f - (WINDOW_WIDTH / 16);
    for (int i = 0; i < elements; i++)
    {
        const float height = MAX_RECTANGLE_HEIGHT * ((float)(rand() % elements + 1) / elements);
        const float width = MAX_RECTANGLE_HEIGHT / elements;
        const float x = currentX;
        const float y = WINDOW_HEIGHT / 2.0f - height;
        rectangles[i] = {
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
    elements = 5;
    resizeRectVector(rectangles);
    Textbox textBox(WINDOW_WIDTH / 2.0f - 100.f, WINDOW_HEIGHT / 1.5f, 225.0f, 50.0f);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Sorting Algorithms Visualisation", 10, 10, 32, RAYWHITE);
        for (const auto &rect : rectangles)
        {
            DrawRectangleGradientEx(rect, GREEN, DARKGREEN, DARKGREEN, GREEN);
        }
        textBox.update();
        if (textBox.keyPressed() && atoi(textBox.getInput()) < 8155 && elements != atoi(textBox.getInput()))
        {
            elements = atoi(textBox.getInput());
            resizeRectVector(rectangles);
        }
        ClearBackground(Color({36, 36, 36}));
        EndDrawing();
    }
}