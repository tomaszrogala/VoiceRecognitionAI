//
// Created by Dawid Walenciak on 13/10/2020.
//

#ifndef VOICERECOGNITIONAI_RECOGNITIONSTARTER_H
#define VOICERECOGNITIONAI_RECOGNITIONSTARTER_H

#include <string>
#include <map>
#include <mutex>

#include "RecognitionResult.h"
#include "VoiceSample.h"

namespace Core {

class RecognitionStarter {
public:
// TODO: instead of using singleton, store samples in database
    static RecognitionStarter getInstance();
    ~RecognitionStarter();

    RecognitionResult identify(const std::string& filePathToRecognize);

private:
    RecognitionStarter();
    void loadVoiceSample(const std::string& identifier, const VoiceSample& voiceSample);

    static RecognitionStarter instance;
    std::map<std::string, VoiceSample> storedVoiceSamples;
};

}

#endif //VOICERECOGNITIONAI_RECOGNITIONSTARTER_H
