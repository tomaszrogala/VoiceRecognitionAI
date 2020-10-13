//
// Created by Dawid Walenciak on 13/10/2020.
//

#ifndef VOICERECOGNITIONAI_RESTUTILS_H
#define VOICERECOGNITIONAI_RESTUTILS_H

#include <string>

namespace Rest {

class RestUtils {
public:
    RestUtils() = delete;
    ~RestUtils() = delete;

    static std::string generateRequestId();
private:

};

}

#endif //VOICERECOGNITIONAI_RESTUTILS_H
