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
    uint16_t iterations = 0;
    std::vector<Element> elements;

    Sort currentSort = Sort::BUBBLE_SORT;

    std::vector<Element> returnShuffled(const std::vector<Element> &elements);
    void update();

private:
    std::vector<Element> bubbleSort(const std::vector<Element> &elements);
    std::vector<Element> selectionSort(const std::vector<Element> &elements);
    std::vector<Element> insertionSort(const std::vector<Element> &elements);
    std::vector<Element> pancakeSort(const std::vector<Element> &elements);
};