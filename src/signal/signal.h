#ifndef SMOOTHLIB_SIGNAL_H_
#define SMOOTHLIB_SIGNAL_H_

#include <cstddef>
#include <vector>

namespace smoothlib {

// Computes a trailing moving average of `input` with the given `window` size.
//
// The output has the same length as `input`. For the first `window - 1`
// elements, a shrinking window from the start of the sequence is used: the
// element at index `i < window - 1` is the mean of `input[0..i]`. From index
// `window - 1` onward, each element is the mean of the preceding `window`
// values. No padding or NaN is produced.
//
// Throws std::invalid_argument if `window == 0`.
std::vector<double> MovingAverage(const std::vector<double>& input,
                                  std::size_t window);

}  // namespace smoothlib

#endif  // SMOOTHLIB_SIGNAL_H_
