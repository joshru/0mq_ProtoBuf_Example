//
// Created by joshru on 4/9/16.
//
#include "zmq.hpp"
#include "message.pb.h"
#include <string>
#include <iostream>

int main() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::Person person;
    person.set_id(1234);
    person.set_name("Josh");
    person.set_email("joshru@uw.edu");
    tutorial::Person::PhoneNumber* phone_number = person.add_phone();
    phone_number->set_number("2537406102");
    phone_number->set_type(tutorial::Person::MOBILE);
    phone_number = person.add_phone();
    phone_number->set_number("2538910713");
    phone_number->set_type(tutorial::Person::HOME);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PAIR);

    std::cout << "Connecting to server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    std::string msg_str;
    person.SerializeToString(&msg_str);

    zmq::message_t request(msg_str.size());
    memcpy((void *) request.data(), msg_str.c_str(), msg_str.size());
    std::cout << "Sending Person data..." << std::endl;
    socket.send(request);


    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
