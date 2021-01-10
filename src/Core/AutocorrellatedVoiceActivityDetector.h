//
// Created by Dawid Walenciak on 08/01/2021.
//

#ifndef VOICERECOGNITIONAI_AUTOCORRELLATEDVOICEACTIVITYDETECTOR_H
#define VOICERECOGNITIONAI_AUTOCORRELLATEDVOICEACTIVITYDETECTOR_H

#include <vector>

namespace Core {

class AutocorrellatedVoiceActivityDetector {
public:
    AutocorrellatedVoiceActivityDetector() = default;
    AutocorrellatedVoiceActivityDetector(const AutocorrellatedVoiceActivityDetector& activityDetector) = delete;

    void removeSilence(std::vector<double>& samples, float sampleRate);

private:
    double bruteForceAutocorrelation(std::vector<double>& samples, std::vector<double>& correlation);
    void mergeSmallSilentAreas(std::vector<bool>& result, int minimumSilenceLength);
    int mergeSmallActiveAreas(std::vector<bool>& result, int minimumActivityLength);
    void initFadeFactors(int fadeLength);
    void applyFadeInFadeOut(std::vector<double>& samples, int fadeLength, int startIndex, int endIndex);

    static const int WINDOW_MILLIS = 1;
    static const int FADE_MILLIS = 1;
    static const int MINIMUM_SILENCE_MILLIS = 4;
    static const int MINIMUM_VOICE_MILLIS = 200;

    double const threshold = 0.0001;
    std::vector<double> fadeInFactors;
    std::vector<double> fadeOutFactors;
};

}

#endif //VOICERECOGNITIONAI_AUTOCORRELLATEDVOICEACTIVITYDETECTOR_H
