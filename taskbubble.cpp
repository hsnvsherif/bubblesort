#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

// Bubble Sort Implementation
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Optimized Bubble Sort with a flag
void bubbleSortWithFlag(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // If no swaps were made, the array is already sorted
    }
}

// Function to generate reverse sorted data
std::vector<int> generateReverseSortedData(int size) {
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = size - i; // Generates descending order
    }
    return data;
}

// Function to generate random data
std::vector<int> generateRandomData(int size) {
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 10000; // Random numbers between 0 and 9999
    }
    return data;
}

// Benchmark function for sorting algorithms
void benchmarkSorting(const std::string& name, void (*sortFunc)(std::vector<int>&), std::vector<int> data) {
    auto start = std::chrono::steady_clock::now();
    sortFunc(data);
    auto end = std::chrono::steady_clock::now();

    std::cout << name << ": " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms" << std::endl;
}

int main() {
    // Test sizes
    std::vector<int> testSizes = {5000, 10000, 20000, 30000, 40000, 50000, 60000};

    std::cout << "Number of Elements\tBubble Sort\tBubble Sort With Flag\tReverse Sorted\n";

    for (int size : testSizes) {
        std::cout << size << "\t\t";

        // Benchmarking Bubble Sort with Random Data
        auto randomData = generateRandomData(size);
        auto dataCopy = randomData;
        auto start = std::chrono::steady_clock::now();
        bubbleSort(dataCopy);
        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\t\t";

        // Benchmarking Optimized Bubble Sort
        dataCopy = randomData;
        start = std::chrono::steady_clock::now();
        bubbleSortWithFlag(dataCopy);
        end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "\t\t";

        // Benchmarking Bubble Sort with Reverse Sorted Data
        auto reverseData = generateReverseSortedData(size);
        start = std::chrono::steady_clock::now();
        bubbleSort(reverseData);
        end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << std::endl;
    }

    return 0;
}
