add_executable(
        image_processor
        image_processor.cpp
        Image.cpp Image.h CLI.h CLI.cpp BMP.cpp BMP.h Filter.cpp Filter.h CropFilter.cpp CropFilter.h GrayscaleFilter.cpp GrayscaleFilter.h NegativeFilter.cpp NegativeFilter.h EdgeDetectionFilter.cpp EdgeDetectionFilter.h SharpFilter.cpp SharpFilter.h GaussianBlurFilter.cpp GaussianBlurFilter.h GlitchFilter.cpp GlitchFilter.h)

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

include_directories(image_processor)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined")
