#include "BMP.h"

namespace {
bool IsBMP(std::ifstream& file) {
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size < 2) {
        return false;
    }

    char signature[2];
    file.read(signature, 2);
    file.seekg(0, std::ios::beg);
    return signature[0] == 'B' && signature[1] == 'M';
}
}  // namespace

namespace image_processor {

void WriteBMP(Image& image, std::string filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);

    if (!file) {
        throw FileException("Error: unable to create file '" + filename + "'");
    }

    const int32_t size = image.GetWidth() * image.GetHeight() * 3;
    BMPHeader header(size);
    BITMAPINFOHEADER info_header(image.GetWidth(), -image.GetHeight(), size);

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    const int32_t row_size = image.GetWidth() * BITS_PER_PIXEL;  // Each pixel takes up 3 bytes (B, G, R)
    const int32_t padding =
        (4 - (row_size % 4)) % 4;  // Number of padding bytes needed to make row size a multiple of 4 bytes

    const auto& channels = image.GetChannels();
    const size_t channels_amount = channels.size();

    if (channels_amount != 1 && channels_amount != BITS_PER_PIXEL) {
        throw FileException(
            "Error: invalid amount of channels in result picture. Please make a report about this issue!");
    }

    const int32_t width = image.GetWidth();
    const int32_t height = image.GetHeight();

    for (int32_t y = 0; y < height; ++y) {
        for (int32_t x = 0; x < width; ++x) {
            for (int32_t i = 0; i < BITS_PER_PIXEL; ++i) {
                // Modulo computation for 1-channel and 3-channel cases
                const auto pixel = static_cast<uint8_t>(255.0 * channels[i % channels_amount][y][x]);
                file.write(reinterpret_cast<const char*>(&pixel), sizeof(pixel));
            }
        }
        // Write padding bytes to ensure that each row is a multiple of 4 bytes
        for (int32_t i = 0; i < padding; ++i) {
            file.write("\0", sizeof(uint8_t));
        }
    }

    if (file.fail() || file.bad()) {
        throw FileException("Error: fatal error occurred while writing to file '" + filename +
                            "' (possibly not enough space left on drive)");
    }
}

Image ReadBMP(std::string filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw FileException("Error: could not open file '" + filename + "'");
    }

    if (!IsBMP(file)) {
        throw FileException("Error: file '" + filename + "' is not a BMP");
    }

    BMPHeader header;
    BITMAPINFOHEADER dib_header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
    file.read(reinterpret_cast<char*>(&dib_header), sizeof(dib_header));

    if (dib_header.compression_method != 0) {
        throw FileException("Error: BMP file '" + filename + "' is compressed");
    }

    if (dib_header.colors_in_palette != 0) {
        throw FileException("Error: BMP file '" + filename + "' has a color table");
    }

    if (dib_header.bits_per_pixel != BITS_REQUIRED) {
        throw FileException("Error: BMP file '" + filename + "' is not 24-bit");
    }

    const int32_t width = dib_header.width;
    const int32_t height = dib_header.height;

    if (width <= 0) {
        throw FileException("Error: BMP file '" + filename + "' has non-positive width");
    }

    const int32_t row_size = ((width * 3 + 3) / 4) * 4;  // round up to nearest 4 bytes
    const int32_t image_size = row_size * height;

    std::unique_ptr<uint8_t[]> image_data(new uint8_t[image_size]);
    file.read(reinterpret_cast<char*>(image_data.get()), image_size);

    return Image(image_data, width, std::abs(height), row_size, height < 0);
}

BITMAPINFOHEADER::BITMAPINFOHEADER(int32_t width, int32_t height, uint32_t image_size)
    : width(width), height(height), image_size(image_size) {
}
BITMAPINFOHEADER::BITMAPINFOHEADER() {
}
BMPHeader::BMPHeader(uint32_t size) : size(sizeof(BMPHeader) + sizeof(BITMAPINFOHEADER) + size) {
}
BMPHeader::BMPHeader() {
}
}  // namespace image_processor