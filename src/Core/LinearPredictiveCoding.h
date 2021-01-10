//
// Created by Dawid Walenciak on 09/01/2021.
//

#ifndef VOICERECOGNITIONAI_LINEARPREDICTIVECODING_H
#define VOICERECOGNITIONAI_LINEARPREDICTIVECODING_H

#include <vector>

namespace Core {

class LinearPredictiveCoding {
public:
    LinearPredictiveCoding() = delete;
    LinearPredictiveCoding(int windowSize, int poles);

    std::vector<std::vector<double>> applyLinearPredictiveCoding(std::vector<double>& window);

private:
    /**
     * Computes discrete auto correlation at lag j algorithm
     * @see <a href="http://en.wikipedia.org/wiki/Autocorrelation">Autocorrelation</a>
     *
     * @param buffer, the buffered signal
     * @param lag, in the range -1 &lt; lag &lt; voiceSample size
     * @return the computed auto correlation result
     */
    double autoCorrelate(std::vector<double>& buffer, int lag);

    int windowSize;
    int poles;
    std::vector<double> output;
    std::vector<double> error;
    std::vector<double> k;
    std::vector<std::vector<double>> matrix;

};

}

#endif //VOICERECOGNITIONAI_LINEARPREDICTIVECODING_H
