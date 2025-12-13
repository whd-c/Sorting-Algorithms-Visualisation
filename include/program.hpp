#pragma once
#include "common.hpp"
#include "sort_manager.hpp"
#include "render.hpp"
#include "ui/textbox.hpp"
#include "ui/button.hpp"
#include <vector>
#include <string>
#include <chrono>

class Program
{
public:
    Program();
    ~Program();
    void run();

private:
    static constexpr const char *WINDOW_TITLE = "Sorting Algorithms Visualisation";

    SortManager sortManager;
    bool sorting = false;
    Render render{sortManager};

    std::chrono::milliseconds accumulatedTime{0};
    bool timerRunning = false;

    void onSortButtonPress(const Button &button, Sort sortType);
    void resetState();
};