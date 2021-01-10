
add_library(AudioFile INTERFACE)

target_include_directories (AudioFile
        INTERFACE $<BUILD_INTERFACE:${AudioFile_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features (AudioFile INTERFACE cxx_std_11)