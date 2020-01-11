//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_USER_H
#define BOOST_ECHO_CLIENT2_USER_H

#include <map>
#include <vector>
#include "Book.h"
#include "RequestBorrow.h"
#include "RequestSubUnsub.h"

using namespace std;

class User {
private:
    map<string,vector<Book*>*>* bookMap;
    map<string,int>* subscribeByID;
    vector<RequestBorrow *>* openRequests;
    vector<RequestSubUnsub*>* openSubUnSubReq;
    int runningID;
    int logOutID;
    string name;
    string password;
    bool isLoggedOut;
public:
    User(string name,string password);
    User(const User &other);
    ~User();
    User& operator=(const User &other);
    void copy(const User &other);
    void addBookToInventory(string bookName,string genre,string borrowedFrom); //
    void removeAllSubscribe();
    void subscribeWithID(string genre,int subscribeID);
    void getAllBooks(string& books,string genre);
    void addRequest(RequestBorrow* requests);
    void setLogOutId(int logOutId);
    void setIsLoggedOut(bool isLoggedOut);
    void insertSubUnsubReq(RequestSubUnsub* req);
    void clean();
    int getRunningID();
    int getLogOutId() const;
    int getSubscribeIDbyTopic(string genre);
    bool removeRequest(string bookName,string genre,int subscribeID);
    bool findBook(string genre,string bookName);
    bool findInInventory(string genre,string bookName);
    bool findRequest(string bookName,string genre,int subscribeID);
    bool getisLoggedOut() const;
    RequestSubUnsub* getReqByRecipt(int receiptID);
    string getName();
    string removeBookFromInventory(string genre,string bookName); //return the bookOwner

};


#endif //BOOST_ECHO_CLIENT2_USER_H
