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

void StompMsgEncoderDecoder::decode(string stomp,string& answer) {
    vector<string> splitedString = split_string(stomp);
    vector<string>::iterator iter = splitedString.begin();
    string first = *iter;
    if(first=="MESSAGE"){

    }
}
}
string StompMsgEncoderDecoder::encode(string msg) {
    return std::__cxx11::string();
}

vector<string> split_string(const string& str)
{
    std::vector<std::string> strings;

    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find('\n', prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;