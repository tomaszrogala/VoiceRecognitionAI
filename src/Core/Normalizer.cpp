//
// Created by Dawid Walenciak on 08/01/2021.
//

#include "Normalizer.h"

#include <limits>
#include <cmath>

#include "Logger.h"

using namespace Utils;

namespace Core {

void Normalizer::normalize(std::vector<double>& samples) {
    double max = std::numeric_limits<double>::lowest();

    for (double sample : samples) {
        double abs = std::abs(sample);
        if (abs > max) {
            max = abs;
        }
    }
    if(max > 1.0) {
        Logger::error("Expected value for audio are in the range -1.0 <= v <= 1.0 ");
        return;
    }
    if (max < 5 * std::numeric_limits<float>::min()) { // ulp of 0.0 is extremely small ! i.e. as small as it can get
        return;
    }
    for (double& sample : samples) {
        sample /= max;
    }
}

}
