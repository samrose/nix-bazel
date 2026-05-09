#include "src/signal/signal.h"

#include <stdexcept>

namespace smoothlib {

std::vector<double> MovingAverage(const std::vector<double>& input,
                                  std::size_t window) {
  if (window == 0) {
    throw std::invalid_argument("window must be > 0");
  }

  std::vector<double> output;
  output.reserve(input.size());

  double running_sum = 0.0;
  for (std::size_t i = 0; i < input.size(); ++i) {
    running_sum += input[i];
    if (i >= window) {
      running_sum -= input[i - window];
    }
    const std::size_t denom = (i + 1 < window) ? (i + 1) : window;
    output.push_back(running_sum / static_cast<double>(denom));
  }

  return output;
}

}  // namespace smoothlib
