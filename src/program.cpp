#include "program.hpp"
#include "textbox.hpp"
#include <algorithm>
#include <random>
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

void Program::resizeElementsVector(std::vector<Element> &elements)
{
    // TODO: Fix elements not showing if elements > 8155
    if (numElements <= 0)
        return;
    elements.resize(numElements);
    for (int i = 0; i < numElements; i++)
    {
        elements[i].val = i + 1;
    }
    elements = returnShuffled(elements);

    float currentX = WINDOW_WIDTH / 2.0f - (WINDOW_WIDTH / 16);
    for (int i = 0; i < numElements; i++)
    {
        const float height = MAX_RECTANGLE_HEIGHT * ((float)(elements[i].val) / numElements);
        const float width = MAX_RECTANGLE_HEIGHT / numElements;
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

std::vector<Program::Element> Program::returnShuffled(const std::vector<Element> &elements)
{
    std::vector<Element> shuffled{elements};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), mt);
    return shuffled;
}

void Program::run()
{
    numElements = 5;
    resizeElementsVector(elements);
    Textbox textBox(WINDOW_WIDTH / 2.0f - 100.f, WINDOW_HEIGHT / 1.5f, 225.0f, 50.0f);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Sorting Algorithms Visualisation", 10, 10, 32, RAYWHITE);
        for (const auto &element : elements)
        {
            DrawRectangleGradientEx(element.rect, GREEN, DARKGREEN, DARKGREEN, GREEN);
        }
        textBox.update();
        if (textBox.keyPressed() && atoi(textBox.getInput()) < 8155 && numElements != atoi(textBox.getInput()))
        {
            numElements = atoi(textBox.getInput());
            resizeElementsVector(elements);
        }
        ClearBackground(Color({36, 36, 36}));
        EndDrawing();
    }
}