#include <string>
#include "catch.hpp"
#include "../CLI.h"

TEST_CASE("ParseArgs with no arguments throws help message") {
    const char* argv[] = {"image_processor"};
    int argc = sizeof(argv) / sizeof(char*);

    REQUIRE_THROWS_WITH(image_processor::ParseArgs(argc, argv), Catch::Contains("image_processor"));
}

TEST_CASE("ParseArgs with input and output file only") {
    const char* argv[] = {"image_processor", "input.bmp", "output.bmp"};
    int argc = sizeof(argv) / sizeof(char*);

    auto [input_file_path, output_file_path, filters] = image_processor::ParseArgs(argc, argv);

    REQUIRE(input_file_path == "input.bmp");
    REQUIRE(output_file_path == "output.bmp");
    REQUIRE(filters.empty());
}

TEST_CASE("ParseArgs with multiple filters and options") {
    const char* argv[] = {"image_processor", "input.bmp", "output.bmp", "-crop", "100", "100", "-gs", "-edge", "50"};
    int argc = sizeof(argv) / sizeof(char*);

    auto [input_file_path, output_file_path, filters] = image_processor::ParseArgs(argc, argv);

    REQUIRE(input_file_path == "input.bmp");
    REQUIRE(output_file_path == "output.bmp");
    REQUIRE(filters.size() == 3);

    REQUIRE(filters[0].name == "crop");
    REQUIRE(filters[0].params.size() == 2);
    REQUIRE(filters[0].params[0] == "100");
    REQUIRE(filters[0].params[1] == "100");

    REQUIRE(filters[1].name == "gs");
    REQUIRE(filters[1].params.empty());

    REQUIRE(filters[2].name == "edge");
    REQUIRE(filters[2].params.size() == 1);
    REQUIRE(filters[2].params[0] == "50");
}