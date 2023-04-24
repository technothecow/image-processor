#include <random>
#include <iostream>
#include "GlitchFilter.h"

namespace {
int32_t GenerateRandomInteger(std::mt19937 generator, int32_t min, int32_t max) {
    std::uniform_int_distribution<int32_t> distribution(min, max);
    return distribution(generator);
}
}  // namespace

void image_processor::GlitchFilter::ApplyFilter(image_processor::Image& image) const {
    uint32_t seed=std::random_device{}();
    std::mt19937 generator(seed_.has_value() ? seed_.value() : seed);
    std::cout<<seed<<std::endl;

    static const int32_t COLORS_PER_PIXEL = 256;
    static const int32_t DEVIATION = 25;
    const static int32_t RADIUS = 10;

    // get the image channels
    std::vector<std::reference_wrapper<Image::Channel>> channels;
    auto& image_channels = image.GetChannels();
    for (int32_t i = 0; i < 3; ++i) {
        // Modulo computation for 1-channel and 3-channel cases
        channels.push_back(image_channels[i % image_channels.size()]);
    }

    // create a random lookup table to remap pixel values
    std::vector<int> lut(COLORS_PER_PIXEL);
    for (int i = 0; i < COLORS_PER_PIXEL; i++) {
        lut[i] = GenerateRandomInteger(generator, 0, COLORS_PER_PIXEL - 1);
    }

    // loop through each pixel in the image
    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {

            // randomly select a glitch effect to apply
            int effect = GenerateRandomInteger(generator, 0, 4);

            // apply the glitch effect to each channel
            switch (effect) {
                case 0:
                    // add a random offset to each channel
                    for (auto& channel : channels) {
                        channel.get()[y][x] +=
                            static_cast<double>(GenerateRandomInteger(generator, -DEVIATION, DEVIATION)) /
                            static_cast<double>(COLORS_PER_PIXEL - 1);
                        channel.get()[y][x] = std::max(0.0, std::min(1.0, channel.get()[y][x]));
                    }
                    break;
                case 1:
                    // create a color shift effect by swapping channels
                    std::swap(channels[0].get()[y][x], channels[2].get()[y][x]);
                    break;
                case 2:
                    // create a chromatic aberration effect by shifting channels
                    channels[0].get()[y][x] = channels[0].get()[y][std::min(x + DEVIATION, image.GetWidth() - 1)];
                    channels[2].get()[y][x] = channels[2].get()[y][std::max(x - DEVIATION, 0)];
                    break;
                case 3:
                    // create a pixelation effect by remapping pixel values to a random lookup table
                    channels[0].get()[y][x] = lut[static_cast<int>(
                        round(channels[0].get()[y][x] * static_cast<double>(COLORS_PER_PIXEL - 1)))];
                    channels[1].get()[y][x] = lut[static_cast<int>(
                        round(channels[1].get()[y][x] * static_cast<double>(COLORS_PER_PIXEL - 1)))];
                    channels[2].get()[y][x] = lut[static_cast<int>(
                        round(channels[2].get()[y][x] * static_cast<double>(COLORS_PER_PIXEL - 1)))];
                    break;
                case 4:
                    // create a radial blur effect by averaging pixel values in a circular region around the current
                    // pixel
                    std::vector<double> sum(3);
                    double count = 0.0;
                    for (int i = -RADIUS; i <= RADIUS; i++) {
                        for (int j = -RADIUS; j <= RADIUS; j++) {
                            int nx = x + i;
                            int ny = y + j;
                            if (nx >= 0 && nx < image.GetWidth() && ny >= 0 && ny < image.GetHeight()) {
                                for (int k = 0; k < 3; ++k) {
                                    sum[k] += channels[k].get()[ny][nx];
                                }
                                count += 1.0;
                            }
                        }
                    }
                    for (int k = 0; k < 3; ++k) {
                        channels[k].get()[y][x] = sum[k] / count;
                    }
                    break;
            }
        }
    }
}

image_processor::GlitchFilter::GlitchFilter(std::optional<uint32_t> seed) : seed_(seed) {
}
