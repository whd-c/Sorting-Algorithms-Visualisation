#include "program.hpp"
#include "ui/textbox.hpp"
#include "ui/button.hpp"
#include <iostream> //DEBUG
#include <chrono>

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
    Textbox inputBox({WINDOW_WIDTH / 2.0f - 120.f, WINDOW_HEIGHT / 1.5f, 225.0f, 50.0f}, MAX_INPUT);
    Button shuffleButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 1.75f, 150.0f, 50.0f}, "SHUFFLE", 25);
    Button bubbleSortButton({50.0f, WINDOW_HEIGHT / 1.85f, 150.0f, 50.0f}, "BUBBLE", 20);
    Button selectionSortButton({50.0f, WINDOW_HEIGHT / 1.45f, 150.0f, 50.0f}, "SELECTION", 20);
    Button insertionSortButton({50.0f, WINDOW_HEIGHT / 1.2f, 150.0f, 50.0f}, "INSERTION", 20);
    Button runSortButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 1.3f, 150.0f, 50.0f}, "RUN SORT", 25);

    auto beg = std::chrono::high_resolution_clock::now();
    auto end = beg;
    while (!WindowShouldClose())
    {

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
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
        DrawText("ELAPSED: ", WINDOW_WIDTH / 1.3f, 30, 20, RAYWHITE);
        snprintf(textBoxText, sizeof(textBoxText), "%lld ms", duration.count());
        DrawText(textBoxText, WINDOW_WIDTH / 1.3f, 60, 20, RAYWHITE);
        shuffleButton.update();
        bubbleSortButton.update();
        runSortButton.update();
        selectionSortButton.update();
        insertionSortButton.update();

        if (shuffleButton.getBtnPressed())
        {
            sortManager.elements = sortManager.returnShuffled(sortManager.elements);
            render.resizeElementsRect(sortManager.elements);
            sorting = false;
        }
        if (bubbleSortButton.getBtnPressed() && sortManager.currentSort != Sort::BUBBLE_SORT)
        {
            sortManager.currentSort = Sort::BUBBLE_SORT;
            sorting = false;
        }
        if (selectionSortButton.getBtnPressed() && sortManager.currentSort != Sort::SELECTION_SORT)
        {
            sortManager.currentSort = Sort::SELECTION_SORT;
            sorting = false;
        }
        if (insertionSortButton.getBtnPressed() && sortManager.currentSort != Sort::INSERTION_SORT)
        {
            sortManager.currentSort = Sort::INSERTION_SORT;
            sorting = false;
        }
        if (runSortButton.getBtnPressed())
        {
            sorting = !sorting;
            if (sorting)
            {
                beg = std::chrono::high_resolution_clock::now();
                end = beg;
            }
        }

        if (sorting)
        {
            if (std::is_sorted(sortManager.elements.begin(), sortManager.elements.end(), [](const Element &a, const Element &b)
                               { return a.val < b.val; }))
            {
                sorting = false;
            }
            sortManager.update();
            runSortButton.setText("STOP SORT");
            render.resizeElementsRect(sortManager.elements);
            end = std::chrono::high_resolution_clock::now();
        }
        else
        {
            runSortButton.setText("RUN SORT");
            sortManager.iterations = 0;
        }

        ClearBackground(Color({36, 36, 36, 255}));
        EndDrawing();
    }
}