//
// Created by Dawid Walenciak on 29/09/2020.
//

#include "Rest/Server.h"
#include "Rest/RouteManager.h"

int main(int argc, char** argv) {
    Rest::Server server;
    server.setRouteManager(new Rest::RouteManager());
    return server.run(argc, argv);
}
