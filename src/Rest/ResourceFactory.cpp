//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceFactory.h"

#include "ResourceNotFound.h"
#include "ResourceTemplate.h"
#include "ResourceCheckVoice.h"

namespace Rest {

Poco::Net::HTTPRequestHandler *ResourceFactory::createResource(ResourceFactory::Type type) {
    switch (type) {
        case NOT_FOUND:
            return new ResourceNotFound();
        case TEMPLATE:
            return new ResourceTemplate();
        case CHECK_VOICE:
            return new ResourceCheckVoice();
        default:
            return new ResourceNotFound();
    }
}
}
