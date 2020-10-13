
add_library(Core STATIC
        RecognitionStarter.cpp
        RecognitionStarter.h)

target_include_directories(Core PUBLIC
        ${POCO_INCLUDE_DIR})
