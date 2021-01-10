//
// Created by Dawid Walenciak on 08/01/2021.
//

#ifndef VOICERECOGNITIONAI_LPCEXTRACTOR_H
#define VOICERECOGNITIONAI_LPCEXTRACTOR_H

#include <vector>

namespace Core {

class LpcExtractor {
public:
    LpcExtractor() = default;

    std::vector<double> extractFeatures(std::vector<double>& samples, float sampleRate);

private:
    int getWindowSize(float sampleRate);
    std::vector<double> getPrecomputedFactors(int windowSize);

    constexpr static float TARGET_WINDOW_LENGTH_IN_MILLIS = 24;
    constexpr static double TWO_PI = 2 * 3.14159265358979323846;
    static const int POLES_NUMBER = 20;

};

}

#endif //VOICERECOGNITIONAI_LPCEXTRACTOR_H
