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
        if (stoi(lines[1].substr(11)) == user.getLogOutId() & user.getisLoggedOut()) {
            connect.close();
            cout << "Disconnecting..." << endl;
            readyStomp = "letMeOut!";
        }
    } else if (lines[0] == "MESSAGE") {
        if (lines[4] == "book status") {
            string genre = lines[3].substr(12);
            cout << genre + ":book status" << endl;
            string allBooks;
            user.getAllBooks(allBooks, genre);
            readyStomp = "SEND" + string("\n") +
                         "destination:" + genre + string("\n") +
                         allBooks + "\n" + "\0";
        } else {
            vector<string> splited;
            SplitThings::splitWords(lines[4], splited);
            string genre = lines[3].substr(12);
            cout << genre + ":" + lines[4] << endl;
            if (splited[0] == "Returning") {
                if (splited[3] == user.getName()) {
                    user.addBookToInventory(splited[1], genre, user.getName());
                }
            } else if (splited.size() >= 4 && splited[3] == "borrow") {
                string book = splited[4];
                if (user.findBook(genre, book)) {
                    readyStomp = "SEND" + string("\n") +
                                 "destination:" + genre + string("\n") +
                                 user.getName() + " has " + book + string("\n") + "\0";
                }
            } else if (splited.size() >= 2 && splited[1] == "has") {
                string owner = splited[0];
                string book = splited[2];
                int subscribeID = stoi(lines[1].substr(13));
                if (user.findRequest(book, genre, subscribeID)) {
                    readyStomp = "SEND" + string("\n") +
                                 "destination:" + genre + string("\n") +
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
    if (currWord == "join") {
        string genre = words[1];
        int id = user.getRunningID();
        int id2 = user.getRunningID();
        stomp = "SUBSCRIBE" + string("\n") +
                "destination:" + genre + string("\n") +
                "id:" + to_string(id) + string("\n") +
                "receipt:" + to_string(id2) + string("\n") + "\0";
        user.subscribeWithID(genre, id);
        cout << "Joined club " + genre << endl;
    } else if (currWord == "exit") {
        string genre = words[1];
        int id = user.getSubscribeIDbyTopic(genre);
        stomp = "UNSUBSCRIBE" + string("\n") +
                "id:" + to_string(id) + string("\n") + "\0";
        cout << "Exited club " + genre << endl;
    } else if (currWord == "add") {
        string genre = words[1];
        string bookName = words[2];
        user.addBookToInventory(bookName, genre, user.getName());
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") +
                user.getName() + " has added the book " + bookName + string("\n") + "\0";
    } else if (currWord == "borrow") {
        string genre = words[1];
        string bookName = words[2];
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") +
                user.getName() + " wish to borrow " + bookName + string("\n") + "\0";
        Requests *request = new Requests(genre, bookName);
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
                    "destination:" + genre + string("\n") +
                    "Returning " + bookName + " to " + bookLender + string("\n") + "\0";

        }
    } else if (currWord == "status") {
        string genre = words[1];
        stomp = "SEND" + string("\n") +
                "destination:" + genre + string("\n") +
                "book status" + string("\n") + "\0";
    } else if (currWord == "logout") {
        int receipt = user.getRunningID();
        user.setLogOutId(receipt);
        user.setIsLoggedOut(true);
        user.removeAllSubscribe();
        stomp = "DISCONNECT" + string("\n") +
                "receipt:" + to_string(receipt) + string("\n") + "\0";
        isDone = true;
    }
}

bool StompMsgEncoderDecoder::isDone1() const {
    return isDone;
}
