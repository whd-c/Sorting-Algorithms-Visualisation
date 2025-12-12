#include "sort_manager.hpp"
#include <iostream>

std::vector<Element> SortManager::returnShuffled(const std::vector<Element> &elements)
{
    std::vector<Element> shuffled{elements};
    std::random_device rd;
    std::mt19937 mt(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), mt);
    return shuffled;
}

void SortManager::update()
{
    switch (currentSort)
    {
    case Sort::BUBBLE_SORT:
        elements = bubbleSort(elements);
        break;
    case Sort::SELECTION_SORT:
        break;
    case Sort::INSERTION_SORT:
        break;
    default:
        break;
    }
}

std::vector<Element> SortManager::bubbleSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    for (size_t i = 0; i < sorted.size() - 1; i++)
    {
        if (sorted[i].val > sorted[i + 1].val)
        {
            sorted[i + 1].selected = true;
            std::swap(sorted[i].val, sorted[i + 1].val);
        }
    }

    return sorted;
}