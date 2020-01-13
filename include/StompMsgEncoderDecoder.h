//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
#define BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H

#include "User.h"
#include "connectionHandler.h"
#include <string>
#include <vector>

using namespace std;

class StompMsgEncoderDecoder {
public:
StompMsgEncoderDecoder(User& user1,ConnectionHandler& _connect);
~StompMsgEncoderDecoder();
string decode(string stomp);    //decode stomp frame to stomp frame response
void encode(string msg,string &stomp);
bool isDone1() const;
int findIndexOfWord(vector<string>& words,string word);
private:
    User& user;
    ConnectionHandler& connect;
    bool isDone;
};


#endif //BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
