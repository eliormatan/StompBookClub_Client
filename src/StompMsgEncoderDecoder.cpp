//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//
#include "../include/SplitThings.h"
#include "../include/StompMsgEncoderDecoder.h"
#include "../include/User.h"
#include <vector>
#include <iostream>

using namespace std;

StompMsgEncoderDecoder::StompMsgEncoderDecoder(User &user1, ConnectionHandler &_connect) : user(user1),
                                                                                           connect(_connect),
                                                                                           isDone(false){}          //todo}

StompMsgEncoderDecoder::~StompMsgEncoderDecoder() {

}


string StompMsgEncoderDecoder::decode(string stomp) {   //todo
    // cout<<stomp<<endl;
    vector<string> lines;
    SplitThings::split_string(stomp, lines);
    string readyStomp = "";
    if (lines[0] == "RECEIPT") {
        int receiptID =  stoi(lines[1].substr(11));
        if (receiptID == user.getLogOutId() & user.getisLoggedOut()) { //Logout
            connect.close();
            cout << "Disconnecting..." << endl;
            readyStomp = "letMeOut!";
        }
        else{
            RequestSubUnsub* req = user.getReqByRecipt(receiptID);
            if(req->getSubId() == -1){
                cout<< "Exited Club "+req->getGenre()<<endl;
            }
            else{
                cout<<"Joined Club "+req->getGenre()<<endl;
            }
            delete req;

        }
    } else if (lines[0] == "MESSAGE") {
        if (lines[5] == "book status") {
            string genre = lines[3].substr(12);
            cout << genre + ":book status" << endl;
            string allBooks;
            user.getAllBooks(allBooks, genre);
            readyStomp = "SEND" + string("\n") +
                         "destination:" + genre + string("\n") + "\n"+
                         allBooks + "\n" + "\0";
        } else {
            vector<string> splited;
            SplitThings::splitWords(lines[5], splited);
            string genre = lines[3].substr(12);
            cout << genre + ":" + lines[5] << endl;
            if (splited[0] == "Returning") {
                if (splited[3] == user.getName()) {
                    user.addBookToInventory(splited[1], genre, user.getName());
                }
            } else if (splited.size() >= 4 && splited[3] == "borrow") {
                string book = splited[4];
                if (user.findBook(genre, book)) {
                    readyStomp = "SEND" + string("\n") +
                                 "destination:" + genre + string("\n") +string("\n")+
                                 user.getName() + " has " + book + string("\n") + "\0";
                }
            } else if (splited.size() >= 2 && splited[1] == "has") {
                string owner = splited[0];
                string book = splited[2];
                int subscribeID = stoi(lines[1].substr(13));
                if (user.findRequest(book, genre, subscribeID)) {
                    readyStomp = "SEND" + string("\n") +
                                 "destination:" + genre + string("\n") + string("\n")+
                                 "Taking " + book + " from " + owner + string("\n") + "\0";
                }
            } else if (splited[0] == "Taking") {
                if (splited[3] == user.getName()) {
                    user.removeBookFromInventory(genre, splited[1]);
                } else {
                    string bookname = splited[1];
                    int subscribeID = stoi(lines[1].substr(13));
                    if (user.removeRequest(bookname, genre, subscribeID)) {
                        user.addBookToInventory(bookname, genre, splited[3]);

                    }
                }
            }
        }
    }
    return readyStomp;
}


void StompMsgEncoderDecoder::encode(string msg, string &stomp) {
    vector<string> words;
    SplitThings::splitWords(msg, words);
    string currWord = words[0];
    if(currWord == "login"){
        cout << "Already logged in. If you want to log in to other user, please Log out first." << endl;
        stomp ="";
    }
    else if (currWord == "join") {
        string genre = words[1];
        int id = user.getRunningID();
        int id2 = user.getRunningID();
        stomp = "SUBSCRIBE" + string("\n") +
                "destination:" + genre + string("\n") +
                "id:" + to_string(id) + string("\n") +
                "receipt:" + to_string(id2) + string("\n") + string("\n")+ "\0";
        user.subscribeWithID(genre, id);
        RequestSubUnsub* req = new RequestSubUnsub(id2,id,genre,"sub");
        user.insertSubUnsubReq(req);
    } else if (currWord == "exit") {
        string genre = words[1];
        int id = user.getSubscribeIDbyTopic(genre);
        stomp = "UNSUBSCRIBE" + string("\n") +
                "id:" + to_string(id) + string("\n") +string("\n") + "\0";
        RequestSubUnsub* req = new RequestSubUnsub(id,-1,genre,"unsub");
        user.insertSubUnsubReq(req);

    } else if (currWord == "add") {
        string genre = words[1];
        string bookName = words[2];
        user.addBookToInventory(bookName, genre, user.getName());
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") + string("\n")+
                user.getName() + " has added the book " + bookName + string("\n") + "\0";
    } else if (currWord == "borrow") {
        string genre = words[1];
        string bookName = words[2];
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") + string("\n")+
                user.getName() + " wish to borrow " + bookName + string("\n") + "\0";
        RequestBorrow *request = new RequestBorrow(genre, bookName);
        user.addRequest(request);
    } else if (currWord == "return") {
        string genre = words[1];
        string bookName = words[2];
        string bookLender = user.removeBookFromInventory(genre,
                                                         bookName);    //remove book returns the name of the lender
        if (bookLender == "BookError") {
            cout << "Book Is Not Yours! :(" << endl;
        } else {
            stomp = "SEND" + string("\n") +
                    "destination:" + genre + string("\n") + string("\n")+
                    "Returning " + bookName + " to " + bookLender + string("\n") + "\0";

        }
    } else if (currWord == "status") {
        string genre = words[1];
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") + string("\n")+
                "book status" + string("\n") + "\0";
    } else if (currWord == "logout") {
        int receipt = user.getRunningID();
        user.setLogOutId(receipt);
        user.setIsLoggedOut(true);
        stomp = "DISCONNECT" + string("\n") +
                "receipt:" + to_string(receipt) + string("\n") +string("\n")+ "\0";
        isDone = true;
    }
}

bool StompMsgEncoderDecoder::isDone1() const {
    return isDone;
}
