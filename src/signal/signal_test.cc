#include "src/signal/signal.h"

#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

namespace smoothlib {
namespace {

TEST(MovingAverageTest, EmptyInputProducesEmptyOutput) {
  const std::vector<double> input;
  EXPECT_TRUE(MovingAverage(input, 3).empty());
}

TEST(MovingAverageTest, WindowOfOneIsIdentity) {
  const std::vector<double> input = {1.0, 2.0, 3.0, 4.0, 5.0};
  EXPECT_EQ(MovingAverage(input, 1), input);
}

TEST(MovingAverageTest, ConstantSignalSmoothsToItself) {
  const std::vector<double> input(10, 7.5);
  const std::vector<double> output = MovingAverage(input, 4);
  ASSERT_EQ(output.size(), input.size());
  for (double v : output) {
    EXPECT_DOUBLE_EQ(v, 7.5);
  }
}

TEST(MovingAverageTest, ShrinkingWindowAtStart) {
  const std::vector<double> input = {1.0, 2.0, 3.0, 4.0, 5.0};
  const std::vector<double> expected = {1.0, 1.5, 2.0, 3.0, 4.0};
  const std::vector<double> output = MovingAverage(input, 3);
  ASSERT_EQ(output.size(), expected.size());
  for (std::size_t i = 0; i < expected.size(); ++i) {
    EXPECT_DOUBLE_EQ(output[i], expected[i]) << "at index " << i;
  }
}

TEST(MovingAverageTest, ZeroWindowThrows) {
  const std::vector<double> input = {1.0, 2.0, 3.0};
  EXPECT_THROW(MovingAverage(input, 0), std::invalid_argument);
}

}  // namespace
}  // namespace smoothlib
