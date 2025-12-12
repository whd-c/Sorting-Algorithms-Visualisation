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

    Sort currentSort = Sort::BUBBLE_SORT;

    std::vector<Element> returnShuffled(const std::vector<Element> &elements);
    void update();

private:
    std::vector<Element> bubbleSort(const std::vector<Element> &elements);
};