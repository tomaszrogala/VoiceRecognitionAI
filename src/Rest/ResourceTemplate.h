//
// Created by Dawid Walenciak on 29/09/2020.
//

#ifndef VOICERECOGNITIONAI_RESOURCETEMPLATE_H
#define VOICERECOGNITIONAI_RESOURCETEMPLATE_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/URI.h>

namespace Rest {

class ResourceTemplate : public Poco::Net::HTTPRequestHandler {
public:
    ResourceTemplate();
    ~ResourceTemplate() override = default;

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;

protected:
    virtual void handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    virtual void handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    virtual void handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    virtual void handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    virtual void handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);
    virtual bool checkSupportedMethodsType(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    std::string baseUrl;
    std::string requestURI;
    std::string requestHost;
    Poco::URI::QueryParameters queryStringParameters;
};

}

#endif //VOICERECOGNITIONAI_RESOURCETEMPLATE_H
