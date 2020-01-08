//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_READFROMSOCKETTASK_H
#define BOOST_ECHO_CLIENT2_READFROMSOCKETTASK_H
#include <stdlib.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include <thread>
#include <mutex>

using namespace std;
class ReadFromSocketTask {    //will used by thread2
private:
    mutex &_mutex;
    ConnectionHandler &_connectionHandler;
    bool terminated;
public:
    ReadFromSocketTask(mutex& mutex,ConnectionHandler& connectionHandler);
    void run();
};
#endif //BOOST_ECHO_CLIENT2_READFROMSOCKETTASK_H