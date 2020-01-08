//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
#define BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H

#include "User.h"
#include <string>
#include <vector>

using namespace std;

class StompMsgEncoderDecoder {
public:
StompMsgEncoderDecoder(User& user1);
~StompMsgEncoderDecoder();
string decode(string stomp);    //decode stomp frame to string
void encode(string msg,string &stomp);      //encode string to stomp frame
private:
    User user;
};


#endif //BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
