//
// Created by Dawid Walenciak on 09/01/2021.
//

#include "LinearPredictiveCoding.h"

#include "Logger.h"

using namespace Utils;

namespace Core {

LinearPredictiveCoding::LinearPredictiveCoding(int windowSize, int poles) : windowSize(windowSize), poles(poles) {
    output.resize(poles);
    error.resize(poles);
    k.resize(poles);
    matrix.resize(poles);
    for(auto& elem : matrix) {
        elem.resize(poles);
    }
}

std::vector<std::vector<double>> LinearPredictiveCoding::applyLinearPredictiveCoding(std::vector<double>& window) {
    if(windowSize != window.size()) {
        Logger::error("Given window length was not equal to the one provided in constructor : ["
        + std::to_string(window.size()) + "] != [" + std::to_string(windowSize) + "]");
        return std::vector<std::vector<double>>();
    }

    std::fill(k.begin(), k.end(), 0.0);
    std::fill(output.begin(), output.end(), 0.0);
    std::fill(error.begin(), error.end(), 0.0);
    for(auto& elem : matrix) {
        std::fill(elem.begin(), elem.end(), 0.0);
    }

    std::vector<double> autoCorrelations;
    autoCorrelations.resize(poles);
    for(int i = 0; i < poles; i++) {
        autoCorrelations[i] = autoCorrelate(window, i);
    }

    error[0] = autoCorrelations[0];

    for (int m = 1; m < poles; m++) {
        double tmp = autoCorrelations[m];
        for (int i = 1; i < m; i++) {
            tmp -= matrix[m - 1][i] * autoCorrelations[m - i];
        }
        k[m] = tmp / error[m - 1];

        for (int i = 0; i < m; i++) {
            matrix[m][i] = matrix[m - 1][i] - k[m] * matrix[m - 1][m - i];
        }
        matrix[m][m] = k[m];
        error[m] = (1 - (k[m] * k[m])) * error[m - 1];
    }

    for (int i = 0; i < poles; i++) {
        if (matrix[poles - 1][i] == 0.0) {
            output[i] = 0.0;
        } else {
            output[i] = matrix[poles - 1][i];
        }
    }

    return { output, error };
}

double LinearPredictiveCoding::autoCorrelate(std::vector<double>& buffer, int lag) {
    if(lag > -1 && lag < buffer.size()) {
        double result = 0.0;
        for (int i = lag; i < buffer.size(); i++) {
            result += buffer[i] * buffer[i - lag];
        }
        return result;
    } else {
        Logger::error("Lag parameter range is : -1 < lag < buffer size. Received [" + std::to_string(lag)
        + "] for buffer size of [" + std::to_string(buffer.size()) + "]");
        return -1.0;
    }
}

}
