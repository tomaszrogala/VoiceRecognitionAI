//
// Created by Dawid Walenciak on 08/01/2021.
//

#include "LpcExtractor.h"
#include "LinearPredictiveCoding.h"

#include <cmath>
#include <algorithm>

namespace Core {

std::vector<double> LpcExtractor::extractFeatures(std::vector<double>& samples, float sampleRate) {
    int windowSize = getWindowSize(sampleRate);
    std::vector<double> factors = getPrecomputedFactors(windowSize);

    std::vector<double> voiceFeatures;
    voiceFeatures.resize(POLES_NUMBER);
    std::vector<double> audioWindow;
    audioWindow.resize(windowSize);

    int counter = 0;
    int halfWindowLength = windowSize / 2;

    for (int i = 0; (i + windowSize) <= samples.size(); i += halfWindowLength) {

        std::copy(&samples[i], &samples[i + windowSize], &audioWindow[0]);

        for (int j = 0; j < audioWindow.size(); j++) {
            audioWindow[j] *= factors[j];
        }

        LinearPredictiveCoding lpc(windowSize, POLES_NUMBER);
        std::vector<double> lpcCoeffs = lpc.applyLinearPredictiveCoding(audioWindow)[0];

        for (int j = 0; j < POLES_NUMBER; j++) {
            voiceFeatures[j] += lpcCoeffs[j];
        }
        counter++;
    }

    if (counter > 1) {
        for (int i = 0; i < POLES_NUMBER; i++) {
            voiceFeatures[i] /= counter;
        }
    }
    return voiceFeatures;
}

int LpcExtractor::getWindowSize(float sampleRate) {
    bool done = false;
    int pow = 8; // 8 bytes == 1ms at 8000 Hz
    float previousMillis = 0.0f;

    while(!done) {
        float millis = 1000 / sampleRate * static_cast<float>(pow);
        if(millis < TARGET_WINDOW_LENGTH_IN_MILLIS) {
            previousMillis = millis;
            pow *= 2;
        } else {
            // closest value to target wins
            if(std::abs(static_cast<int>(TARGET_WINDOW_LENGTH_IN_MILLIS - millis)) > TARGET_WINDOW_LENGTH_IN_MILLIS - previousMillis) {
                pow /= 2; // previousMillis was closer
            }
            done = true;
        }
    }
    return pow;
}

std::vector<double> LpcExtractor::getPrecomputedFactors(int windowSize) {
    std::vector<double> factors;
    factors.resize(windowSize);
    int sizeMinusOne = windowSize - 1;
    for(int i = 0; i < windowSize; i++) {
        factors[i] = 0.54 - (0.46 * std::cos((TWO_PI * i) / sizeMinusOne));
    }
    return factors;
}

}
