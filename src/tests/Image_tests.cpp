#include "catch.hpp"
#include "../Image.h"

TEST_CASE("Image constructor with valid parameters") {
    std::unique_ptr<uint8_t[]> data(new uint8_t[6]{255, 0, 0, 0, 255, 0});  // NOLINT
    int32_t width = 2;
    int32_t height = 1;
    int32_t row_size = 6;  // NOLINT
    bool top_down = true;

    image_processor::Image image(data, width, height, row_size, top_down);

    REQUIRE(image.GetWidth() == 2);
    REQUIRE(image.GetHeight() == 1);

    auto& channels = image.GetChannels();
    REQUIRE(channels.size() == 3);
    REQUIRE(channels[0].size() == 1);
    REQUIRE(channels[0][0].size() == 2);
    REQUIRE(channels[1].size() == 1);
    REQUIRE(channels[1][0].size() == 2);
    REQUIRE(channels[2].size() == 1);
    REQUIRE(channels[2][0].size() == 2);

    REQUIRE(channels[0][0][0] == 1.0);
    REQUIRE(channels[0][0][1] == 0.0);
    REQUIRE(channels[1][0][0] == 0.0);
    REQUIRE(channels[1][0][1] == 1.0);
    REQUIRE(channels[2][0][0] == 0.0);
    REQUIRE(channels[2][0][1] == 0.0);
}

TEST_CASE("Set width of the image") {
    image_processor::Image image(2, 2);
    auto& channels = image.GetChannels();
    channels[0][0][0] = 0.5;  // NOLINT
    channels[0][0][1] = 0.3;  // NOLINT
    channels[0][1][0] = 0.8;  // NOLINT
    channels[0][1][1] = 0.2;  // NOLINT

    image.SetWidth(3);

    REQUIRE(image.GetWidth() == 3);
    REQUIRE(image.GetHeight() == 2);
    channels = image.GetChannels();
    REQUIRE(channels.size() == 3);
    REQUIRE(channels[0].size() == 2);
    REQUIRE(channels[0][0].size() == 3);
    REQUIRE(channels[0][1].size() == 3);
    REQUIRE(channels[0][0][0] == 0.5);  // NOLINT
    REQUIRE(channels[0][0][1] == 0.3);  // NOLINT
    REQUIRE(channels[0][0][2] == 0.0);
    REQUIRE(channels[0][1][0] == 0.8);  // NOLINT
    REQUIRE(channels[0][1][1] == 0.2);  // NOLINT
    REQUIRE(channels[0][1][2] == 0.0);
}

TEST_CASE("Set height of the image") {
    const int32_t width = 2;
    const int32_t height = 2;
    const int32_t new_height = 3;
    const std::unique_ptr<uint8_t[]> data(new uint8_t[12]{255, 0, 0, 0, 255, 0, 0, 0, 255, 0, 0, 0});
    const int32_t row_size = width * 3;
    const bool top_down = false;

    image_processor::Image image(data, width, height, row_size, top_down);
    REQUIRE(image.GetHeight() == height);

    image.SetHeight(new_height);
    REQUIRE(image.GetHeight() == new_height);

    const auto& channels = image.GetChannels();
    REQUIRE(channels.size() == 3);
    for (const auto& channel : channels) {
        REQUIRE(channel.size() == new_height);
        for (const auto& row : channel) {
            REQUIRE(row.size() == width);
        }
    }
}
