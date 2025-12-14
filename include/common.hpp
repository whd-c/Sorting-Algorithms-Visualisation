#pragma once
#include <cstdint>
#include "raylib.h"

enum class Sort
{
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    PANCAKE_SORT,
    MERGE_SORT,
};

struct Element
{
    Rectangle rect;
    int val = 0;
    bool selected = false;
};

constexpr uint16_t WINDOW_WIDTH = 800;
constexpr uint16_t WINDOW_HEIGHT = 450;

constexpr Color DARKRED = {55, 0, 0, 255};