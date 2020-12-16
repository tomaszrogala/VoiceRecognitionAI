//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "Server.h"

#include <iostream>
#include <utility>

#include <Poco/Util/HelpFormatter.h>
#include <Poco/Net/HTTPServer.h>

#include "Logger.h"

using namespace Utils;

namespace Rest {

Server::Server() :
helpRequested(false),
portOptionSet(false),
configOptionSet(false),
port(8081),
endpoint("localhost"),
routeManagerInstance() {}

Server::~Server() = default;

void Server::setPort(unsigned short portNumber) {
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
        Logger::debug("Setting up server params.");

        auto *httpServerParams = new Poco::Net::HTTPServerParams();

        Logger::info("Starting REST Server...");

        Poco::Net::HTTPServer httpServer(routeManagerInstance, Poco::Net::ServerSocket(port), httpServerParams);

        Logger::info("Voice Recognition AI Service started!");
        Logger::debug("Host data: " + endpoint + ":" + std::to_string(port));

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
