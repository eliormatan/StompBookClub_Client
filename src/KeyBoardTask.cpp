//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//
#include "../include/KeyBoardTask.h"

KeyBoardTask::KeyBoardTask(ConnectionHandler &connectionHandler, StompMsgEncoderDecoder &encDec1)
        : _connectionHandler(connectionHandler),encDec(encDec1), terminated(false)  {}

void KeyBoardTask::run() {
    while (!terminated) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        string frameToSend;
        encDec.encode(line, frameToSend);
        if (frameToSend != "") {
            if (!_connectionHandler.sendLine(frameToSend)) {
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                terminated = true;
            }
            if (encDec.isDone1())
                terminated = true;
        }
    }

}
