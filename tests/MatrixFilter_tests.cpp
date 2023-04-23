#include <iostream>
#include "catch.hpp"
#include "../Filter.h"

namespace image_processor {

TEST_CASE("MatrixFilter applies filter to the image") {
    // Create test image
    const int32_t width = 4;
    const int32_t height = 4;
    std::unique_ptr<uint8_t[]> data(new uint8_t[3 * width * height]);
    for (int32_t i = 0; i < width * height; ++i) {
        data[3 * i + 0] = 100;  // B  // NOLINT
        data[3 * i + 1] = 0;    // G
        data[3 * i + 2] = 0;    // R
    }
    Image image(data, width, height, width * 3, true);

    // Create test filter
    std::vector<std::vector<double>> matrix = {
        {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},  // NOLINT
        {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},  // NOLINT
        {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},  // NOLINT
    };
    MatrixFilter filter(matrix);

    // Apply filter
    filter.ApplyFilter(image);

    // Verify result
    std::vector<std::vector<double>> expected_values = {
        {0.392157, 0.392157, 0.392157, 0.392157},  // NOLINT
        {0.392157, 0.392157, 0.392157, 0.392157},  // NOLINT
        {0.392157, 0.392157, 0.392157, 0.392157},  // NOLINT
        {0.392157, 0.392157, 0.392157, 0.392157},  // NOLINT
    };

    const auto& channels = image.GetChannels();
    REQUIRE(channels.size() == 3);
    REQUIRE(image.GetWidth() == width);
    REQUIRE(image.GetHeight() == height);
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            double actual_value = channels[0][i][j];
            double expected_value = expected_values[i][j];
            CAPTURE(i, j, 0, actual_value, expected_value);
            REQUIRE(actual_value == Approx(expected_value).epsilon(0.01));  // NOLINT
        }
    }
}

}  // namespace image_processor