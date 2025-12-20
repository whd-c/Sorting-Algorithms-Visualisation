#pragma once
#include <raylib.h>
#include "common.hpp"

class Slider
{
public:
    Slider(Rectangle _main);
    void update();

    float getValue() const { return currValue; }

private:
    Rectangle main;
    Rectangle slider;

    float currValue;
    float minValue = 0.01f;
    float maxValue = 1.99f;
};