#include <stdlib.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include <thread>
#include <mutex>
using namespace std;
class KeyboardTask{   //will used by thread1
private:
    mutex & _mutex;
    ConnectionHandler & _connectionHandler;
public:
    KeyboardTask(mutex& mutex,ConnectionHandler& connectionHandler) : _mutex(mutex),_connectionHandler(connectionHandler) {}
    void run(){  //todo
        while(!logoutCommand) {
            if (command == "login")
        }
    }
};
