//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/KeyBoardTask.h"
KeyBoardTask::KeyBoardTask(mutex &mutex, ConnectionHandler &connectionHandler, StompMsgEncoderDecoder& encDec1) : _mutex(
        mutex), _connectionHandler(connectionHandler), terminated(false), encDec(encDec1) {}

void KeyBoardTask::run() {
    while (!terminated) {
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
