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
    case Sort::PANCAKE_SORT:
        elements = pancakeSort(elements);
        break;
    case Sort::MERGE_SORT:
        elements = mergeSort(elements);
        break;
    default:
        break;
    }
}

void SortManager::resizeElementsRect()
{
    // TODO: Fix elements not showing if elements > 8000
    float currentX = WINDOW_WIDTH / 2.0f - (WINDOW_WIDTH / 5.75f);
    constexpr float MAX_RECTANGLE_HEIGHT = 150.0f;
    for (int i = 0; i < numElements; i++)
    {
        const float height = MAX_RECTANGLE_HEIGHT * (static_cast<float>((elements[i].val)) / numElements);
        const float width = MAX_RECTANGLE_HEIGHT / numElements * 2;
        const float x = currentX;
        const float y = WINDOW_HEIGHT / 2.0f - height;
        elements[i].rect = {
            x,
            y,
            width,
            height,
        };
        currentX += width;
    }
}

std::vector<Element> SortManager::bubbleSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    for (int i = 0; i < numElements - 1 - iterations; i++)
    {
        if (sorted[i].val > sorted[i + 1].val)
        {
            std::swap(sorted[i].val, sorted[i + 1].val);
        }
    }
    sorted[numElements - 1 - iterations].selected = true;
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

std::vector<Element> SortManager::pancakeSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    int currSize = numElements - iterations;

    if (currSize <= 1)
        return sorted;

    auto maxIt = std::max_element(
        sorted.begin(),
        sorted.begin() + currSize,
        [](const Element &a, const Element &b)
        {
            return a.val < b.val;
        });
    int maxIndex = std::distance(sorted.begin(), maxIt);

    if (maxIndex != currSize - 1)
    {
        std::reverse(sorted.begin(), sorted.begin() + maxIndex + 1);
        std::reverse(sorted.begin(), sorted.begin() + currSize);
    }

    sorted[currSize - 1].selected = true;
    iterations++;
    return sorted;
}

std::vector<Element> SortManager::mergeSort(const std::vector<Element> &elements)
{
    std::vector<Element> sorted{elements};
    int currSize = std::pow(2, iterations);
    if (currSize > numElements - 1)
        return sorted;
    std::vector<Element> mergeSortArr1(numElements);
    std::vector<Element> mergeSortArr2(numElements);

    for (int leftStart = 0; leftStart < numElements - 1; leftStart += 2 * currSize)
    {
        int mid = std::min(leftStart + currSize - 1, numElements - 1);
        int rightEnd = std::min(leftStart + 2 * currSize - 1, numElements - 1);
        int n1 = mid - leftStart + 1;
        int n2 = rightEnd - mid;

        for (int i = 0; i < n1; i++)
        {
            mergeSortArr1[i] = sorted[leftStart + i];
        }
        for (int i = 0; i < n2; i++)
        {
            mergeSortArr2[i] = sorted[mid + 1 + i];
        }
        int i = 0;
        int j = 0;
        int k = leftStart;

        while (i < n1 && j < n2)
        {
            if (mergeSortArr1[i].val <= mergeSortArr2[j].val)
            {
                sorted[k] = mergeSortArr1[i];
                i++;
            }
            else
            {
                sorted[k] = mergeSortArr2[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            sorted[k] = mergeSortArr1[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            sorted[k] = mergeSortArr2[j];
            j++;
            k++;
        }
        sorted[mid].selected = true;
    }
    iterations++;
    return sorted;
}