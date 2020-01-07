//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompMsgEncoderDecoder.h"

using namespace std;

StompMsgEncoderDecoder::StompMsgEncoderDecoder() {            //todo

}

StompMsgEncoderDecoder::~StompMsgEncoderDecoder() {      //todo

}

string StompMsgEncoderDecoder::splitWords(string line) {
    vector<string> splitWords(string line){
        vector <string> words;
        string word;
        for(unsigned int i=0;i<line.size();i++){
            if(line[i] == ' '){
                words.push_back(word);
                word = "";
            }
            else{
                word += line[i];
            }
        }
        words.push_back(word);
        return words;
    }
}

string StompMsgEncoderDecoder::decode(string stomp) {
    return std::__cxx11::string();
}

string StompMsgEncoderDecoder::encode(string msg) {
    return std::__cxx11::string();
}
