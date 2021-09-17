#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <cstdlib>
#include <restbed>
#include <sstream>

#include "ServerLogger.hpp"

using namespace restbed;

constexpr ushort DEFAULTPORT = 5073;

std::string defaultAnswer = "Hello World";

void resourceHandler(const std::shared_ptr<Session> session)
{
    session->close(OK, defaultAnswer, { {"Content-Length", std::to_string(defaultAnswer.length())} });
}

void defaultHandler(const std::shared_ptr<Session> session)
{
    std::stringstream ss;

    ss << "ID :" << session->get_id() << std::endl;
    ss << "Origen: " << session->get_origin() << std::endl;

    string out = ss.str();

    session->close(OK, out, { { "Content-Length", std::to_string(out.length()) } });
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
    resource->set_method_handler("GET", resourceHandler);

    auto resource1 = std::make_shared<Resource>();
    resource1->set_path("/");
    resource1->set_method_handler("GET", defaultHandler);

    auto settings = std::make_shared<Settings>();
    settings->set_port(port);
    settings->set_bind_address("0.0.0.0");
    settings->set_default_header("Connection", "close");

    Service service;
    service.set_logger(std::make_shared<ServerLogger>());
    service.publish(resource);
    service.publish(resource1);
    service.start(settings);

    return EXIT_SUCCESS;
}