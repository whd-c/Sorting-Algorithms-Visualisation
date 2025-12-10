#pragma once

#include "common.hpp"
#include "sort_manager.hpp"
#include <vector>

class Render
{
public:
    Render(SortManager &_sortManager) : sortManager(_sortManager) {}
    void resizeElementsRect(std::vector<Element> &elements);

    static constexpr float MAX_RECTANGLE_WIDTH = 225.0f;
    static constexpr float MAX_RECTANGLE_HEIGHT = 150.0f;

private:
    SortManager &sortManager;
};