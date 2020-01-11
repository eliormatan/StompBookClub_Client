//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_KEYBOARDTASK_H
#define BOOST_ECHO_CLIENT2_KEYBOARDTASK_H


#include <mutex>
#include "StompMsgEncoderDecoder.h"
#include "connectionHandler.h"
using namespace std;

class KeyBoardTask {
private:
    mutex &_mutex;
    ConnectionHandler &_connectionHandler;
    StompMsgEncoderDecoder encDec;
    bool terminated;
public:
    KeyBoardTask(mutex& mutex,ConnectionHandler& connectionHandler,StompMsgEncoderDecoder& encDec1);
    void run();
};


#endif //BOOST_ECHO_CLIENT2_KEYBOARDTASK_H
