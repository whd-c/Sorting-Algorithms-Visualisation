#pragma once
#include "common.hpp"
#include "sort_manager.hpp"
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

    SortManager sortManager;

    void resizeElementsRect(std::vector<Element> &elements);
};