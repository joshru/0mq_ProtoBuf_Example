//
// Created by joshru on 4/9/16.
//

#include "zmq.hpp"
#include <string>
#include <iostream>
#include "message.pb.h"
#include <google/protobuf/text_format.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
    zmq::context_t context(1); //prepare our context and socket
    zmq::socket_t socket(context, ZMQ_PAIR);
    socket.bind("tcp://*:5555");

    while (true) {
        zmq::message_t request;
        socket.recv(&request); // wait for next request from client

        std::cout << "Received" << std::endl;
        tutorial::Person person;
        std::string msg_str(static_cast<char*>(request.data()), request.size());
        person.ParseFromString(msg_str);
        std::string text_str;
        google::protobuf::TextFormat::PrintToString(person, &text_str);
        std::cout << text_str << std::endl;
    }
    return 0;
}

#pragma clang diagnostic pop