cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Boost_Echo_Client2 src/connectionHandler.cpp include/connectionHandler.h src/echoClient.cpp src/KeyboardTask.cpp src/ReadFromSocketTask.cpp)

find_package(Boost 1.58.0 REQUIRED COMPONENTS system filesystem)
target_link_libraries(Boost_Echo_Client2 ${Boost_LIBRARIES})

