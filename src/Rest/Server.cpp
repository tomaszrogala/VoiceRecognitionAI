//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "Server.h"

#include <iostream>
#include <utility>

#include <Poco/Util/HelpFormatter.h>
#include <Poco/Net/HTTPServer.h>

namespace Rest {

Server::Server() :
helpRequested(false),
portOptionSet(false),
configOptionSet(false),
port(8081),
endpoint("localhost"),
routeManagerInstance() {}

Server::~Server() = default;

void Server::setPort(int portNumber) {
    port = portNumber;
}

void Server::setRouteManager(Poco::Net::HTTPRequestHandlerFactory* routeManager) {
    routeManagerInstance = routeManager;
}

void Server::defineOptions(Poco::Util::OptionSet& options) {
    ServerApplication::defineOptions(options);

    options.addOption(
            Poco::Util::Option("help", "h", "display help information about server")
                    .required(false)
                    .repeatable(false)
                    .callback(Poco::Util::OptionCallback<Server>(this, &Server::handleHelp))
    );

    options.addOption(
            Poco::Util::Option("port", "p", "set port for server")
                    .required(false)
                    .repeatable(false)
                    .argument("value")
                    .callback(Poco::Util::OptionCallback<Server>(this, &Server::handleSetPort))
    );

    options.addOption(
            Poco::Util::Option("config", "c", "set path to config file")
                    .required(false)
                    .repeatable(false)
                    .argument("value")
                    .callback(Poco::Util::OptionCallback<Server>(this, &Server::handleSetConfig))
    );
}

void Server::initialize(Poco::Util::Application& self) {
    Application::initialize(self);
}

void Server::uninitialize() {
    Application::uninitialize();
}

int Server::main(const std::vector<std::string>& args) {
    if(!helpRequested) {
        // TODO: create some logger instead of using standard output
        std::cout<<"Setting up server params."<<std::endl;

        auto *httpServerParams = new Poco::Net::HTTPServerParams();

        std::cout<<"Starting REST Server..."<<std::endl;

        Poco::Net::HTTPServer httpServer(routeManagerInstance, Poco::Net::ServerSocket(port), httpServerParams);

        std::cout<<"Voice Recognition AI Service started!"<<std::endl;
        std::cout<<"Bind to endpoint: "<<endpoint<<":"<<port<<std::endl;

        httpServer.start();
        waitForTerminationRequest();
        httpServer.stop();
    }
    return Poco::Util::Application::EXIT_OK;
}

void Server::handleHelp(const std::string& key, const std::string& value) {
    helpRequested = true;
    displayHelp();
    stopOptionsProcessing();
}

void Server::handleSetPort(const std::string& key, const std::string& value) {
    // TODO
}

void Server::handleSetConfig(const std::string& key, const std::string& value) {
    // TODO
}

void Server::displayHelp() {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("VoiceRecognitionAI");
    helpFormatter.format(std::cout);
}

}
