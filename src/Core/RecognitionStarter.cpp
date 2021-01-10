//
// Created by Dawid Walenciak on 13/10/2020.
//

#include "RecognitionStarter.h"
#include <algorithm>
#include "Logger.h"

using namespace Utils;

namespace Core {

float RecognitionStarter::DEFAULT_SAMPLE_RATE = 16000.0;
std::string RecognitionStarter::TEST_DATA_ENVIRONMENT_VARIABLE = "TEST_DATA_LOCATION";

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
    if(universalModel == nullptr) {
        universalModel = std::make_shared<VoiceSample>(voiceSampleToRecognize);
    }
    else {
        universalModel->merge(voiceSampleToRecognize);
    }
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
    if(std::getenv(TEST_DATA_ENVIRONMENT_VARIABLE.c_str()) == nullptr) {
        loadVoiceSamplesFromDirectory(std::filesystem::current_path().string());
    }
    else {
        loadVoiceSamplesFromDirectory(std::getenv(TEST_DATA_ENVIRONMENT_VARIABLE.c_str()));
    }
}

void RecognitionStarter::loadVoiceSample(const std::string& identifier,  const VoiceSample& voiceSample) {
    if(voiceSampleLibrary.find(identifier) != voiceSampleLibrary.end()) {
        Logger::error("Identifier: " + identifier + " already exist!");
        return;
    }
    voiceSampleLibrary[identifier] = voiceSample;
}

void RecognitionStarter::loadVoiceSamplesFromDirectory(const std::string& pathToDirectory) {
    for(auto& entry : std::filesystem::directory_iterator(pathToDirectory)) {
        auto filePath = entry.path().string();
        auto filenameWithoutExtension = entry.path().filename().string().substr(0, entry.path().filename().string().find('.'));
        if(filenameWithoutExtension.find("sample_") != std::string::npos) {
            auto sampleOwnerName = filenameWithoutExtension.substr(7);
            loadVoiceSample(sampleOwnerName, VoiceSample(filePath, DEFAULT_SAMPLE_RATE));
        }
    }
}

}
