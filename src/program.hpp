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
    uint16_t elements = 5;
    std::vector<Rectangle> rectangles{};

    Sort currentSort;

    void resizeRectVector(std::vector<Rectangle> &rectangles);
};