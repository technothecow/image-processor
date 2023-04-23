#include <iostream>
#include "CLI.h"
#include "BMP.h"
#include "Filter.h"

int main(int argc, const char* argv[]) {
    try {
        auto [input_file, output_file, filters] = image_processor::ParseArgs(argc, argv);
        auto image = image_processor::ReadBMP(input_file);
        for (const auto& filter : filters) {
            image_processor::ApplyFilter(image, filter);
        }
        image_processor::WriteBMP(image, output_file);
        std::cout << "Completed!\n";
    } catch (const std::bad_alloc& e) {
        std::cerr << "Error: out of memory" << '\n';
        return 1;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (const std::string& message) {
        std::cout << message << '\n';
    }
    return 0;
}
