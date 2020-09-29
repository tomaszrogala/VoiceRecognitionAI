//
// Created by Dawid Walenciak on 29/09/2020.
//

#ifndef VOICERECOGNITIONAI_RESOURCECHECKVOICE_H
#define VOICERECOGNITIONAI_RESOURCECHECKVOICE_H

#include "ResourceTemplate.h"

namespace Rest {

class ResourceCheckVoice : public ResourceTemplate {
public:
    ResourceCheckVoice();
protected:
    void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) override;
};

}

#endif //VOICERECOGNITIONAI_RESOURCECHECKVOICE_H
