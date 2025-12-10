#pragma once
#include "common.hpp"
#include "sort_manager.hpp"
#include "render.hpp"
#include <vector>
#include <string>

class Program
{
public:
    Program();
    ~Program();
    void run();

private:
    static constexpr const char *WINDOW_TITLE = "Sorting Algorithms Visualisation";

    SortManager sortManager;
    Render render{sortManager};
};