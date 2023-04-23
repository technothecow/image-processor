#pragma once

#include <cmath>
#include <numeric>
#include "Filter.h"
namespace image_processor {

class GaussianBlurFilter final : public ChannelWiseFilter {
public:
    explicit GaussianBlurFilter(double sigma);

    ~GaussianBlurFilter() override = default;

protected:
    void ImplementFilter(Image::Channel& channel) const final;

private:
    std::vector<double> kernel_;
};

}  // namespace image_processor