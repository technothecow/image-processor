#pragma once

#include <vector>
#include <memory>

namespace image_processor {

class Image {
public:
    using Channel = std::vector<std::vector<double>>;

    explicit Image(int32_t width = 0, int32_t height = 0);
    Image(const std::unique_ptr<uint8_t[]>& data, int32_t width, int32_t height, int32_t row_size, bool top_down);

    std::vector<Channel>& GetChannels();
    int32_t GetWidth() const;
    void SetWidth(int32_t width);
    int32_t GetHeight() const;
    void SetHeight(int32_t height);

private:
    std::vector<Channel> channels_;
    int32_t width_;
    int32_t height_;
};

}  // namespace image_processor