cmake_minimum_required(VERSION 3.5)
project(0mq___ProtoBuf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lzmq -lprotobuf")

set(SOURCE_FILES server.cpp client.cpp)

add_library(message message.pb.cc)
add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client message)
target_link_libraries(server message)
#add_executable(0mq___ProtoBuf ${SOURCE_FILES})