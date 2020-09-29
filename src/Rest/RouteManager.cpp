//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "RouteManager.h"

#include <iostream>

#include <Poco/Net/HTTPServerRequest.h>

#include "ResourceNotFound.h"
#include "ResourceCheckVoice.h"
#include "ResourceFactory.h"

namespace Rest {

RouteManager::RouteManager() {
    std::cout<<"Preparing routes."<<std::endl;

    routeMap["/vc/check"] = ResourceFactory::CHECK_VOICE;

    std::cout<<"Routes added."<<std::endl;
}

Poco::Net::HTTPRequestHandler* RouteManager::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    std::cout<<"Getting resource: "<<request.getURI()<<std::endl;
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
