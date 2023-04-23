#include "GaussianBlurFilter.h"

void image_processor::GaussianBlurFilter::ImplementFilter(image_processor::Image::Channel& channel) const {
    const ssize_t size = static_cast<ssize_t>(kernel_.size());
    const ssize_t half_size = size / 2;

    // Create a temporary buffer to hold the convolved values
    std::vector<std::vector<double>> buffer(channel.size(), std::vector<double>(channel[0].size()));

    // Convolve the data with the kernel_ in the horizontal direction
    for (ssize_t i = 0; i < static_cast<ssize_t>(channel.size()); i++) {
        for (ssize_t j = 0; j < static_cast<ssize_t>(channel[i].size()); j++) {
            double sum = 0;
            for (ssize_t k = -half_size; k <= half_size; k++) {
                size_t index = std::min(channel[i].size() - 1, static_cast<size_t>(std::max(0l, j + k)));
                sum += channel[i][index] * kernel_[k + half_size];
            }
            buffer[i][j] = sum;
        }
    }

    // Convolve the data with the kernel_ in the vertical direction
    for (ssize_t j = 0; j < static_cast<ssize_t>(channel[0].size()); j++) {
        for (ssize_t i = 0; i < static_cast<ssize_t>(channel.size()); i++) {
            double sum = 0;
            for (ssize_t k = -half_size; k <= half_size; k++) {
                size_t index = std::min(channel.size() - 1, static_cast<size_t>(std::max(0l, i + k)));
                sum += buffer[index][j] * kernel_[k + half_size];
            }
            channel[i][j] = sum;
        }
    }
}

image_processor::GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    // Precompute the kernel values
    int size = static_cast<int>(ceil(2 * sigma)) | 1;
    kernel_.resize(size * 2 + 1);
    for (int i = -size; i <= size; i++) {
        double x = i / sigma;
        kernel_[i + size] = exp(-x * x / 2);
    }

    // Normalize the kernel values
    double sum = std::accumulate(kernel_.begin(), kernel_.end(), 0.0);
    for (double& value : kernel_) {
        value /= sum;
    }
}
