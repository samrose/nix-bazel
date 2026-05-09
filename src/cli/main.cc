#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "src/signal/signal.h"

int main(int argc, char** argv) {
  std::size_t window = 3;
  if (argc > 1) {
    window = static_cast<std::size_t>(std::stoul(argv[1]));
  }

  std::vector<double> input;
  for (double x; std::cin >> x;) {
    input.push_back(x);
  }

  const std::vector<double> output = smoothlib::MovingAverage(input, window);

  for (std::size_t i = 0; i < output.size(); ++i) {
    if (i > 0) std::cout << ' ';
    std::cout << output[i];
  }
  std::cout << '\n';
  return 0;
}
