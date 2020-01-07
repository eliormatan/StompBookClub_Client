#include <stdlib.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include <thread>
#include "../include/StompMsgEncoderDecoder.h"
#include <mutex>
using namespace std;
class KeyboardTask{   //will used by thread1
private:
    mutex & _mutex;
    ConnectionHandler & _connectionHandler;
    bool  terminated;
    StompMsgEncoderDecoder encDec;
public:
    KeyboardTask(mutex& mutex,ConnectionHandler& connectionHandler,StompMsgEncoderDecoder encDec1) : _mutex(mutex),_connectionHandler(connectionHandler),terminated(false),encDec(encDec1) {}
    void run(){
        while(!terminated){
            const short bufsize = 1024;
            char buf[bufsize];
            std::cin.getline(buf, bufsize);
            std::string line(buf);
            string frameToSend = encDec.encode(line);
//            int len=frameToSend.length();
            if (!_connectionHandler.sendLine(frameToSend)) {
//                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
        }
    }
};
