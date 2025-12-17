#pragma once
#include "common.hpp"
#include "sort_manager.hpp"
#include "render.hpp"
#include "ui/textbox.hpp"
#include "ui/button.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <optional>
#include <functional>

class Program
{
public:
    Program();
    ~Program();
    void run();

private:
    static constexpr const char *WINDOW_TITLE = "Sorting Algorithms Visualisation";

    SortManager sortManager;
    // Render render; DEPRECATED

    std::chrono::milliseconds accumulatedTime{0};
    bool timerRunning = false;
    std::optional<std::reference_wrapper<Button>> selectedSortBtn;

    void onSortButtonPress(Button &button, Sort sortType);
    void resetState();
};