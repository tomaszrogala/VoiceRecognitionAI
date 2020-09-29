//
// Created by Dawid Walenciak on 29/09/2020.
//

#ifndef VOICERECOGNITIONAI_ROUTEMANAGER_H
#define VOICERECOGNITIONAI_ROUTEMANAGER_H

#include <map>

#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include "ResourceTemplate.h"
#include "ResourceFactory.h"

namespace Rest {

class RouteManager : public Poco::Net::HTTPRequestHandlerFactory {
public:
    RouteManager();

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;

private:
    Poco::Net::HTTPRequestHandler* getResource(const std::string& resource);

    std::map<std::string, ResourceFactory::Type> routeMap;

};

}

#endif //VOICERECOGNITIONAI_ROUTEMANAGER_H
