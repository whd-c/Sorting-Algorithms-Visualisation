#pragma once
#include <cstdint>
#include "raylib.h"

enum class Sort
{
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
};

struct Element
{
    Rectangle rect;
    int val = 0;
};

constexpr uint16_t WINDOW_WIDTH = 800;
constexpr uint16_t WINDOW_HEIGHT = 450;