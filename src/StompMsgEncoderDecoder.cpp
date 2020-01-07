//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//

#include "../include/StompMsgEncoderDecoder.h"
#include "../include/User.h"
#include <vector>

using namespace std;

StompMsgEncoderDecoder::StompMsgEncoderDecoder(){            //todo
    user=user.getIntance();
}

StompMsgEncoderDecoder::~StompMsgEncoderDecoder() {      //todo

}

void StompMsgEncoderDecoder::splitWords(string line,vector<string>& words) {
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
}

string StompMsgEncoderDecoder::decode(string stomp) {   //todo
    return std::__cxx11::string();
}

void StompMsgEncoderDecoder::encode(string msg,string &stomp) { //todo
    vector<string> words;
    splitWords(msg,words);
    string currWord=words[0];
    if(currWord=="login"){
        int seperate=words[1].find(':');
        string host=words[1].substr(0,seperate);
        string port=words[1].substr(seperate+1,words[1].length()-1);
        string username=words[2];
        string password=words[3];
        stomp="CONNECT"+string("\n")+
               "accept-version:1.2"+string("\n")+
               "host:stomp.cs.bgu.ac.il"+string("\n")+
               "login:"+username+string("\n")+
                "passcode:"+password+string("\n")+"\0";
    }
    else if(currWord=="join"){
        string genre=words[1];
        int id=user.getRunningID();
        stomp="SUBSCRIBE"+string("\n")+
                "destination:"+genre+string("\n")+
                "id:"+to_string(id)+string("\n")+
                "receipt:"+to_string(id)+string("\n")+"\0";
    }
    else if(currWord=="exit"){
        string genre=words[1];
        int id=user.getRunningID();
        stomp="UNSUBSCRIBE"+string("\n")+
                "id:"+to_string(id)+string("\n")+"\0";
    }
    else if(currWord=="add"){
        string genre=words[1];
        string bookName=words[2];
        stomp="SEND"+string("\n")+
                ""
    }
    else if(currWord=="borrow"){

    }
    else if(currWord=="return"){

    }
    else if(currWord=="status"){

    }
    else if(currWord=="logout"){

    }

}
