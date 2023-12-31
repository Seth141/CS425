#include <iostream>
#include <thread>  
#include "Connection.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"

const uint16_t DefaultPort = 8143; // My new port value
const size_t BufferSize = 1000;  // May alter this size when done

//
//Still working on this and testing: 
//
/*
template<typename T, size_t Size>
class RingBuffer {
public:
    bool pushing(const T& item) {
        auto current_tail = tail.load(std::memory_order_relaxed);
        auto next_tail = increment(current_tail);
        if (next_tail != head.load(std::memory_order_acquire)) {
            buffer[current_tail] = item;
            tail.store(next_tail, std::memory_order_release);
            return true;
        }
        return false;  // Buffer is full
    }
*/


/*
bool popping(T& item) {
        auto current_head = head.load(std::memory_order_relaxed);
        if (current_head == tail.load(std::memory_order_acquire)) {
            return false;  // Buffer is empty
        }

        item = buffer[current_head];
        head.store(increment(current_head), std::memory_order_release);
        return true;
    }
*/

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
