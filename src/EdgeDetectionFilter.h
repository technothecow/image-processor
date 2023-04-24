#pragma once

#include "Filter.h"
namespace image_processor {

class EdgeThresholdFilter final : public ChannelWiseFilter {
public:
    explicit EdgeThresholdFilter(double threshold);

    ~EdgeThresholdFilter() override = default;

protected:
    void ImplementFilter(Image::Channel &channel) const final;

private:
    double threshold_;
};

class EdgeDetectionFilter final : public ComplicatedFilter {
public:
    explicit EdgeDetectionFilter(double threshold);

    ~EdgeDetectionFilter() override = default;

private:
    static const std::vector<std::vector<double>> MATRIX;
};

}  // namespace image_processor