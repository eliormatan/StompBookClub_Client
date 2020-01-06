//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompMsgEncoderDecoder.h"

using namespace std;

StompMsgEncoderDecoder::StompMsgEncoderDecoder() {            //todo

}

StompMsgEncoderDecoder::~StompMsgEncoderDecoder() {      //todo

}

string StompMsgEncoderDecoder::decodeNextByte(char nextByte) {
    if (nextByte == '\0') {
        pushByte(nextByte);
        return popString();
    }
    pushByte(nextByte);
    return nullptr; //not a full object yet
}

vector<unsigned char> StompMsgEncoderDecoder::encode(string message) {   //todo
//    string bytes = makeItStomp(message);
//     bytes.push_back("/n");
//     bytes.push_back("/0");
//    return vector<char> bytesToSend(output.begin(),output.end());
}

void StompMsgEncoderDecoder::pushByte(char byte) {   //todo
//      if(len >= bytes->size())   {
//          bytes=Arrays.copyOf(bytes,len*2);
//      }
}

string StompMsgEncoderDecoder::popString() {     //todo 

}

vector<unsigned char> StompMsgEncoderDecoder::stringToBytes(string msg) {    //todo
    return vector<unsigned char>();
}
string StompMsgEncoderDecoder::BytesToString(vector<unsigned char> bytes) {           //todo
    return std::__cxx11::string();
}

string StompMsgEncoderDecoder::makeItStomp(string msg) {           //todo
                                          //a lot of switch case
    return std::__cxx11::string();
}
