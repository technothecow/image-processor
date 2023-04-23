#pragma once

#include <string>
#include "Image.h"
#include "CLI.h"

namespace image_processor {

struct FilterException : public std::exception {
public:
    explicit FilterException(const std::string& msg) : message_(msg) {
    }

    const char* what() const throw() final {
        return message_.c_str();
    }

private:
    std::string message_;
};

class Filter {
public:
    virtual void ApplyFilter(Image& image) const = 0;

    virtual ~Filter() = default;
};

class ChannelWiseFilter : public Filter {
public:
    ~ChannelWiseFilter() override = default;

    void ApplyFilter(Image& image) const final;

protected:
    virtual void ImplementFilter(Image::Channel& channel) const = 0;
};

class MatrixFilter : public ChannelWiseFilter {
public:
    explicit MatrixFilter(const std::vector<std::vector<double>>& matrix);

    ~MatrixFilter() override = default;

protected:
    void ImplementFilter(Image::Channel& channel) const final;

private:
    std::vector<std::vector<double>> matrix_;
};

class ComplicatedFilter : public Filter {
public:
    ComplicatedFilter();

    ~ComplicatedFilter() override = default;

    void ApplyFilter(Image& image) const final;
    void AddFilter(std::unique_ptr<Filter>&& filter);

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};

void ApplyFilter(Image& image, const FilterCommand& filter);

}  // namespace image_processor