//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceTemplate.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

namespace Rest {

ResourceTemplate::ResourceTemplate() : baseUrl(), requestURI(), requestHost() {}

void ResourceTemplate::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    if(checkSupportedMethodsType(request, response)){
        Poco::URI uri = Poco::URI(request.getURI());

        requestURI = request.getURI();
        requestHost = request.getHost();
        baseUrl = "https://" + requestHost + requestURI;
        queryStringParameters = uri.getQueryParameters();

        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
            this->handleGet(request, response);
        }
        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT) {
            this->handlePut(request, response);
        }
        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
            this->handlePost(request, response);
        }
        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE) {
            this->handleDelete(request, response);
        }
        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
            this->handleOptions(request, response);
        }
    }
    else{
        // TODO: prepare response message
        //ResponseRequest::changeStatusReason(405, response);
        std::ostream &errorStream = response.send();
        //errorStream << StatusMessage(405, Poco::Net::HTTPResponse::HTTP_REASON_VERSION_NOT_SUPPORTED, "Unsupported method type").build();
        errorStream.flush();
    }
}

void ResourceTemplate::handleGet(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    // TODO
}

void ResourceTemplate::handlePost(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    // TODO
}

void ResourceTemplate::handlePut(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    // TODO
}

void ResourceTemplate::handleDelete(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    // TODO
}

void ResourceTemplate::handleOptions(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    // TODO
}

bool ResourceTemplate::checkSupportedMethodsType(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    return request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS;
}
}
