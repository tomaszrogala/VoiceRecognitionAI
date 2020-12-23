//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "ResourceTemplate.h"
#include "ResponseMessage.h"

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
        response.setStatus(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
        std::ostream &errorStream = response.send();
        errorStream << ResponseMessage().status(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED).message("Unsupported method type.").build();
        errorStream.flush();
    }
}

void ResourceTemplate::handleGet(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse& response) {
    returnNotImplemented(response);
}

void ResourceTemplate::handlePost(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse& response) {
    returnNotImplemented(response);
}

void ResourceTemplate::handlePut(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse& response) {
    returnNotImplemented(response);
}

void ResourceTemplate::handleDelete(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse& response) {
    returnNotImplemented(response);
}

void ResourceTemplate::handleOptions(Poco::Net::HTTPServerRequest&, Poco::Net::HTTPServerResponse& response) {
    returnNotImplemented(response);
}

bool ResourceTemplate::checkSupportedMethodsType(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    return request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE ||
           request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS;
}

void ResourceTemplate::returnNotImplemented(Poco::Net::HTTPServerResponse& response) {
    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream << ResponseMessage().status(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED).message("Method currently not implemented.").build();
    errorStream.flush();
}

}
