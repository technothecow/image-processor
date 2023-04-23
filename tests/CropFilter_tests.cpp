#include "catch.hpp"
#include "../Image.h"
#include "../CropFilter.h"

namespace image_processor {

TEST_CASE("CropFilter applies filter to the image") {
    // Create test image
    const int32_t width = 4;
    const int32_t height = 4;
    std::unique_ptr<uint8_t[]> data(new uint8_t[3 * width * height]);
    for (int32_t i = 0; i < width * height; ++i) {
        data[3 * i + 0] = 0;    // B
        data[3 * i + 1] = 212;  // G  // NOLINT
        data[3 * i + 2] = 133;  // R  // NOLINT
    }
    Image image(data, width, height, width * 3, true);

    CropFilter filter(2, 2);

    // Apply filter
    filter.ApplyFilter(image);

    // Verify result
    std::vector<std::vector<double>> expected_values = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
    };

    const auto& channels = image.GetChannels();
    REQUIRE(channels.size() == 3);
    REQUIRE(image.GetWidth() == 2);
    REQUIRE(image.GetHeight() == 2);
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            double actual_value = channels[0][i][j];
            double expected_value = expected_values[i][j];
            CAPTURE(i, j, 0, actual_value, expected_value);
            REQUIRE(actual_value == Approx(expected_value).epsilon(0.01));  // NOLINT
        }
    }
}

TEST_CASE("CropFilter applies filter to the image with extra size") {
    // Create test image
    const int32_t width = 4;
    const int32_t height = 4;
    std::unique_ptr<uint8_t[]> data(new uint8_t[3 * width * height]);
    for (int32_t i = 0; i < width * height; ++i) {
        data[3 * i + 0] = 0;    // B
        data[3 * i + 1] = 212;  // G  // NOLINT
        data[3 * i + 2] = 133;  // R  // NOLINT
    }
    Image image(data, width, height, width * 3, true);

    CropFilter filter(5, 5);  // NOLINT

    // Apply filter
    filter.ApplyFilter(image);

    // Verify result
    std::vector<std::vector<double>> expected_values = {
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 0.0, 0.0, 0.0},
    };

    const auto& channels = image.GetChannels();
    REQUIRE(channels.size() == 3);
    REQUIRE(image.GetWidth() == 4);
    REQUIRE(image.GetHeight() == 4);
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            double actual_value = channels[0][i][j];
            double expected_value = expected_values[i][j];
            CAPTURE(i, j, 0, actual_value, expected_value);
            REQUIRE(actual_value == Approx(expected_value).epsilon(0.01));  // NOLINT
        }
    }
}

}  // namespace image_processor