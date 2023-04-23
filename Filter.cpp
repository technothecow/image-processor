#include <sstream>
#include "Filter.h"
#include "GaussianBlurFilter.h"
#include "GlitchFilter.h"
#include "CropFilter.h"
#include "SharpFilter.h"
#include "EdgeDetectionFilter.h"
#include "GrayscaleFilter.h"
#include "NegativeFilter.h"

void image_processor::ChannelWiseFilter::ApplyFilter(image_processor::Image& image) const {
    for (auto& channel : image.GetChannels()) {
        ImplementFilter(channel);
    }
}

void image_processor::MatrixFilter::ImplementFilter(Image::Channel& channel) const {
    ssize_t height = static_cast<ssize_t>(channel.size());
    ssize_t width = static_cast<ssize_t>(channel[0].size());
    ssize_t half_size = static_cast<ssize_t>(matrix_.size()) / 2;

    std::vector<std::vector<double>> buffer(height, std::vector<double>(width));

    for (ssize_t y = 0; y < height; ++y) {
        for (ssize_t x = 0; x < width; ++x) {
            double sum = 0;
            for (ssize_t dy = -half_size; dy <= half_size; ++dy) {
                for (ssize_t dx = -half_size; dx <= half_size; ++dx) {
                    ssize_t fy = std::min(height - 1, std::max(0l, y + dy));
                    ssize_t fx = std::min(width - 1, std::max(0l, x + dx));
                    sum += channel[fy][fx] * matrix_[half_size + dy][half_size + dx];
                }
            }
            buffer[y][x] = std::max(0.0, std::min(1.0, sum));
        }
    }

    std::swap(buffer, channel);
}

image_processor::MatrixFilter::MatrixFilter(const std::vector<std::vector<double>>& matrix) : matrix_(matrix) {
    if (matrix.size() % 2 != 1) {
        throw FilterException("Error: even size of matrix for convolution filter. Please make a report on this issue!");
    }
}

void image_processor::ComplicatedFilter::ApplyFilter(image_processor::Image& image) const {
    for (auto& filter : filters_) {
        filter->ApplyFilter(image);
    }
}

image_processor::ComplicatedFilter::ComplicatedFilter() {
}

void image_processor::ComplicatedFilter::AddFilter(std::unique_ptr<Filter>&& filter) {
    filters_.push_back(std::move(filter));
}

namespace {
template <typename T>
bool IsConvertible(const std::string& str) {
    T value;
    std::stringstream ss(str);
    ss >> std::noskipws >> value;
    return ss.eof() && !ss.fail();
}
}  // namespace

void image_processor::ApplyFilter(image_processor::Image& image, const image_processor::FilterCommand& filter_command) {
    std::unique_ptr<Filter> filter;
    if (filter_command.name == "blur") {
        if (filter_command.params.size() != 1 || !IsConvertible<double>(filter_command.params[0])) {
            throw FilterException("Error: expected float as argument to blur effect.");
        }
        filter = std::make_unique<GaussianBlurFilter>(std::stod(filter_command.params[0]));
    } else if (filter_command.name == "glitch") {
        switch (filter_command.params.size()) {
            case 0:
                filter = std::make_unique<GlitchFilter>();
                break;
            case 1:
                if (!IsConvertible<int>(filter_command.params[0]) || std::stoi(filter_command.params[0]) < 0) {
                    throw FilterException("Error: expected unsigned 31-bit integer as argument to glitch effect");
                }
                filter = std::make_unique<GlitchFilter>(std::stoi(filter_command.params[0]));
                break;
            default:
                throw FilterException("Error: expected zero or one argument to glitch effect");
        }
    } else if (filter_command.name == "crop") {
        if (filter_command.params.size() != 2 || !IsConvertible<int>(filter_command.params[0]) ||
            std::stoi(filter_command.params[0]) < 0 || !IsConvertible<int>(filter_command.params[1]) ||
            std::stoi(filter_command.params[1]) < 0) {
            throw FilterException("Error: expected two unsigned 31-bit integers as argument to crop effect");
        }
        filter = std::make_unique<CropFilter>(stoi(filter_command.params[0]), std::stoi(filter_command.params[1]));
    } else if (filter_command.name == "sharp") {
        if (!filter_command.params.empty()) {
            throw FilterException("Error: no arguments are expected to crop effect");
        }
        filter = std::make_unique<SharpFilter>();
    } else if (filter_command.name == "edge") {
        if (filter_command.params.size() != 1 || !IsConvertible<double>(filter_command.params[0])) {
            throw FilterException("Error: expected float as argument to edge detection effect.");
        }
        filter = std::make_unique<EdgeDetectionFilter>(std::stod(filter_command.params[0]));
    } else if (filter_command.name == "gs") {
        if (!filter_command.params.empty()) {
            throw FilterException("Error: no arguments are expected to grayscale effect");
        }
        filter = std::make_unique<GrayscaleFilter>();
    } else if (filter_command.name == "neg") {
        if (!filter_command.params.empty()) {
            throw FilterException("Error: no arguments are expected to negative effect");
        }
        filter = std::make_unique<NegativeFilter>();
    }
    filter.get()->ApplyFilter(image);
}
