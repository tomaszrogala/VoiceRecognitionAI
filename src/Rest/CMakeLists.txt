
add_library(Rest STATIC
        Server.cpp
        Server.h
        RouteManager.cpp
        RouteManager.h
        ResourceTemplate.cpp
        ResourceTemplate.h
        ResourceNotFound.cpp
        ResourceNotFound.h
        ResourceCheckVoice.cpp
        ResourceCheckVoice.h
        ResourceFactory.cpp
        ResourceFactory.h)

target_include_directories(Rest PUBLIC
        ${POCO_INCLUDE_DIR})
