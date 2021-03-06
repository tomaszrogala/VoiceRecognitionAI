//
// Created by Dawid Walenciak on 13/12/2020.
//

#ifndef VOICERECOGNITIONAI_VOICESAMPLE_H
#define VOICERECOGNITIONAI_VOICESAMPLE_H

#include <vector>
#include <string>

namespace Core {

class VoiceSample {
public:
    static std::vector<double> extractFeaturesFromSampleFile(const std::string& filePath, float sampleRate);

    VoiceSample();
    VoiceSample(const std::string& pathToSampleFile, float sampleRate);
    explicit VoiceSample(std::vector<double> features);
    VoiceSample(const VoiceSample& voiceSample);

    double getDistance(const VoiceSample& voiceSample) const;
    void merge(const std::vector<double>& features);
    void merge(const VoiceSample& voiceSample);

    std::string getFeaturesAsString() const;
    std::vector<double> getFeatures() const;

private:
    std::vector<double> currentSampleFeatures;
    int mergeCount;

};

}

#endif //VOICERECOGNITIONAI_VOICESAMPLE_H
