//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//
#include "../include/SplitThings.h"
#include "../include/StompMsgEncoderDecoder.h"
#include "../include/User.h"
#include <vector>

using namespace std;

StompMsgEncoderDecoder::StompMsgEncoderDecoder(User& user1):user(user1) {            //todo
}

StompMsgEncoderDecoder::~StompMsgEncoderDecoder() {      //todo

}


string StompMsgEncoderDecoder::decode(string stomp) {   //todo
    
    return std::__cxx11::string();
}


void StompMsgEncoderDecoder::encode(string msg,string &stomp) {
    vector<string> words;
    SplitThings::splitWords(msg,words);
    string currWord=words[0];
    if(currWord=="join"){
        string genre=words[1];
        int id=user.getRunningID();
        int id2=user.getRunningID();
        stomp="SUBSCRIBE"+string("\n")+
                "destination:"+genre+string("\n")+
                "id:"+to_string(id)+string("\n")+
                "receipt:"+to_string(id2)+string("\n")+"\0";
        user.subscribeWithID(genre,id);
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
        user.addBookToInventory(bookName,genre, nullptr);
        stomp="SEND"+string("\n")+
                "destination:"+genre+string("\n")+
                user.getName()+" has added the book "+bookName+string("\n")+"\0";
    }
    else if(currWord=="borrow"){
        string genre=words[1];
        string bookName=words[2];
        stomp="SEND"+string("\n")+
              "destination:"+genre+string("\n")+
              user.getName()+" wish to borrow "+bookName+string("\n")+"\0";
    }
    else if(currWord=="return"){
        string genre=words[1];
        string bookName=words[2];
        string bookLender=user.removeBookFromInventory(genre,bookName);    //remove book returns the name of the lender
        stomp="SEND"+string("\n")+
                "Returning "+bookName+" to "+bookLender+string("\n")+"\0";
    }
    else if(currWord=="status"){
        string genre=words[1];
        stomp="SEND"+string("\n")+
                "destination:"+genre+string("\n")+
                "book status"+string("\n")+"\0";
    }
    else if(currWord=="logout"){
        int receipt=user.getRunningID();
        user.removeAllSubscribe();
        stomp="DISCONNECT"+string("\n")+
                "receipt:"+to_string(receipt)+string("\n")+"\0";
    }
}
