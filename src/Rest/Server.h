//
// Created by Dawid Walenciak on 29/09/2020.
//

#ifndef VOICERECOGNITIONAI_SERVER_H
#define VOICERECOGNITIONAI_SERVER_H

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

namespace Rest {

class Server : public Poco::Util::ServerApplication {
public:
    Server();
    ~Server() override;

    void setPort(int portNumber);
    void setRouteManager(Poco::Net::HTTPRequestHandlerFactory* routeManager);

protected:
    void defineOptions(Poco::Util::OptionSet& options) override;
    void initialize(Application& self) override;
    void uninitialize() override;
    int main(const std::vector<std::string>& args) override;

    void handleHelp(const std::string& key, const std::string& value);
    void handleSetPort(const std::string& key, const std::string& value);
    void handleSetConfig(const std::string& key, const std::string& value);
private:
    void displayHelp();

    bool helpRequested;
    bool portOptionSet;
    bool configOptionSet;

    int port;
    std::string endpoint;

    Poco::Net::HTTPRequestHandlerFactory* routeManagerInstance;
};

}

#endif //VOICERECOGNITIONAI_SERVER_H
