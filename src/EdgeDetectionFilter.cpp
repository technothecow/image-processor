#include "EdgeDetectionFilter.h"
#include "GrayscaleFilter.h"

namespace image_processor {

const std::vector<std::vector<double>> EdgeDetectionFilter::MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : ComplicatedFilter() {
    AddFilter(std::make_unique<GrayscaleFilter>());
    AddFilter(std::make_unique<MatrixFilter>(MATRIX));
    AddFilter(std::make_unique<EdgeThresholdFilter>(threshold));
}
void EdgeThresholdFilter::ImplementFilter(Image::Channel& channel) const {
    for (auto& row : channel) {
        for (auto& pixel : row) {
            pixel = pixel > threshold_ ? 1 : 0;
        }
    }
}
EdgeThresholdFilter::EdgeThresholdFilter(double threshold) : threshold_(threshold) {
}

}  // namespace image_processor