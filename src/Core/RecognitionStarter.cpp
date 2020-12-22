//
// Created by Dawid Walenciak on 13/10/2020.
//

#include "RecognitionStarter.h"

#include "Logger.h"

using namespace Utils;

namespace Core {

float RecognitionStarter::DEFAULT_SAMPLE_RATE = 16000.0;

RecognitionStarter RecognitionStarter::getInstance() {
    static RecognitionStarter instance;
    return instance;
}

RecognitionResult RecognitionStarter::identify(const std::string& filePathToRecognize) {
    if(voiceSampleLibrary.empty()) {
        Logger::error("Cannot identify sample! Sample library empty.");
        return RecognitionResult("", 0, 0.0);
    }

    VoiceSample voiceSampleToRecognize(filePathToRecognize, DEFAULT_SAMPLE_RATE);
    std::vector<RecognitionResult> resultArray;

    double distanceFromUniversalModel = voiceSampleToRecognize.getDistance(*universalModel);

    for (auto const& [identifier, voiceSample] : voiceSampleLibrary) {
        double distance = voiceSample.getDistance(voiceSampleToRecognize);
        int probability = 100 - (int) (distance/((distance + distanceFromUniversalModel) * 100));
        resultArray.emplace_back(identifier, probability, distance);
    }

    std::sort(resultArray.begin(), resultArray.end(), [](const auto& elem1, const auto& elem2) {
        return elem1.getDistance() > elem2.getDistance();
    });

    return resultArray.front();
}

RecognitionStarter::~RecognitionStarter() = default;

RecognitionStarter::RecognitionStarter() {
    // TODO: load real samples which will be base for recognition
    loadVoiceSample("voiceName1", VoiceSample("TODO", DEFAULT_SAMPLE_RATE));
    loadVoiceSample("voiceName2", VoiceSample("TODO", DEFAULT_SAMPLE_RATE));
    loadVoiceSample("voiceName3", VoiceSample("TODO", DEFAULT_SAMPLE_RATE));
}

void RecognitionStarter::loadVoiceSample(const std::string& identifier,  const VoiceSample& voiceSample) {
    if(voiceSampleLibrary.find(identifier) != voiceSampleLibrary.end()) {
        Logger::error("Identifier: " + identifier + " already exist!");
        return;
    }
    voiceSampleLibrary[identifier] = voiceSample;
    if(universalModel == nullptr) {
        universalModel = std::make_shared<VoiceSample>(voiceSample);
    }
    else {
        universalModel->merge(voiceSample);
    }
}

}
