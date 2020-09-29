//
// Created by Dawid Walenciak on 29/09/2020.
//

#ifndef VOICERECOGNITIONAI_RESOURCEFACTORY_H
#define VOICERECOGNITIONAI_RESOURCEFACTORY_H

#include <Poco/Net/HTTPRequestHandler.h>

namespace Rest {

class ResourceFactory {
public:
    enum Type {
        NOT_FOUND,
        TEMPLATE,
        CHECK_VOICE
    };

    static Poco::Net::HTTPRequestHandler* createResource(Type type);

    ResourceFactory() = delete;
    ~ResourceFactory() = delete;
};

}

#endif //VOICERECOGNITIONAI_RESOURCEFACTORY_H
