#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <restbed>

#include "ServerLogger.hpp"

using namespace restbed;

std::string defaultAnswer = "Hello World";

void testHandler(const std::shared_ptr<Session> session)
{
    session->close(OK, defaultAnswer, { {"Content-Length", std::to_string(defaultAnswer.length())} });
}

int main(int argc, char** argv)
{
    auto resource = std::make_shared<Resource>();
    resource->set_path("/resource");
    resource->set_method_handler("GET", testHandler);

    auto settings = std::make_shared<Settings>();
    settings->set_port(5073);
    settings->set_bind_address("0.0.0.0");
    settings->set_default_header("Connection", "close");

    Service service;
    service.set_logger(std::make_shared<ServerLogger>());
    service.publish(resource);
    service.start(settings);

    return EXIT_SUCCESS;
}