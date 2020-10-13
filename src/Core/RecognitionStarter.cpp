//
// Created by Dawid Walenciak on 13/10/2020.
//

#include "RecognitionStarter.h"

#include <utility>

namespace Core {

RecognitionStarter::RecognitionStarter(std::string filePath) : voiceKnown(false), voiceOwner(), audioFilePath(std::move(filePath)) {}

RecognitionStarter::~RecognitionStarter() = default;

void RecognitionStarter::start() {
    // TODO: do main job to recognize voice from audioFilePath
}

bool RecognitionStarter::isVoiceKnown() const {
    return voiceKnown;
}

void RecognitionStarter::setVoiceKnown(bool isVoiceKnown) {
    this->voiceKnown = isVoiceKnown;
}

const std::string& RecognitionStarter::getVoiceOwner() const {
    return voiceOwner;
}

void RecognitionStarter::setVoiceOwner(const std::string& ownerName) {
    this->voiceOwner = ownerName;
}

}
