//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/User.h"

string User::getBooksByGenre(string genre) {
    return std::__cxx11::string();
}

User::User() {
    bookMap = map<string,vector<Book>>();
    subscribeByID = map<string,int>();

}

User::~User() {
//    delete bookMap;
//    delete subscribeByID;
}

User *User::getInstance() {
    return this;
}

int User::getrunningID() {
    return runningID++;
}
