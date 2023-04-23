#include "catch.hpp"
#include "../Image.h"
#include "../GrayscaleFilter.h"

namespace image_processor {

TEST_CASE("GrayscaleFilter applies filter to the image") {
    // Create test image
    const int32_t width = 4;
    const int32_t height = 4;
    std::unique_ptr<uint8_t[]> data(new uint8_t[3 * width * height]);
    for (int32_t i = 0; i < width * height; ++i) {
        data[3 * i + 0] = 111;  // B  // NOLINT
        data[3 * i + 1] = 212;  // G  // NOLINT
        data[3 * i + 2] = 33;   // R  // NOLINT
    }
    Image image(data, width, height, width * 3, true);

    GrayscaleFilter filter;

    // Apply filter
    filter.ApplyFilter(image);

    // Verify result
    std::vector<std::vector<double>> expected_values = {
        {0.576333, 0.576333, 0.576333, 0.576333},  // NOLINT
        {0.576333, 0.576333, 0.576333, 0.576333},  // NOLINT
        {0.576333, 0.576333, 0.576333, 0.576333},  // NOLINT
        {0.576333, 0.576333, 0.576333, 0.576333},  // NOLINT
    };

    const auto& channels = image.GetChannels();
    REQUIRE(channels.size() == 1);
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