#pragma once

#include "Filter.h"
namespace image_processor {

class GrayscaleFilter final : public Filter {
public:
    ~GrayscaleFilter() override = default;

    void ApplyFilter(Image& image) const final;
};

}  // namespace image_processor