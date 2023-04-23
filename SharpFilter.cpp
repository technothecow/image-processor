#include "SharpFilter.h"
const std::vector<std::vector<double>> image_processor::SharpFilter::SHARP_MATRIX = {
    {0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
image_processor::SharpFilter::SharpFilter() : MatrixFilter(SHARP_MATRIX) {
}
