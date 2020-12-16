//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "RouteManager.h"

#include <Poco/Net/HTTPServerRequest.h>

#include "Logger.h"
#include "ResourceNotFound.h"
#include "ResourceCheckVoice.h"
#include "ResourceFactory.h"

using namespace Utils;

namespace Rest {

RouteManager::RouteManager() {
    Logger::debug("Preparing routes.");

    routeMap["/vc/check"] = ResourceFactory::CHECK_VOICE;

    Logger::debug("Routes added.");
}

Poco::Net::HTTPRequestHandler* RouteManager::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    Logger::info("Getting resource: " + request.getURI());
    return getResource(request.getURI());
}

Poco::Net::HTTPRequestHandler* RouteManager::getResource(const std::string& resource) {
    Poco::URI uri = Poco::URI(resource);
    auto routePosition = routeMap.find(uri.getPath());
    if(routePosition == routeMap.end()){
        return new ResourceNotFound();
    }

    return ResourceFactory::createResource(routePosition->second);
}

}
