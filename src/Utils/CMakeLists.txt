
add_library(Utils STATIC
        FileManager.cpp
        FileManager.h Logger.cpp Logger.h)

target_include_directories(Utils PUBLIC
        ${POCO_INCLUDE_DIR})
