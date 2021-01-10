//
// Created by Dawid Walenciak on 13/12/2020.
//

#include "VoiceSample.h"

#include <string>
#include <sstream>
#include <utility>
#include <iterator>
#include <cmath>
#include <AudioFile.h>

#include "Logger.h"
#include "AutocorrellatedVoiceActivityDetector.h"
#include "Normalizer.h"
#include "LpcExtractor.h"

using namespace Utils;

namespace Core {

// TODO: implement extraction of features from "extractFeatures" from Recognito.java
std::vector<double> VoiceSample::extractFeaturesFromSampleFile(const std::string& filePath, float sampleRate) {
    /// Open file
    AudioFile<double> audioFile(filePath);
    audioFile.printSummary();

    /// Count sample rate
    float diff = std::abs(audioFile.getSampleRate() - sampleRate);
    if(diff > 5 * std::numeric_limits<float>::min()) {
        Logger::error("Sample rate of this file is different than configured. Sample rate: " + std::to_string(audioFile.getSampleRate()));
        return std::vector<double>();
    }

    /// Convert to signed, big endian, 1 channel, 16Bit, 16000 HZ sample
    if(audioFile.getBitDepth() != 16 && audioFile.getSampleRate() != 16000) {
        Logger::error("Audio file cannot be parsed!");
        return std::vector<double>();
    }
    if(audioFile.isStereo()) {
        Logger::error("Currently only MONO audio files are supported.");
        return std::vector<double>();

        // TODO in future
        /*AudioFile<double>::AudioBuffer buffer;
        buffer.resize(1);
        buffer.front().resize(audioFile.samples.front().size());
        for (auto& sample : buffer.front()) {
            sample =
        }*/
    }

    /// Exctract features
    std::vector<double> features = audioFile.samples.front();
    // AutocorrellatedVoiceActivityDetector
    AutocorrellatedVoiceActivityDetector voiceActivityDetector;
    voiceActivityDetector.removeSilence(features, audioFile.getSampleRate());
    // Normalizer
    Normalizer::normalize(features);
    // LpcFeaturesExtractor
    LpcExtractor lpcExtractor;

    return lpcExtractor.extractFeatures(features, sampleRate);
}

VoiceSample::VoiceSample() : currentSampleFeatures(), mergeCount(0) {}

VoiceSample::VoiceSample(const std::string& pathToSampleFile, float sampleRate)
: VoiceSample(extractFeaturesFromSampleFile(pathToSampleFile, sampleRate)) {}

VoiceSample::VoiceSample(std::vector<double> features)
: currentSampleFeatures(std::move(features)), mergeCount(1) {}

VoiceSample::VoiceSample(const VoiceSample& voiceSample)
: currentSampleFeatures(voiceSample.currentSampleFeatures), mergeCount(1) {}

// TODO
double VoiceSample::getDistance(const VoiceSample& voiceSample) const {
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
