//
// Created by Dawid Walenciak on 13/10/2020.
//

#ifndef VOICERECOGNITIONAI_RECOGNITIONSTARTER_H
#define VOICERECOGNITIONAI_RECOGNITIONSTARTER_H

#include <string>

namespace Core {

class RecognitionStarter {
public:
    explicit RecognitionStarter(std::string filePath);
    ~RecognitionStarter();

    void start();

    bool isVoiceKnown() const;
    void setVoiceKnown(bool isVoiceKnown);
    const std::string& getVoiceOwner() const;
    void setVoiceOwner(const std::string& voiceOwner);

private:
    bool voiceKnown;
    std::string voiceOwner;
    std::string audioFilePath;

};

}

#endif //VOICERECOGNITIONAI_RECOGNITIONSTARTER_H
