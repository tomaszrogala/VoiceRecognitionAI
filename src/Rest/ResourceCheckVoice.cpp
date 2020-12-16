//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceCheckVoice.h"

#include <iostream>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/JSON/Object.h>

#include "RestUtils.h"
#include "RecognitionStarter.h"
#include "FileManager.h"
#include "Logger.h"

using namespace Utils;

namespace Rest {

ResourceCheckVoice::ResourceCheckVoice() : ResourceTemplate() {}

void ResourceCheckVoice::handlePost(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    Logger::debug("Processing post request.");

    response.set("Content-Type", "application/json");
    response.set("RequestId", RestUtils::generateRequestId());

    FileManager fileManager;
    auto audioFilePath = fileManager.generateTemporaryPathToFile();
    fileManager.writeStreamToFile(request.stream(), audioFilePath);

    Core::RecognitionResult recognitionResult = Core::RecognitionStarter::getInstance().identify(audioFilePath);

    Poco::JSON::Object jsonObject;
    jsonObject.set("probability", recognitionResult.getProbability());
    jsonObject.set("name", recognitionResult.getIdentifier());

    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream &result = response.send();
    jsonObject.stringify(result);
    result.flush();
    fileManager.removeFile(audioFilePath);
    Logger::debug("Processing done.");
}

}
