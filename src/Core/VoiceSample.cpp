//
// Created by Dawid Walenciak on 13/12/2020.
//

#include "VoiceSample.h"

#include <string>
#include <sstream>
#include <utility>

#include "Logger.h"

using namespace Utils;

namespace Core {

std::vector<double> VoiceSample::extractFeaturesFromSampleFile(const std::string& filePath, float sampleRate) {
    return std::vector<double>();
}

VoiceSample::VoiceSample(const std::string& pathToSampleFile, float sampleRate)
: VoiceSample(extractFeaturesFromSampleFile(pathToSampleFile, sampleRate)) {}

VoiceSample::VoiceSample(std::vector<double> features)
: currentSampleFeatures(std::move(features)), mergeCount(1) {}

VoiceSample::VoiceSample(const VoiceSample& voiceSample)
: currentSampleFeatures(voiceSample.currentSampleFeatures), mergeCount(1) {}

// TODO
double VoiceSample::getDistance(const VoiceSample& voiceSample) {
    return 0;
}

void VoiceSample::merge(const std::vector<double>& features) {
    if(currentSampleFeatures.size() == features.size()) {
        Logger::error("Features size of new Voice Sample is different than current one!");
        return;
    }
    for(int i=0; i<currentSampleFeatures.size(); i++) {
        currentSampleFeatures[i] = ((currentSampleFeatures[i]*mergeCount) + features[i])/(mergeCount+1);
    }
    mergeCount++;
}

void VoiceSample::merge(const VoiceSample& voiceSample) {
    merge(voiceSample.currentSampleFeatures);
}

std::string VoiceSample::getFeaturesAsString() const {
    std::ostringstream output;
    if(!currentSampleFeatures.empty()) {
        std::copy(currentSampleFeatures.begin(), currentSampleFeatures.end()-1, std::ostream_iterator<double>(output, ", "));
        output << currentSampleFeatures.back();
    }
    return output.str();
}

std::vector<double> VoiceSample::getFeatures() const {
    return currentSampleFeatures;
}

}
