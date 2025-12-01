#include "textbox.hpp"
#include <iostream>

bool Textbox::keyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if (((key >= 48) && (key <= 57)) || IsKeyPressed(KEY_BACKSPACE))
        keyPressed = true;

    return keyPressed;
}

void Textbox::update()
{
    // i shamelessly copied this from raylib examples lmao 😭
    if (CheckCollisionPointRec(GetMousePosition(), rect))
        mouseOnText = true;
    else
        mouseOnText = false;

    if (mouseOnText)
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();
        while (key > 0)
        {

            if ((key >= 48) && (key <= 57) && (letterCount < MAX_INPUT_CHARS))
            {
                input[letterCount] = (char)key;
                input[letterCount + 1] = '\0';
                letterCount++;
            }
            if (std::atoi(input) > MAX_INPUT)
            {
                snprintf(input, sizeof(input), "%d", MAX_INPUT);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            input[letterCount] = '\0';
        }
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText)
        framesCounter++;
    else
        framesCounter = 0;
    DrawRectangleRec(rect, LIGHTGRAY);
    if (mouseOnText)
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, DARKBLUE);
    else
        DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, DARKGRAY);

    DrawText(input, (int)rect.x + 5, (int)rect.y + 8, 40, BLUE);
    if (mouseOnText)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            if (((framesCounter / 20) % 2) == 0)
                DrawText("_", (int)rect.x + 8 + MeasureText(input, 40), (int)rect.y + 12, 40, BLUE);
        }
    }
}