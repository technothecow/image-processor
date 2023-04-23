#include "CropFilter.h"

void image_processor::CropFilter::ApplyFilter(image_processor::Image& image) const {
    const int32_t height = std::min(height_, image.GetHeight());
    const int32_t width = std::min(width_, image.GetWidth());
    image.SetHeight(height);
    image.SetWidth(width);
}

image_processor::CropFilter::CropFilter(int32_t width, int32_t height) : width_(width), height_(height) {
}
