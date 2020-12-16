//
// Created by Dawid Walenciak on 16/12/2020.
//

#ifndef VOICERECOGNITIONAI_FILEMANAGER_H
#define VOICERECOGNITIONAI_FILEMANAGER_H

#include <istream>

namespace Utils {

class FileManager {
public:
    FileManager() = default;

    /**
     * Function to convert stream data to file
     * @param istream data stream
     * @param filePath file path to save data from istream
     */
    void writeStreamToFile(const std::istream& istream, const std::string& filePath);

    /**
     *  Function to remove file under certain path
     * @param filePath path to file to remove
     */
    void removeFile(const std::string& filePath);

    /**
     * @example /tmp/audio_file_1608134823.wav
     * @return Generate path to /tmp/ directory with name "audio_file_<unix timestamp>.wav"
     */
    std::string generateTemporaryPathToFile();
};
}

#endif //VOICERECOGNITIONAI_FILEMANAGER_H
