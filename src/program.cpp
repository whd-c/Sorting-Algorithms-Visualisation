#include "program.hpp"
#include "ui/textbox.hpp"
#include "ui/button.hpp"
#include <iostream> //DEBUG

Program::Program()
{
    srand(time(0));
    SetTargetFPS(144);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    sortManager.elements.resize(sortManager.numElements);
}

Program::~Program()
{
    CloseWindow();
}

void Program::run()
{
    for (int i = 0; i < sortManager.numElements; i++)
    {
        sortManager.elements[i].val = i + 1;
    }
    render.resizeElementsRect(sortManager.elements);
    constexpr int MAX_INPUT = 5000;
    constexpr int MIN_INPUT = 5;
    Textbox inputBox({WINDOW_WIDTH / 2.0f - 100.f, WINDOW_HEIGHT / 1.5f, 225.0f, 50.0f}, MAX_INPUT);
    Button shuffleButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 2.0f, 150.0f, 50.0f}, "SHUFFLE", 25);
    Button bubbleSortButton({50.0f, WINDOW_HEIGHT / 1.5f, 150.0f, 50.0f}, "BUBBLE SORT", 20);
    Button runSortButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 1.5f, 150.0f, 50.0f}, "RUN SORT", 25);
    Button stopSortButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 1.2f, 150.0f, 50.0f}, "STOP SORT", 25);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawText("Sorting Algorithms Visualisation", 10, 10, 32, RAYWHITE);
        for (auto &element : sortManager.elements)
        {
            if (element.selected)
            {
                DrawRectangleGradientEx(element.rect, RED, DARKRED, DARKRED, RED);
                element.selected = false;
            }

            else
                DrawRectangleGradientEx(element.rect, WHITE, GRAY, GRAY, WHITE);
        }

        inputBox.update();
        if (inputBox.keyPressed() && sortManager.numElements != std::atoi(inputBox.getInput()))
        {
            sortManager.numElements = (std::atoi(inputBox.getInput()) > MIN_INPUT) ? (std::atoi(inputBox.getInput())) : (MIN_INPUT);
            sortManager.elements.resize(sortManager.numElements);
            for (int i = 0; i < sortManager.numElements; i++)
            {
                sortManager.elements[i].val = i + 1;
            }
            render.resizeElementsRect(sortManager.elements);
        }
        char textBoxText[10];
        snprintf(textBoxText, sizeof(textBoxText), "MAX: %d", MAX_INPUT);
        DrawText(textBoxText, WINDOW_WIDTH / 2 - 90.0f, WINDOW_HEIGHT / 1.25f, 30, RAYWHITE);
        snprintf(textBoxText, sizeof(textBoxText), "MIN: %d", MIN_INPUT);
        DrawText(textBoxText, WINDOW_WIDTH / 2 - 90.0f, WINDOW_HEIGHT / 1.15f, 30, RAYWHITE);
        shuffleButton.update();
        bubbleSortButton.update();
        runSortButton.update();
        stopSortButton.update();

        if (shuffleButton.getBtnPressed())
        {
            sortManager.elements = sortManager.returnShuffled(sortManager.elements);
            render.resizeElementsRect(sortManager.elements);
            sorting = false;
        }
        if (bubbleSortButton.getBtnPressed())
        {
            sortManager.currentSort = Sort::BUBBLE_SORT;
        }
        if (runSortButton.getBtnPressed())
        {
            sorting = true;
        }
        if (stopSortButton.getBtnPressed())
        {
            sorting = false;
        }

        if (sorting)
        {
            if (std::is_sorted(sortManager.elements.begin(), sortManager.elements.end(), [](const Element &a, const Element &b)
                               { return a.val < b.val; }))
            {
                sorting = false;
            }
            sortManager.update();
            render.resizeElementsRect(sortManager.elements);
        }

        ClearBackground(Color({36, 36, 36, 255}));
        EndDrawing();
    }
}