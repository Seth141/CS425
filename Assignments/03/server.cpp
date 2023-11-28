#include <iostream>
#include <thread>  // Include for std::thread
#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

const uint16_t DefaultPort = 8143; // Update this variable with your assigned port value

int main(int argc, char* argv[]) {
    uint16_t port = argc > 1 ? std::stol(argv[1]) : DefaultPort;
    Connection connection(port);

    while (connection) {
        auto clientSocket = connection.accept();
        std::thread([clientSocket]() {
            Session session(clientSocket);
            std::string msg;
            session >> msg;
            HTTPRequest request(msg);
            const char* root = "/home/faculty/shreiner/public_html/03";
            HTTPResponse response(request, root);
            session << response;
        }).detach();
    }
    return 0;
}