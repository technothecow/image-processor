add_library(contrib_catch_main
  contrib/catch/catch_main.cpp ../src/tests/CLI_tests.cpp ../src/tests/Validation_tests.cpp ../src/tests/MatrixFilter_tests.cpp ../src/tests/GrayscaleFilter_tests.cpp ../src/tests/NegativeFilter_tests.cpp ../src/tests/SharpFilter_tests.cpp ../src/tests/EdgeFilter_tests.cpp ../src/tests/BlurFilter_tests.cpp ../src/tests/GlitchFilter_tests.cpp ../src/tests/Image_tests.cpp ../src/tests/CropFilter_tests.cpp)

target_include_directories(contrib_catch_main
  PUBLIC contrib/catch)
