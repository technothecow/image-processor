#pragma once

#include "Filter.h"
namespace image_processor {

class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override = default;

protected:
    void ImplementFilter(Image::Channel &channel) const final;
};

}  // namespace image_processor