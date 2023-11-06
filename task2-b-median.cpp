#include <stdexcept>
#include <vector>

#include "common.h"

// Note: pivot functions are not used in this source file, since
// calculation of median might required finding 2 middle elements
// in case the array length is even (and pivot functions in common.h)
// are not really designed for this


// Function to partition the array using Quick Select with deterministic pivot
size_t deterministic_partition(int *arr, size_t low, size_t high) {
    size_t pivotIdx = deterministicPivot(&arr[low], high - low + 1) + low;
    int pivotValue = arr[pivotIdx];

    // Move the pivot element to the end
    std::swap(arr[pivotIdx], arr[high]);

    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        if (arr[j] < pivotValue) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    // Move the pivot element back to its correct position
    std::swap(arr[i], arr[high]);

    return i;
}

// Quick Select with deterministic pivot
int deterministicQuickSelect(int *arr, size_t low, size_t high, size_t k) {
    if (low == high) {
        return arr[low];
    }

    size_t pivotIdx = deterministic_partition(arr, low, high);

    if (k == pivotIdx) {
        return arr[pivotIdx];
    } else if (k < pivotIdx) {
        return deterministicQuickSelect(arr, low, pivotIdx - 1, k);
    } else {
        return deterministicQuickSelect(arr, pivotIdx + 1, high, k);
    }
}
/**
 * @brief calculate median of @p v in deterministic fashion
 *
 * @param v
 *
 * Constraints:
 *      1. v.size() >= 1
 * Examples:
 *      v = [1]     ---> 1
 *      v = [1,2]   ---> 1.5
 *      v = [3,4,4] ---> 4
 *
 * @return double - median of @p v
 */
double medianDeterministicPivot(std::vector<int> &v)
{
    if (v.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    size_t n = v.size();
    std::vector<int> arr(v);  // Make a copy of the vector as an array

    if (n % 2 == 0) {
        size_t k1 = n / 2 - 1;
        size_t k2 = n / 2;
        return (static_cast<double>(deterministicQuickSelect(&arr[0], 0, n - 1, k1)) +
                static_cast<double>(deterministicQuickSelect(&arr[0], 0, n - 1, k2))) /
               2.0;
    } else {
        size_t k = n / 2;
        return static_cast<double>(deterministicQuickSelect(&arr[0], 0, n - 1, k));
    }
}

size_t random_partition(int *arr, size_t low, size_t high) {
    size_t pivotIdx = uniformRandomPivot(&arr[low], high - low + 1) + low;
    int pivotValue = arr[pivotIdx];

    // Move the pivot element to the end
    std::swap(arr[pivotIdx], arr[high]);

    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        if (arr[j] < pivotValue) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    // Move the pivot element back to its correct position
    std::swap(arr[i], arr[high]);

    return i;
}

int randomQuickSelect(int *arr, size_t low, size_t high, size_t k) {
    if (low == high) {
        return arr[low];
    }

    size_t pivotIdx = random_partition(arr, low, high);

    if (k == pivotIdx) {
        return arr[pivotIdx];
    } else if (k < pivotIdx) {
        return randomQuickSelect(arr, low, pivotIdx - 1, k);
    } else {
        return randomQuickSelect(arr, pivotIdx + 1, high, k);
    }
}
/**
 * @brief calculates median of @p v by selecting pivot uniformly at random
 *
 * @param v
 *
 * Constraints:
 *      1. v.size() >= 1
 * Examples:
 *      v = [1]     ---> 1
 *      v = [1,2]   ---> 1.5
 *      v = [3,4,4] ---> 4
 *
 * @return double - median of @p v
 */
double medianUniformRandomPivot(std::vector<int> &v)
{
    if (v.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    size_t n = v.size();
    std::vector<int> arr(v);  // Make a copy of the vector as an array

    if (n % 2 == 0) {
        size_t k1 = n / 2 - 1;
        size_t k2 = n / 2;
        return (static_cast<double>(randomQuickSelect(&arr[0], 0, n - 1, k1)) +
                static_cast<double>(randomQuickSelect(&arr[0], 0, n - 1, k2))) /
               2.0;
    } else {
        size_t k = n / 2;
        return static_cast<double>(randomQuickSelect(&arr[0], 0, n - 1, k));
    }
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
#include "utils/median.h"
