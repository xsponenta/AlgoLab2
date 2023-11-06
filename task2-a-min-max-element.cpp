#include <stdexcept>
#include <utility>
#include <vector>

/**
 * @brief deterministic algorithm for calculating min/max value in the given vector
 *
 * @param v - vector to find min/max value in
 *
 * Constraints:
 *      1. @p v is not empty
 *      2. first element of the returned pair should be <= than the second element
 *      3. no constraints on the values inside @p v
 *
 * @return std::pair<int, int> pair of min and max elements of @p v
 */
std::pair<int, int> minMaxElement(const std::vector<int> &v)
{
    // TODO: implement
    // throw std::logic_error{ "minMaxElement: not implemented!" };
    // Check if the input vector is not empty
    if (v.empty()) {
        throw std::invalid_argument("Input vector is empty");
    }

    int min_val = v[0]; // Initialize min_val with the first element of the vector
    int max_val = v[0]; // Initialize max_val with the first element of the vector

    // Iterate through the vector to find the minimum and maximum values
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] < min_val) {
            min_val = v[i]; // Update min_val if a smaller element is found
        } else if (v[i] > max_val) {
            max_val = v[i]; // Update max_val if a larger element is found
        }
    }

    // Return a pair containing the minimum and maximum values
    return std::make_pair(min_val, max_val);
}

// lengths of vectors to benchmark (feel free to change)
const std::vector<long long> Ns{ 1, 5, 10, 100, 10000 };

// don't touch
#include "utils/min-max-element.h"
