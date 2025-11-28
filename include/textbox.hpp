#pragma once
#include "raylib.h"
#include "common.hpp"

class Textbox
{
public:
    Textbox(Rectangle _rect) : rect(_rect) {};
    void update();
    bool keyPressed();

    const char *getInput() const { return input; }

private:
    Rectangle rect;
    static constexpr uint8_t MAX_INPUT = 4;
    int8_t letterCount = 0;
    uint8_t framesCounter = 0;
    bool mouseOnText = false;
    char input[MAX_INPUT + 1] = "\0";
};