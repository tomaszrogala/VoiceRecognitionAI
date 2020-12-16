//
// Created by Dawid Walenciak on 16/12/2020.
//

#include "FileManager.h"

#include <fstream>

namespace Utils {

void FileManager::writeStreamToFile(const std::istream& istream, const std::string& filePath) {
    std::ofstream ofstream;
    ofstream.open(filePath);
    ofstream << istream.rdbuf();
}

void FileManager::removeFile(const std::string& filePath) {
    // TODO: add logic to remove file
}

std::string FileManager::generateTemporaryPathToFile() {
    auto timestamp = std::time(nullptr);
    return "/tmp/audio_file_" + std::to_string(timestamp) + ".wav";
}

}
