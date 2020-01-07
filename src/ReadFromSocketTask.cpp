#include <stdlib.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include <thread>
#include <mutex>

using namespace std;
class ReadFromSocketTask{    //will used by thread2
private:
    mutex & _mutex;
    ConnectionHandler & _connectionHandler;
public:
    ReadFromSocketTask(mutex& mutex,ConnectionHandler& connectionHandler) : _mutex(mutex),_connectionHandler(connectionHandler) {}
    void run(){  //todo

    }
};