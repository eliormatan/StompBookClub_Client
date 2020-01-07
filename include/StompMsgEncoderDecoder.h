//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
#define BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H

#include <string>
#include <vector>

using namespace std;

class StompMsgEncoderDecoder {//todo
public:
StompMsgEncoderDecoder();
~StompMsgEncoderDecoder();
string decode(string stomp);    //decode stomp frame to string
void encode(string msg,string &stomp);      //encode string to stomp frame
void splitWords(string line,vector<string> & words);

private:
    User user;
};


#endif //BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
