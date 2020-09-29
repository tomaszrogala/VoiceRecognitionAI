//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceNotFound.h"

#include <Poco/Net/HTTPServerResponse.h>

namespace Rest {

void ResourceNotFound::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    //ResponseRequest::changeStatusReason(404, response);
    //Exception exception(404, Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND, "This route does not exist.");

    std::ostream &errorStream = response.send();
    //errorStream << exception.buildJson();
    errorStream.flush();
}

}
