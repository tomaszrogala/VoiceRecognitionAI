//
// Created by Dawid Walenciak on 29/09/2020.
//

#ifndef VOICERECOGNITIONAI_RESOURCENOTFOUND_H
#define VOICERECOGNITIONAI_RESOURCENOTFOUND_H

#include <Poco/Net/HTTPRequestHandler.h>

namespace Rest {

class ResourceNotFound : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

}

#endif //VOICERECOGNITIONAI_RESOURCENOTFOUND_H
