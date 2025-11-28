#pragma once
#include "raylib.h"
#include "common.hpp"
#include <vector>
#include <string>

class Program
{
public:
    Program();
    ~Program();
    void run();

private:
    static constexpr uint8_t MAX_SIZE = 100;
    static constexpr const char *WINDOW_TITLE = "Sorting Algorithms Visualisation";

    static constexpr float MAX_RECTANGLE_WIDTH = 225.0f;
    static constexpr float MAX_RECTANGLE_HEIGHT = 150.0f;
    uint16_t numElements = 5;
    struct Element
    {
        Rectangle rect;
        int val = 0;
    };
    std::vector<Element> elements;

    Sort currentSort;

    void resizeElementsVector(std::vector<Element> &elements);
    std::vector<Element> returnShuffled(const std::vector<Element> &elements);
};