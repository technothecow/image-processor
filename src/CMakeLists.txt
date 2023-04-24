set(SOURCES image_processor.cpp Image.cpp CLI.cpp BMP.cpp Filter.cpp CropFilter.cpp GrayscaleFilter.cpp NegativeFilter.cpp EdgeDetectionFilter.cpp SharpFilter.cpp GaussianBlurFilter.cpp GlitchFilter.cpp)

add_executable(image_processor ${SOURCES})

add_catch(test_IP_CLI tests/CLI_tests.cpp CLI.cpp)
add_catch(test_IP_Validation tests/Validation_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_MatrixFilter tests/MatrixFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_GrayscaleFilter tests/GrayscaleFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_NegativeFilter tests/NegativeFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_SharpFilter tests/SharpFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_EdgeFilter tests/EdgeFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_BlurFilter tests/BlurFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_GlitchFilter tests/GlitchFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_CropFilter tests/CropFilter_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)
add_catch(test_IP_Image tests/Image_tests.cpp Filter.cpp Image.cpp GrayscaleFilter.cpp SharpFilter.cpp NegativeFilter.cpp GaussianBlurFilter.cpp EdgeDetectionFilter.cpp CropFilter.cpp GlitchFilter.cpp)

target_include_directories(image_processor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined")
