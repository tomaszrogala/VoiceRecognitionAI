//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceCheckVoice.h"

#include <iostream>
#include <sstream>

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>

namespace Rest {

ResourceCheckVoice::ResourceCheckVoice() : ResourceTemplate() {}

void ResourceCheckVoice::handlePost(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    std::cout<<"Processing post request."<<std::endl;
    // TODO: setup standard for request headers
    //response.set("Accept", request.get("Accept"));
    //response.set("Content-Type", request.get("Content-Type"));
    //response.set("RequestId", request.get("RequestId"));

    std::stringstream buffer;
    buffer << request.stream().rdbuf();

    std::cout<<"Request body: \n"<<buffer.str()<<std::endl;

    // TODO: get wav file and check if can recognize voice
    response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK);

    std::ostream &result = response.send();
    // TODO: as msg return message with result
    //result << msg;
    result.flush();
}

}
