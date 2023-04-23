#pragma once

#include "Filter.h"

namespace image_processor {

class CropFilter final : public Filter {
public:
    CropFilter(int32_t width, int32_t height);

    ~CropFilter() override = default;

    void ApplyFilter(Image& image) const final;

private:
    int32_t width_;
    int32_t height_;
};

}  // namespace image_processor