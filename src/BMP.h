#pragma once

#include <fstream>
#include "Image.h"

namespace image_processor {

struct FileException : public std::exception {
public:
    explicit FileException(const std::string& msg) : message_(msg) {
    }

    const char* what() const throw() final {
        return message_.c_str();
    }

private:
    std::string message_;
};

static const int16_t BMP_TYPE = 0x4D42;
static const uint16_t BITS_REQUIRED = 24;
static const int32_t BITS_PER_PIXEL = 3;

#pragma pack(push, 1)

struct BITMAPINFOHEADER {
    BITMAPINFOHEADER();
    BITMAPINFOHEADER(int32_t width, int32_t height, uint32_t image_size);

    uint32_t size = sizeof(BITMAPINFOHEADER);
    int32_t width;
    int32_t height;
    uint16_t planes = 1;
    uint16_t bits_per_pixel = BITS_REQUIRED;
    uint32_t compression_method = 0;
    uint32_t image_size;
    int32_t horizontal_resolution = 0;
    int32_t vertical_resolution = 0;
    uint32_t colors_in_palette = 0;
    uint32_t important_colors = 0;
};

struct BMPHeader {
    BMPHeader();
    explicit BMPHeader(uint32_t size);

    uint16_t type = BMP_TYPE;
    uint32_t size;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offbits = sizeof(BMPHeader) + sizeof(BITMAPINFOHEADER);
};

#pragma pack(pop)

Image ReadBMP(std::string filename);

void WriteBMP(Image& image, std::string filename);

}  // namespace image_processor