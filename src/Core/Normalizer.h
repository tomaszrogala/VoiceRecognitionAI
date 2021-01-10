//
// Created by Dawid Walenciak on 08/01/2021.
//

#ifndef VOICERECOGNITIONAI_NORMALIZER_H
#define VOICERECOGNITIONAI_NORMALIZER_H

#include <vector>

namespace Core {

class Normalizer {
public:
    Normalizer() = delete;
    Normalizer(const Normalizer& normalizer) = delete;

    static void normalize(std::vector<double>& samples);
};

}

#endif //VOICERECOGNITIONAI_NORMALIZER_H
