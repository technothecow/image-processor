#include "catch.hpp"
#include "../Filter.h"

TEST_CASE("ApplyFilter throws FilterException when 'blur' filter is called with an incorrect argument") {
    image_processor::Image image;
    image_processor::FilterCommand filter_command{"blur", {"not_a_float"}};
    REQUIRE_THROWS_AS(image_processor::ApplyFilter(image, filter_command), image_processor::FilterException);
}

TEST_CASE("ApplyFilter throws FilterException when 'glitch' filter is called with an incorrect argument") {
    image_processor::Image image;
    image_processor::FilterCommand filter_command{"glitch", {"-1"}};
    REQUIRE_THROWS_AS(image_processor::ApplyFilter(image, filter_command), image_processor::FilterException);
}

TEST_CASE("ApplyFilter throws FilterException when 'crop' filter is called with incorrect arguments") {
    image_processor::Image image;
    image_processor::FilterCommand filter_command{"crop", {"not_a_uint", "not_a_uint"}};
    REQUIRE_THROWS_AS(image_processor::ApplyFilter(image, filter_command), image_processor::FilterException);
}

TEST_CASE("ApplyFilter throws FilterException when 'edge' filter is called with an incorrect argument") {
    image_processor::Image image;
    image_processor::FilterCommand filter_command{"edge", {"not_a_float"}};
    REQUIRE_THROWS_AS(image_processor::ApplyFilter(image, filter_command), image_processor::FilterException);
}

TEST_CASE("ApplyFilter throws FilterException when 'gs' filter is called with arguments") {
    image_processor::Image image;
    image_processor::FilterCommand filter_command{"gs", {"not_empty"}};
    REQUIRE_THROWS_AS(image_processor::ApplyFilter(image, filter_command), image_processor::FilterException);
}

TEST_CASE("ApplyFilter throws FilterException when 'neg' filter is called with arguments") {
    image_processor::Image image;
    image_processor::FilterCommand filter_command{"neg", {"not_empty"}};
    REQUIRE_THROWS_AS(image_processor::ApplyFilter(image, filter_command), image_processor::FilterException);
}