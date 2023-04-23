#include "GrayscaleFilter.h"
void image_processor::GrayscaleFilter::ApplyFilter(image_processor::Image& image) const {
    static const double R_COEFFICIENT = 0.299;
    static const double G_COEFFICIENT = 0.587;
    static const double B_COEFFICIENT = 0.114;

    auto& channels = image.GetChannels();

    if (channels.size() == 1) {
        return;
    }

    if (channels.size() != 3) {
        throw FilterException(
            "Error: grayscale filter could only be used on three channels. Please make a report on this issue!");
    }

    for (int32_t i = 0; i < image.GetHeight(); ++i) {
        for (int32_t j = 0; j < image.GetWidth(); ++j) {
            channels[0][i][j] = R_COEFFICIENT * channels[2][i][j] + G_COEFFICIENT * channels[1][i][j] +
                                B_COEFFICIENT * channels[0][i][j];
        }
    }

    channels.pop_back();
    channels.pop_back();
}
