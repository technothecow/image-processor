#include "CLI.h"

namespace image_processor {
std::tuple<std::string, std::string, std::vector<FilterCommand>> ParseArgs(int argc, const char* argv[]) {
    if (argc == 1) {
        std::string help =
            "\033[1m\033[38;2;255;165;0mimage_processor\033[0m - a CLI app that applies filters to BMP images\n\n";
        help +=
            "\033[1mUsage:\033[0m \033[38;2;255;105;97mimage_processor\033[0m \033[38;2;255;218;185minput_file\033[0m "
            "\033[38;2;255;218;185moutput_file\033[0m [\033[38;2;176;196;222m-filter1\033[0m "
            "\033[38;2;176;196;222moption1\033[0m \033[38;2;176;196;222moption2\033[0m ...] "
            "[\033[38;2;176;196;222m-filter2\033[0m \033[38;2;176;196;222moption1\033[0m "
            "\033[38;2;176;196;222moption2\033[0m ...] ...\n\n";
        help += "\033[1mArguments:\033[0m\n";
        help += "  \033[38;2;255;218;185minput_file\033[0m\tPath to the input BMP file\n";
        help += "  \033[38;2;255;218;185moutput_file\033[0m\tPath to the output BMP file\n";
        help += "  \033[38;2;176;196;222m-filter1\033[0m\t\tName of the first filter to apply\n";
        help += "  \033[38;2;176;196;222m-option1\033[0m\t\tFilter option 1 for filter 1\n";
        help += "  \033[38;2;176;196;222m-option2\033[0m\t\tFilter option 2 for filter 1\n";
        help += "  ...\n\n";
        help += "\033[1mAvailable Filters:\033[0m\n";
        help +=
            "  \033[38;2;176;196;222m-crop\033[0m \033[38;2;255;218;185mwidth\033[0m "
            "\033[38;2;255;218;185mheight\033[0m\tCrops the image to the specified width and height\n";
        help += "  \033[38;2;176;196;222m-gs\033[0m\t\t\t\t\tConverts the image to grayscale\n";
        help += "  \033[38;2;176;196;222m-neg\033[0m\t\t\t\t\tInverts the colors of the image\n";
        help += "  \033[38;2;176;196;222m-sharp\033[0m\t\t\t\tApplies a sharpening filter to the image\n";
        help +=
            "  \033[38;2;176;196;222m-edge\033[0m \033[38;2;255;218;185mthreshold\033[0m\t\tApplies an edge detection "
            "filter to the image with the specified threshold\n";
        help +=
            "  \033[38;2;176;196;222m-blur\033[0m \033[38;2;255;218;185msigma\033[0m\t\t\tApplies a Gaussian blur "
            "filter "
            "to the image with the specified sigma\n";
        help +=
            "  \033[38;2;176;196;222m-glitch\033[0m \033[38;2;255;218;185mseed\033[0m\t\t\tApplies a glitch effect to "
            "the image with the specified seed\n";

        throw help;
    }

    std::string input_file_path = argv[1];
    std::string output_file_path = argv[2];
    std::vector<FilterCommand> filters;

    for (int i = 3; i < argc; i++) {
        std::string arg = argv[i];

        if (arg[0] == '-') {
            filters.push_back({arg.substr(1)});
        } else {
            if (filters.empty()) {
                throw ParseException("Error: parameter '" + arg + "' specified before filter command");
            }
            filters.back().params.push_back(arg);
        }
    }

    return std::make_tuple(std::move(input_file_path), std::move(output_file_path), std::move(filters));
}
}  // namespace image_processor