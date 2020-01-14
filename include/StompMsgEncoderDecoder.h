//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
#define BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H

#include "User.h"
#include "connectionHandler.h"
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

class StompMsgEncoderDecoder {
public:
StompMsgEncoderDecoder(User& user1,ConnectionHandler& _connect);
~StompMsgEncoderDecoder();
string decode(string stomp);    //decode stomp frame to stomp frame response
void encode(string msg,string &stomp);
void onUnsub(string genre,int unSubID,string& stomp);
void onJoin(string genre,int subID,int recipetID,string& stomp);
bool isDone1() const;
int findIndexOfWord(vector<string>& words,string word);

private:
    User& user;
    ConnectionHandler& connect;
    bool isDone;
    bool subFinished;
    mutex lock1;
    condition_variable cond;
};


#endif //BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
