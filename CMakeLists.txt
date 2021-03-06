cmake_minimum_required(VERSION 3.9)
project(VoiceRecognitionAI)

set(CMAKE_CXX_STANDARD 17)

# External libs

find_package(Poco REQUIRED COMPONENTS Foundation Net Zip Util)
set(POCO_INCLUDE_DIR $ENV{Poco_DIR}/include)

# Main executable

add_executable(VoiceRecognitionAI
        ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_include_directories(VoiceRecognitionAI PUBLIC
        ${POCO_INCLUDE_DIR})

target_link_libraries(VoiceRecognitionAI PUBLIC
        Poco::Foundation
        Poco::Net
        Poco::Util
        AudioFile
        Core
        Rest
        Utils)

# Internal components

add_subdirectory(${PROJECT_SOURCE_DIR}/ext/AudioFile)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/Core)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Rest)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/Utils)
