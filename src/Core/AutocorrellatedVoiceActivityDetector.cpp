//
// Created by Dawid Walenciak on 08/01/2021.
//

#include "AutocorrellatedVoiceActivityDetector.h"

namespace Core {

void AutocorrellatedVoiceActivityDetector::removeSilence(std::vector<double>& samples, float sampleRate) {
    int milliInSample = static_cast<int>(sampleRate) / 1000;

    int minimumSilenceLength = MINIMUM_SILENCE_MILLIS * milliInSample;
    int minimumActivityLength = (MINIMUM_VOICE_MILLIS * static_cast<int>(sampleRate))/1000;
    std::vector<bool> result;
    result.resize(samples.size());

    if(samples.size() < minimumActivityLength) {
        return;
    }

    int windowsSize = WINDOW_MILLIS * milliInSample;
    std::vector<double> correlation;
    std::vector<double> window;
    correlation.resize(windowsSize);
    window.resize(windowsSize);

    for(int position = 0; position + windowsSize < samples.size(); position += windowsSize) {
        //window.insert(window.begin(), &samples[position], &samples[position+windowsSize]);
        std::copy(&samples[position], &samples[position + windowsSize], &window[0]);
        double mean = bruteForceAutocorrelation(window, correlation);
        std::fill(&result[position], &result[position + windowsSize], mean > threshold);
    }

    mergeSmallSilentAreas(result, minimumSilenceLength);

    int silenceCounter = mergeSmallActiveAreas(result, minimumActivityLength);

    if(silenceCounter > 0) {
        int fadeLength = FADE_MILLIS * milliInSample;
        initFadeFactors(fadeLength);
        std::vector<double> shortenedVoiceSample;
        shortenedVoiceSample.resize(samples.size() - silenceCounter);
        int copyCounter = 0;
        for (int i = 0; i < result.size(); i++) {
            if(result[i]) {
                int startIndex = i;
                int counter = 0;
                while (i < result.size() && result[i++]) {
                    counter++;
                }
                int endIndex = startIndex + counter;
                applyFadeInFadeOut(samples, fadeLength, startIndex, endIndex);
                //shortenedVoiceSample.insert(shortenedVoiceSample.end(), &samples[startIndex], &samples[startIndex+counter]);
                std::copy(&samples[startIndex], &samples[startIndex+counter], &shortenedVoiceSample[copyCounter]);
                copyCounter += counter;
            }
        }
        samples = shortenedVoiceSample;
        return;
    }
}

double AutocorrellatedVoiceActivityDetector::bruteForceAutocorrelation(std::vector<double>& samples, std::vector<double>& correlation) {
    std::fill(correlation.begin(), correlation.end(), 0);
    int n = samples.size();
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            correlation[j] += samples[i] * samples[(n + i - j) % n];
        }
    }
    double mean = 0.0;
    for(int i = 0; i < samples.size(); i++) {
        mean += correlation[i];
    }
    return mean / correlation.size();
}

void AutocorrellatedVoiceActivityDetector::mergeSmallSilentAreas(std::vector<bool>& result, int minimumSilenceLength) {
    bool active;
    int increment = 0;
    for(int i = 0; i < result.size(); i += increment) {
        active = result[i];
        increment = 1;
        while((i + increment < result.size()) && result[i + increment] == active) {
            increment++;
        }
        if(!active && increment < minimumSilenceLength) {
            // convert short silence to opposite
            std::fill(&result[i], &result[i + increment], !active);
        }
    }
}

int AutocorrellatedVoiceActivityDetector::mergeSmallActiveAreas(std::vector<bool>& result, int minimumActivityLength) {
    bool active;
    int increment = 0;
    int silenceCounter = 0;
    for(int i = 0; i < result.size(); i += increment) {
        active = result[i];
        increment = 1;
        while((i + increment < result.size()) && result[i + increment] == active) {
            increment++;
        }
        if(active && increment < minimumActivityLength) {
            // convert short activity to opposite
            std::fill(&result[i], &result[i + increment], !active);
            silenceCounter += increment;
        }
        if(!active) {
            silenceCounter += increment;
        }
    }
    return silenceCounter;
}

void AutocorrellatedVoiceActivityDetector::initFadeFactors(int fadeLength) {
    fadeInFactors.resize(fadeLength);
    fadeOutFactors.resize(fadeLength);
    for(int i = 0; i < fadeLength; i++) {
        fadeInFactors[i] = (1.0 / fadeLength) * i;
        fadeOutFactors[i] = 1.0 - fadeInFactors[i];
    }
}

void AutocorrellatedVoiceActivityDetector::applyFadeInFadeOut(std::vector<double>& samples, int fadeLength, int startIndex, int endIndex) {
    int fadeOutStart = endIndex - fadeLength;
    for(int i = 0; i < fadeLength; i++) {
        samples[startIndex + i] *= fadeInFactors[i];
        samples[fadeOutStart + i] *= fadeOutFactors[i];
    }
}

}