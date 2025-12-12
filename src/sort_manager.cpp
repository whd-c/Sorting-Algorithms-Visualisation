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
        elements = selectionSort(elements);
        break;
    case Sort::INSERTION_SORT:
        elements = insertionSort(elements);
        break;
    default:
        break;
    }
}

std::vector<Element> SortManager::bubbleSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    for (int i = 0; i < numElements - 1 - iterations; i++)
    {
        if (sorted[i].val > sorted[i + 1].val)
        {
            sorted[i].selected = true;
            std::swap(sorted[i].val, sorted[i + 1].val);
        }
    }
    iterations++;
    return sorted;
}

std::vector<Element> SortManager::selectionSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    int min_index = iterations;
    for (int i = min_index + 1; i < numElements; i++)
    {
        if (sorted[i].val < sorted[min_index].val)
        {
            min_index = i;
        }
    }

    std::swap(sorted[iterations].val, sorted[min_index].val);
    sorted[iterations].selected = true;
    sorted[min_index].selected = true;
    iterations++;
    return sorted;
}

std::vector<Element> SortManager::insertionSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    if (iterations >= numElements - 1)
        return sorted;
    Element key = sorted[iterations + 1];
    int i = iterations;
    while (i >= 0 && sorted[i].val > key.val)
    {
        sorted[i + 1].val = sorted[i].val;
        i--;
    }
    sorted[i + 1] = key;
    sorted[i + 1].selected = true;
    key.selected = true;
    iterations++;
    return sorted;
}