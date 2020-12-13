//
// Created by Dawid Walenciak on 08/12/2020.
//

#ifndef VOICERECOGNITIONAI_RECOGNITIONRESULT_H
#define VOICERECOGNITIONAI_RECOGNITIONRESULT_H

#include <string>

namespace Core {

class RecognitionResult {
public:
    RecognitionResult(const std::string& identifier, int probability, double distance);

    std::string getIdentifier() const;
    int getProbability() const;
    double getDistance() const;

private:
    std::string identifier;
    int probability;
    double distance;
};

inline RecognitionResult::RecognitionResult(const std::string& identifier, int probability, double distance) {
    this->identifier = identifier;
    this->probability = probability;
    this->distance = distance;
}

inline std::string RecognitionResult::getIdentifier() const {
    return identifier;
}

inline int RecognitionResult::getProbability() const {
    return probability;
}

inline double RecognitionResult::getDistance() const {
    return distance;
}

}

#endif //VOICERECOGNITIONAI_RECOGNITIONRESULT_H
