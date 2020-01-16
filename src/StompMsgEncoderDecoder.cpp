//
// Created by eliorma@wincs.cs.bgu.ac.il on 06/01/2020.
//
#include "../include/SplitThings.h"
#include "../include/StompMsgEncoderDecoder.h"
#include "../include/User.h"
#include <vector>
#include <iostream>
#include <condition_variable>

using namespace std;

StompMsgEncoderDecoder::StompMsgEncoderDecoder(User &user1, ConnectionHandler &_connect) : user(user1),
                                                                                           connect(_connect),
                                                                                           isDone(false),
                                                                                           subFinished(false),
                                                                                           lock1(),
                                                                                           cond() {}


StompMsgEncoderDecoder::~StompMsgEncoderDecoder() {

}


string StompMsgEncoderDecoder::decode(string stomp) {
    // cout<<stomp<<endl;
    vector<string> lines;
    SplitThings::split_string(stomp, lines);
    string readyStomp = "";
    if (lines[0] == "RECEIPT") {
        int receiptID = stoi(lines[1].substr(11));
        if ((receiptID == user.getLogOutId()) & user.getisLoggedOut()) { //Logout
            connect.close();
            cout << "Disconnecting..." << endl;
            readyStomp = "letMeOut!";
        } else {
            RequestSubUnsub *req = user.getReqByRecipt(receiptID);
            if (req->getSubId() == -1) {
                cout << "Exited Club " + req->getGenre() << endl;
                user.increaseUnSub();
                cond.notify_all();
            } else {
                cout << "Joined Club " + req->getGenre() << endl;
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
                         "destination:" + genre + string("\n") + "\n" +
                         allBooks + "\n" + "\0";
        } else {
            vector<string> splited;
            SplitThings::splitWords(lines[5], splited);
            string genre = lines[3].substr(12);
            cout << genre + ":" + lines[5] << endl;
            if (splited[0] == "Returning") {
                if (splited[splited.size()-1] == user.getName()) {
                    string book = SplitThings::getBookName(1, findIndexOfWord(splited, "to") - 1, splited);
                    user.addBookToInventory(book, genre, user.getName());
                }
            } else if (splited.size() >= 4 && splited[3] == "borrow") {
                string book = SplitThings::getBookName(4, splited.size() - 1, splited);
                if (user.findBook(genre, book)) {
                    readyStomp = "SEND" + string("\n") +
                                 "destination:" + genre + string("\n") + string("\n") +
                                 user.getName() + " has " + book + string("\n") + "\0";
                }
            } else if (splited.size() >= 2 && splited[1] == "has") {
                string owner = splited[0];
                string book = SplitThings::getBookName(2, splited.size() - 1, splited);
                int subscribeID = stoi(lines[1].substr(13));
                if (user.findRequest(book, genre, subscribeID)) {
                    readyStomp = "SEND" + string("\n") +
                                 "destination:" + genre + string("\n") + string("\n") +
                                 "Taking " + book + " from " + owner + string("\n") + "\0";
                }
            } else if (splited[0] == "Taking") {
                int namelocation = splited.size()-1;
                if (splited[namelocation] == user.getName()) {
                    string book = SplitThings::getBookName(1, findIndexOfWord(splited, "from") - 1, splited);
                    user.removeBookFromInventory(genre, book);
                } else {
                    string bookName = SplitThings::getBookName(1, findIndexOfWord(splited, "from") - 1, splited);
                    int subscribeID = stoi(lines[1].substr(13));
                    if (user.removeRequest(bookName, genre, subscribeID)) {
                        user.addBookToInventory(bookName, genre, splited[namelocation]);

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
    if (currWord == "login") {
        cout << "Already logged in. If you want to log in to other user, please Log out first." << endl;
        stomp = "";
    } else if (currWord == "join") {
        string genre = words[1];
        int subId = user.getRunningID();
        int recipetID = user.getRunningID();
        onJoin(genre, subId, recipetID, stomp);
    } else if (currWord == "exit") {
        string genre = words[1];
        int UnSubid = user.getSubscribeIDbyTopic(genre);
        int recipetID = user.getRunningID();
        onUnsub(genre, UnSubid,recipetID, stomp);
    } else if (currWord == "add") {
        string genre = words[1];
        string bookName = SplitThings::getBookName(2, words.size() - 1, words);
        user.addBookToInventory(bookName, genre, user.getName());
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") + string("\n") +
                user.getName() + " has added the book " + bookName + string("\n") + "\0";
    } else if (currWord == "borrow") {
        string genre = words[1];
        string bookName = SplitThings::getBookName(2, words.size() - 1, words);
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") + string("\n") +
                user.getName() + " wish to borrow " + bookName + string("\n") + "\0";
        RequestBorrow *request = new RequestBorrow(genre, bookName);
        user.addRequest(request);
    } else if (currWord == "return") {
        string genre = words[1];
        string bookName = SplitThings::getBookName(2, words.size() - 1, words);
        string bookLender = user.removeBookFromInventory(genre,
                                                         bookName);    //remove book returns the name of the lender
        if (bookLender == "BookError") {
            cout << "Book Is Not Yours! :(" << endl;
        } else {
            stomp = "SEND" + string("\n") +
                    "destination:" + genre + string("\n") + string("\n") +
                    "Returning " + bookName + " to " + bookLender + string("\n") + "\0";

        }
    } else if (currWord == "status") {
        string genre = words[1];
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") + string("\n") +
                "book status" + string("\n") + "\0";
    } else if (currWord == "logout") {
        int receipt = user.getRunningID();
        user.setLogOutId(receipt);
        user.setIsLoggedOut(true);
        vector<string> topics;
        user.getAllTopics(topics);
        unsigned int start = user.getTotalUnSub();
        for (auto topic:topics) {
            string exitStomp = "";
            onUnsub(topic, user.getSubscribeIDbyTopic(topic), exitStomp);
            connect.sendLine(exitStomp);
        }
        unique_lock<mutex> cond2{lock1};
        while ((start+topics.size()) != (user.getTotalUnSub())) {
            cond.wait(cond2);
        }
        stomp = "DISCONNECT" + string("\n") +
                "receipt:" + to_string(receipt) + string("\n") + string("\n") + "\0";
        isDone = true;
    }
}

bool StompMsgEncoderDecoder::isDone1() const {
    return isDone;
}

int StompMsgEncoderDecoder::findIndexOfWord(vector<string> &words, string word) {
    int i = 0;
    for (string str:words) {
        if (str == word) {
            return i;
        }
        i++;
    }
    return -1;
}

void StompMsgEncoderDecoder::onUnsub(string genre, int unSubID,int receiptID, string &stomp) {
    stomp = "UNSUBSCRIBE" + string("\n") +
            "id:" + to_string(unSubID) + string("\n")
            +"receipt:"+to_string(receiptID)+ string("\n")+string("\n") + "\0";
    RequestSubUnsub *req = new RequestSubUnsub(receiptID, -1, genre, "unsub");
    user.unsubWithID(genre,unSubID);
    user.insertSubUnsubReq(req);
}

void StompMsgEncoderDecoder::onJoin(string genre, int subID, int recipetID, string &stomp) {
    stomp = "SUBSCRIBE" + string("\n") +
            "destination:" + genre + string("\n") +
            "id:" + to_string(subID) + string("\n") +
            "receipt:" + to_string(recipetID) + string("\n") + string("\n") + "\0";
    user.subscribeWithID(genre, subID);
    RequestSubUnsub *req = new RequestSubUnsub(recipetID, subID, genre, "sub");
    user.insertSubUnsubReq(req);
}

