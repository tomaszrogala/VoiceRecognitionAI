//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceCheckVoice.h"

#include <iostream>
#include <sstream>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Object.h>

#include "RestUtils.h"
#include "RecognitionStarter.h"

namespace Rest {

ResourceCheckVoice::ResourceCheckVoice() : ResourceTemplate() {}

void ResourceCheckVoice::handlePost(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    std::cout<<"Processing post request."<<std::endl;

    response.set("Content-Type", "application/json");
    response.set("RequestId", RestUtils::generateRequestId());

    std::stringstream buffer;
    buffer << request.stream().rdbuf();

    // TODO: get audio file, save in path and check if can recognize voice
    Core::RecognitionResult recognitionResult = Core::RecognitionStarter::getInstance().identify("");

    Poco::JSON::Object jsonObject;
    jsonObject.set("status", recognitionResult.getProbability());
    jsonObject.set("name", recognitionResult.getIdentifier());

    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream &result = response.send();
    jsonObject.stringify(result);
    result.flush();
}

}
