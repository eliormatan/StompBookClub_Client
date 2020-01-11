cmake_minimum_required(VERSION 3.15)
project(Boost_Echo_Client2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Boost_Echo_Client2 src/connectionHandler.cpp include/connectionHandler.h src/ReadFromSocketTask.cpp src/User.cpp include/User.h src/Book.cpp include/Book.h src/ClientMain.cpp src/SplitThings.cpp include/SplitThings.h src/KeyBoardTask.cpp include/KeyBoardTask.h include/ReadFromSocketTask.h include/StompMsgEncoderDecoder.h src/StompMsgEncoderDecoder.cpp src/RequestBorrow.cpp include/RequestBorrow.h src/RequestSubUnsub.cpp include/RequestSubUnsub.h)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 1.65.1 REQUIRED COMPONENTS
        date_time filesystem iostreams system)
find_package(Threads)
target_link_libraries(Boost_Echo_Client2 Boost::date_time Boost::filesystem
        Boost::iostreams Boost::system)

