
add_library(Core STATIC
        RecognitionStarter.cpp
        RecognitionStarter.h
        RecognitionResult.h
        VoiceSample.cpp
        VoiceSample.h)

target_include_directories(Core PUBLIC
        ${POCO_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src/Utils)
