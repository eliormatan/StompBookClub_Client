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
string decodeNextByte(char nextByte);
vector<unsigned char> encode(string message);

private:
    vector<unsigned char> bytes[1<<10]; //start with 1k
    int len = 0;
    string BytesToString(vector<unsigned char> bytes);
    vector<unsigned char> stringToBytes(string msg);
    void pushByte(char byte);
    string popString();
    string makeItStomp(string msg);
};


#endif //BOOST_ECHO_CLIENT2_STOMPMSGENCODERDECODER_H
