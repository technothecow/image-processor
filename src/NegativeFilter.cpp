#include "NegativeFilter.h"
void image_processor::NegativeFilter::ImplementFilter(Image::Channel& channel) const {
    for (auto& row : channel) {
        for (auto& pixel : row) {
            pixel = 1 - pixel;
        }
    }
}
