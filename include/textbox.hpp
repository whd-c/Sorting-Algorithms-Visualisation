#pragma once
#include "raylib.h"
#include "common.hpp"
#include <iostream>

class Textbox
{
public:
    Textbox(Rectangle _rect, uint16_t _MAX_INPUT) : rect(_rect), MAX_INPUT(_MAX_INPUT) {};
    void update();
    bool keyPressed();

    const char *getInput() const { return input; }

private:
    Rectangle rect;
    static constexpr uint8_t MAX_INPUT_CHARS = 4;
    const uint16_t MAX_INPUT = 5000;
    int8_t letterCount = 0;
    uint8_t framesCounter = 0;
    bool mouseOnText = false;
    char input[MAX_INPUT_CHARS + 1] = "\0";
};