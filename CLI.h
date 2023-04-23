#include <tuple>
#include <string>
#include <vector>

#pragma once

namespace image_processor {

struct ParseException : public std::exception {
public:
    explicit ParseException(const std::string& msg) : message_(msg) {
    }

    const char* what() const throw() final {
        return message_.c_str();
    }

private:
    std::string message_;
};

struct FilterCommand {
    std::string name;
    std::vector<std::string> params;
};

std::tuple<std::string, std::string, std::vector<FilterCommand>> ParseArgs(int argc, const char* argv[]);

}  // namespace image_processor