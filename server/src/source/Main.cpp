#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <cstdlib>
#include <restbed>

#include "ServerLogger.hpp"

using namespace restbed;

constexpr ushort DEFAULTPORT = 5073;

std::string defaultAnswer = "Hello World";

void testHandler(const std::shared_ptr<Session> session)
{
    session->close(OK, defaultAnswer, { {"Content-Length", std::to_string(defaultAnswer.length())} });
}

int main(int argc, char** argv)
{
    // Set default parameters
    ushort port = DEFAULTPORT;

    // Parse arguments
    for(int i=1; i < argc; ++i)
    {
        if (!strcmp("--port", argv[i])) { port = atoi(argv[i]); }

        else { std::cout << "Unknown Parameter: " << argv[i] << std::endl; }
    }

    auto resource = std::make_shared<Resource>();
    resource->set_path("/resource");
    resource->set_method_handler("GET", testHandler);

    auto settings = std::make_shared<Settings>();
    settings->set_port(port);
    settings->set_bind_address("0.0.0.0");
    settings->set_default_header("Connection", "close");

    Service service;
    service.set_logger(std::make_shared<ServerLogger>());
    service.publish(resource);
    service.start(settings);

    return EXIT_SUCCESS;
}