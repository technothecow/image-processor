#pragma once

#include "Filter.h"
namespace image_processor {

class SharpFilter final : public MatrixFilter {
public:
    SharpFilter();

    ~SharpFilter() override = default;

private:
    static const std::vector<std::vector<double>> SHARP_MATRIX;
};

}  // namespace image_processor