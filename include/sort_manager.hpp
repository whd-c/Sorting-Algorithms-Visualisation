#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "common.hpp"
#include "raylib.h"

class SortManager
{
public:
    uint16_t numElements = 5;
    std::vector<Element> elements;

    Sort currentSort;
    std::vector<Element> returnShuffled(const std::vector<Element> &elements);
};