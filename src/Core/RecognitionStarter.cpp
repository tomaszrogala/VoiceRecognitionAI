//
// Created by Dawid Walenciak on 13/10/2020.
//

#include "RecognitionStarter.h"

namespace Core {

RecognitionStarter RecognitionStarter::getInstance() {
    return instance;
}

RecognitionResult RecognitionStarter::identify(const std::string& filePathToRecognize) {
    return RecognitionResult("", 0, 0.0);
}

RecognitionStarter::~RecognitionStarter() = default;

RecognitionStarter::RecognitionStarter() {
    loadVoiceSample("test1", *(new VoiceSample()));
}

void RecognitionStarter::loadVoiceSample(const std::string& identifier,  const VoiceSample& voiceSample) {
    storedVoiceSamples[identifier] = voiceSample;
}

}
