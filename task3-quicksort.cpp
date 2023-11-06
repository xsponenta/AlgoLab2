#include <stdexcept>
#include <vector>
#include <random>
#include "common.h"
/**
 * @brief selects median as pivot in deterministic fashion
 *
 * @param data - pointer to the part of array
 * @param n - number of elements in (sub)array pointed to by @p data
 *
 * Constraints (should hold in quickSortMedianPivot(...) implementation)
 *      1. @p data is not nullptr
 *      2. @p n > 0
 *
 * @return size_t index of pivot element (should be in range [0; n - 1])
 */
size_t deterministicMedianPivot(int *data, size_t n)
{
  if (data == nullptr || n <= 0) {
    throw std::invalid_argument("Invalid input for deterministicMedianPivot");
  }

  size_t left = 0;
  size_t right = n - 1;
  size_t target = n / 2;

  while (left < right) {
    size_t pivotIndex = left;
    size_t pivotNewIndex = left;

    for (size_t i = left + 1; i <= right; i++) {
      if (data[i] < data[pivotIndex]) {
        std::swap(data[i], data[pivotNewIndex]);
        pivotNewIndex++;
      }
    }

    std::swap(data[pivotIndex], data[pivotNewIndex]);

    if (pivotNewIndex == target) {
      return pivotNewIndex;
    } else if (pivotNewIndex < target) {
      left = pivotNewIndex + 1;
    } else {
      right = pivotNewIndex - 1;
    }
  }

  return left;
}

/**
 * @brief selects median as pivot using randomized approach
 *
 * @param data - pointer to the part of array
 * @param n - number of elements in (sub)array pointed to by @p data
 *
 * Constraints (should hold in quickSortMedianPivot(...) implementation)
 *      1. @p data is not nullptr
 *      2. @p n > 0
 *
 * @return size_t index of pivot element (should be in range [0; n - 1])
 */
size_t uniformRandomMedianPivot(int *data, size_t n) {
  if (data == nullptr || n <= 0) {
    throw std::invalid_argument("Invalid input for uniformRandomMedianPivot");
  }
  size_t randomIndex = rand() % n;
  std::swap(data[randomIndex], data[n - 1]);

  return n - 1; //
}

// --------------------
// --------------------
// --------------------

// note: the quicksort logic of applying pivot function that finds the median might
// be different as opposed to simple pivot functions (i.e. deterministicPivot,
// uniformRandomPivot), hence there are 2 implementations of quickSort to be done

size_t partition(std::vector<int> &v, Pivot_f pivotFunction, size_t left, size_t right) {
  size_t pivotIndex = pivotFunction(&v[left], right - left + 1) + left;
  int pivotValue = v[pivotIndex];
  std::swap(v[pivotIndex], v[right]);

  size_t storeIndex = left;
  for (size_t i = left; i < right; ++i) {
    if (v[i] < pivotValue) {
      std::swap(v[i], v[storeIndex]);
      ++storeIndex;
    }
  }

  std::swap(v[storeIndex], v[right]);
  return storeIndex;
}

void quickSort(std::vector<int> &v, Pivot_f pivotFunction, size_t left, size_t right) {
  if (left < right) {
    size_t pivotIndex = partition(v, pivotFunction, left, right);

    if (left < pivotIndex) {
      quickSort(v, pivotFunction, left, pivotIndex - 1);
    }
    if (pivotIndex < right) {
      quickSort(v, pivotFunction, pivotIndex + 1, right);
    }
  }
}

/**
 * @brief quicksort implementation for simple pivot selection methods
 *
 * @param v - vector to sort
 * @param pivotFunction - function pointer that specifies the algorithm to select
 * pivot element. quickSortSimplePivot will be tested/benchmarked with
 * deterministicPivot and uniformRandomPivot implementations from common.h
 */
void quickSortSimplePivot(std::vector<int> &v, Pivot_f pivotFunction)
{
  if (v.empty()) {
    return;
  }
  quickSort(v, pivotFunction, 0, v.size() - 1);
}

/**
 * @brief quicksort implementation with median element as pivot
 *
 * @param v - vector to sort
 * @param pivotFunction - function pointer that specifies the algorithm to select
 * pivot element. quickSortMedianPivot will be tested/benchmarked with
 * deterministicMedianPivot and uniformRandomMedianPivot implementations
 */
void quickSortMedianPivot(std::vector<int> &v, Pivot_f pivotFunction)
{
  if (v.empty()) {
    return;
  }
  quickSort(v, pivotFunction, 0, v.size() - 1);
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
        .add(PivotPolicy::Deterministic, InputData::SortedArray,                { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::Deterministic, InputData::ReversedSortedArray,        { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::Deterministic, InputData::RandomArray,                { 1LL, 2LL, 5LL, 10LL, 20LL })

        .add(PivotPolicy::UniformRandom, InputData::SortedArray,                { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::UniformRandom, InputData::ReversedSortedArray,        { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::UniformRandom, InputData::RandomArray,                { 1LL, 2LL, 5LL, 10LL, 20LL })

        .add(PivotPolicy::MedianDeterministic, InputData::SortedArray,          { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::MedianDeterministic, InputData::ReversedSortedArray,  { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::MedianDeterministic, InputData::RandomArray,          { 1LL, 2LL, 5LL, 10LL, 20LL })

        .add(PivotPolicy::MedianUniformRandom, InputData::SortedArray,          { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::MedianUniformRandom, InputData::ReversedSortedArray,  { 1LL, 2LL, 5LL, 10LL, 20LL })
        .add(PivotPolicy::MedianUniformRandom, InputData::RandomArray,          { 1LL, 2LL, 5LL, 10LL, 20LL })
    .build()
};
// clang-format on

// don't touch
#include "utils/quicksort.h"
