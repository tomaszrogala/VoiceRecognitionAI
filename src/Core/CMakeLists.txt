
add_library(Core STATIC
        RecognitionStarter.cpp
        RecognitionStarter.h
        RecognitionResult.h
        VoiceSample.cpp
        VoiceSample.h AutocorrellatedVoiceActivityDetector.cpp AutocorrellatedVoiceActivityDetector.h Normalizer.cpp Normalizer.h LpcExtractor.cpp LpcExtractor.h LinearPredictiveCoding.cpp LinearPredictiveCoding.h)

target_include_directories(Core PUBLIC
        ${POCO_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src/Utils
        ${PROJECT_SOURCE_DIR}/ext/AudioFile)
