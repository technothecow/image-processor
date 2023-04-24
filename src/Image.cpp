#include "Image.h"

namespace image_processor {

std::vector<Image::Channel>& Image::GetChannels() {
    return channels_;
}

Image::Image(const std::unique_ptr<uint8_t[]>& data, int32_t width, int32_t height, int32_t row_size, bool top_down)
    : width_(width), height_(height) {
    static const int32_t IMAGE_CHANNELS = 3;
    static const double PRECISION = 255;

    channels_.resize(IMAGE_CHANNELS);
    for (size_t k = 0; k < IMAGE_CHANNELS; ++k) {
        channels_[k].resize(height);
    }

    for (int32_t index = 0; index < height; ++index) {
        auto i = top_down ? index : height - index - 1;  // Positive height (down-up) case handling
        for (size_t k = 0; k < IMAGE_CHANNELS; ++k) {
            channels_[k][i].resize(width);
        }
        for (int32_t j = 0; j < width; ++j) {
            for (int32_t k = 0; k < IMAGE_CHANNELS; ++k) {
                channels_[k][i][j] = static_cast<double>(data[index * row_size + IMAGE_CHANNELS * j + k]) / PRECISION;
            }
        }
    }
}

int32_t Image::GetWidth() const {
    return width_;
}

void Image::SetWidth(int32_t width) {
    for (auto& channel : channels_) {
        for (auto& row : channel) {
            row.resize(width);
        }
    }
    width_ = width;
}

int32_t Image::GetHeight() const {
    return height_;
}

void Image::SetHeight(int32_t height) {
    for (auto& channel : channels_) {
        channel.resize(height);
        if (height > height_) {
            for (int32_t i = height_; i < height; ++i) {
                channel[i].resize(GetWidth());
            }
        }
    }
    height_ = height;
}
Image::Image(int32_t width, int32_t height) : width_(width), height_(height) {
    channels_.resize(3);
    SetHeight(height);
    SetWidth(width);
}

}  // namespace image_processor