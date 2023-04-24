#pragma once

#include <optional>
#include "Filter.h"
namespace image_processor {

class GlitchFilter final : public Filter {
public:
    explicit GlitchFilter(std::optional<uint32_t> seed = std::nullopt);

    ~GlitchFilter() override = default;

    void ApplyFilter(Image& image) const final;

private:
    std::optional<uint32_t> seed_;
};

}  // namespace image_processor