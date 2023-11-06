#include <stdexcept>
#include <vector>

#include "common.h"

/**
 * @brief finds kth order statistics in the input vector @p v
 *
 * @param v
 * @param k
 * @param pivotFunction - function pointer that specifies the algorithm to select
 * pivot element. quickSelect will be tested/benchmarked with deterministicPivot
 * and uniformRandomPivot implementations from common.h
 *
 * Constraints:
 *      1. v.size() > 0
 *      2. 1 <= k <= v.size()
 *      3. pivotPolicy != nullptr (e.g. it's safe to call pivotPolicy())
 *
 * @return int - kth order statistics of the input array @p v . For example:
 *      v = [3, 2, 5, 4],     k = 2 ---> 3
 *      v = [5, 7, 6, 5],     k = 2 ---> 5
 *      v = [4, 5, 6, 0, 2],  k = 1 ---> 0
 */

size_t partition(int *arr, size_t low, size_t high, size_t pivotIndex) {
    int pivotValue = arr[pivotIndex];
    size_t i = low;

    // Move the pivot to the end
    std::swap(arr[pivotIndex], arr[high]);

    for (size_t j = low; j < high; ++j) {
        if (arr[j] < pivotValue) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    // Move the pivot to its correct position
    std::swap(arr[i], arr[high]);
    return i;
}

int quickSelect(std::vector<int> &v, int k, Pivot_f pivotFunction) {
    if (v.empty() || k <= 0 || k > v.size() || pivotFunction == nullptr) {
        throw std::invalid_argument("Invalid input");
    }

    int left = 0;
    int right = v.size() - 1;

    while (left <= right) {
        // Choose a pivot using the provided pivot function
        size_t pivotIndex = pivotFunction(&v[0] + left, right - left + 1);
        size_t pivotPosition = left + pivotIndex;

        // Partition the vector and get the new pivot position
        size_t newPivotPosition = partition(&v[0], left, right, pivotPosition);

        if (newPivotPosition == k - 1) {
            // The pivot is in its final sorted position
            return v[newPivotPosition];
        } else if (newPivotPosition > k - 1) {
            // The kth order statistic is in the left subarray
            right = newPivotPosition - 1;
        } else {
            // The kth order statistic is in the right subarray
            left = newPivotPosition + 1;
        }
    }

    throw std::runtime_error("Failed to find the kth order statistic");
}


// --------------------
// --------------------
// --------------------

// clang-format off
#include "utils/benchmarkdata.h"

// lengths of arrays to benchmark (for different combinations of pivot policy and input data)
// feel free to change the numbers or add more if necessary
const BenchmarkData benchmarksData {
    BenchmarkData::Builder{}
        .add(PivotPolicy::Deterministic, InputData::SortedArray,            { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::Deterministic, InputData::ReversedSortedArray,    { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::Deterministic, InputData::RandomArray,            { 1LL, 2LL, 5LL, 10LL, 20LL })
        
        .add(PivotPolicy::UniformRandom, InputData::SortedArray,            { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::UniformRandom, InputData::ReversedSortedArray,    { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::UniformRandom, InputData::RandomArray,            { 1LL, 2LL, 5LL, 10LL, 20LL })
    .build()
};
// clang-format on

// don't touch
#include "utils/kth-order-statistics.h"
