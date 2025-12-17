#include "program.hpp"
#include <iostream> //DEBUG

Program::Program()
{
    srand(time(0));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (GetWindowHandle() == nullptr)
    {
        throw std::runtime_error("Failed to create window!");
    }
    SetTargetFPS(144);
    Image icon = LoadImage("icon/icon.png");
    if (icon.data == nullptr)
    {
        throw std::runtime_error("Failed to load icon.png!");
    }
    SetWindowIcon(icon);
    UnloadImage(icon);
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
    sortManager.resizeElementsRect();
    constexpr int MAX_INPUT = 5000;
    constexpr int MIN_INPUT = 5;
    Textbox inputBox({WINDOW_WIDTH / 2.0f - 120.f, WINDOW_HEIGHT / 1.5f, 225.0f, 50.0f}, MAX_INPUT);
    Button shuffleButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 1.75f, 150.0f, 50.0f}, "SHUFFLE", 25);
    Button mergeSortButton({50.0f, WINDOW_HEIGHT / 6.0f, 150.0f, 50.0f}, "MERGE", 20);
    Button pancakeSortButton({50.0f, WINDOW_HEIGHT / 6.0f + 75.0f, 150.0f, 50.0f}, "PANCAKE", 20);
    Button bubbleSortButton({50.0f, WINDOW_HEIGHT / 6.0f + 150.0f, 150.0f, 50.0f}, "BUBBLE", 20);
    Button selectionSortButton({50.0f, WINDOW_HEIGHT / 6.0f + 225.0f, 150.0f, 50.0f}, "SELECTION", 20);
    Button insertionSortButton({50.0f, WINDOW_HEIGHT / 6.0f + 300.0f, 150.0f, 50.0f}, "INSERTION", 20);
    Button runSortButton({WINDOW_WIDTH / 1.35f, WINDOW_HEIGHT / 1.3f, 150.0f, 50.0f}, "RUN SORT", 25);

    auto beg = std::chrono::high_resolution_clock::now();
    selectedSortBtn = bubbleSortButton;
    selectedSortBtn->get().setSelected();

    while (!WindowShouldClose())
    {

        auto duration = accumulatedTime;
        if (timerRunning)
        {
            duration += std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - beg);
        }
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
            resetState();
            sortManager.numElements = (std::atoi(inputBox.getInput()) > MIN_INPUT) ? (std::atoi(inputBox.getInput())) : (MIN_INPUT);
            sortManager.elements.resize(sortManager.numElements);
            for (int i = 0; i < sortManager.numElements; i++)
            {
                sortManager.elements[i].val = i + 1;
            }
            sortManager.resizeElementsRect();
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
        mergeSortButton.update();
        bubbleSortButton.update();
        runSortButton.update();
        selectionSortButton.update();
        insertionSortButton.update();
        pancakeSortButton.update();

        if (shuffleButton.getBtnPressed())
        {
            sortManager.elements = sortManager.returnShuffled(sortManager.elements);
            sortManager.resizeElementsRect();
            resetState();
        }
        onSortButtonPress(mergeSortButton, Sort::MERGE_SORT);
        onSortButtonPress(pancakeSortButton, Sort::PANCAKE_SORT);
        onSortButtonPress(bubbleSortButton, Sort::BUBBLE_SORT);
        onSortButtonPress(selectionSortButton, Sort::SELECTION_SORT);
        onSortButtonPress(insertionSortButton, Sort::INSERTION_SORT);
        if (runSortButton.getBtnPressed())
        {
            sortManager.sorting = !sortManager.sorting;
            if (sortManager.sorting)
            {
                if (sortManager.iterations >= sortManager.numElements - 1 && std::is_sorted(sortManager.elements.begin(), sortManager.elements.end(), [](const Element &a, const Element &b)
                                                                                            { return a.val < b.val; }))
                {
                    sortManager.iterations = 0;
                    accumulatedTime = std::chrono::milliseconds(0);
                }
                beg = std::chrono::high_resolution_clock::now();
                timerRunning = true;
            }
            else
            {
                accumulatedTime += std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - beg);
                timerRunning = false;
            }
        }

        if (sortManager.sorting)
        {
            if (std::is_sorted(sortManager.elements.begin(), sortManager.elements.end(), [](const Element &a, const Element &b)
                               { return a.val < b.val; }))
            {
                accumulatedTime += std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - beg);
                sortManager.sorting = false;

                timerRunning = false;
            }
            sortManager.update();
            runSortButton.setText("STOP SORT");
            sortManager.resizeElementsRect();
        }
        else
        {
            runSortButton.setText("RUN SORT");
        }

        ClearBackground(Color({36, 36, 36, 255}));
        EndDrawing();
    }
}

void Program::onSortButtonPress(Button &button, Sort sortType)
{
    if (button.getBtnPressed() && sortManager.currentSort != sortType)
    {
        if (selectedSortBtn)
        {
            selectedSortBtn->get().setSelected(false);
        }
        sortManager.currentSort = sortType;
        button.setSelected();
        selectedSortBtn = button;
        resetState();
    }
}

void Program::resetState()
{
    sortManager.sorting = false;
    sortManager.iterations = 0;
    timerRunning = false;
    accumulatedTime = std::chrono::milliseconds(0);
}