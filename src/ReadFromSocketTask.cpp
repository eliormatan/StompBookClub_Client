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
    bool terminated;
public:
    ReadFromSocketTask(mutex& mutex,ConnectionHandler& connectionHandler) : _mutex(mutex),_connectionHandler(connectionHandler),terminated(false) {}
    void run(){  //todo
        while(!terminated) {
            std::string answer;
            if (!_connectionHandler.getLine(answer)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            int len = answer.length();
            answer.resize(len - 1);
            std::cout << answer << std::endl;
            if (answer == "bye") {
                std::cout << "Exiting...\n" << std::endl;
                break;
            }
        }
    }
};