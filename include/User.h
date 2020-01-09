//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_USER_H
#define BOOST_ECHO_CLIENT2_USER_H

#include <map>
#include <vector>
#include "Book.h"
#include "Requests.h"

using namespace std;

class User {
private:
    map<string,vector<Book*>*>* bookMap;
    map<string,int>* subscribeByID;
    vector<Requests *>* openRequests;
    int runningID;
    int logOutID;
private:
    string name;
    string password;
    bool isLoggedOut;
public:
    User(string name,string password);
    ~User();
    string removeBookFromInventory(string genre,string bookName); //return the bookOwner
    void addBookToInventory(string bookName,string genre,string borrowedFrom); //
    void removeAllSubscribe();
    void subscribeWithID(string genre,int subscribeID);
    void getAllBooks(string& books,string genre);
    void addRequest(Requests* requests);
    void setLogOutId(int logOutId);
    void setIsLoggedOut(bool isLoggedOut);
    int getRunningID();
    int getSubscribeIDbyTopic(string genre);
    bool removeRequest(string bookName,string genre,int subscribeID);
    bool findBook(string genre,string bookName);
    string getName();
    string getPassword();
    int getLogOutId() const;
    bool getisLoggedOut() const;

};


#endif //BOOST_ECHO_CLIENT2_USER_H
