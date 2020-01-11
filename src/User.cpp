//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include <algorithm>
#include "../include/User.h"


User::User(string _name,string _password):name(_name),password(_password),logOutID(-1),isLoggedOut(false) {
    bookMap = new map<string,vector<Book*>*>();
    subscribeByID = new map<string,int>();
    openRequests = new vector<Requests*>();
    runningID=0;
}

User::~User() {

}

int User::getRunningID() {
    return runningID++;
}

string User::getName() {
    return name;
}

string User::getPassword() {
    return password;
}



void User::addBookToInventory(string bookName, string genre, string borrowedFrom) {
//    Book newBook(bookName,borrowedFrom);
    map<string,vector<Book*>*>::iterator iter = bookMap->find(genre);
    if(iter!=bookMap->end()){
        vector<Book*>* vectorToInsert = iter->second;
        if(!findBook(genre,bookName)) {
            iter->second->insert(iter->second->begin(), new Book(bookName, borrowedFrom));
        }
        else{
            for(Book *book:*vectorToInsert){
                if(book->getName()==bookName) {
                    book->setIsMineAtTheMoment(true);
                    break;
                }
            }
        }
    }
    else{
        vector<Book*>* vectorToInsert = new vector<Book*>();
        vectorToInsert->insert(vectorToInsert->begin(),new Book(bookName,borrowedFrom));
        bookMap->insert(bookMap->begin(),pair<string,vector<Book*>*>(genre,vectorToInsert));
    }
}

string User::removeBookFromInventory(string genre, string bookName) {
    map<string,vector<Book*>*>::iterator iter = bookMap->find(genre);
    if(iter!=bookMap->end()) {
        for (int i = 0; i < iter->second->size(); i++) {
            Book *currBook = iter->second->at(i);
            if (currBook->getName() == bookName & currBook->getIsMineAtTheMoment()) {
                string ownerName = currBook->getBorrowedFrom();
                currBook->setIsMineAtTheMoment(false);
                return ownerName;
            } else {
                return "BookError";
            }
        }

        return "BookError";
    }
}

void User::removeAllSubscribe() {
    for(map<string,vector<Book*>*>::iterator iter=bookMap->begin();iter!=bookMap->end();iter++){
        for(int i=0;i<iter->second->size();i++)
        {
            delete iter->second->at(i);
        }
        delete (iter->second);
    }
}

void User::subscribeWithID(string genre, int subscribeID) {
    subscribeByID->insert(pair<string,int>(genre,subscribeID));
}

void User::getAllBooks(string &books,string genre) {
    books+=name+string(":");
    for(auto genreOfMap:*bookMap){
        if(genreOfMap.first==genre) {
            vector<Book *> *bookvec = genreOfMap.second;
            for (auto book:*bookvec) {
                if(book->getIsMineAtTheMoment()) {
                    books += book->getName() + string(",");
                }
            }
            books = books.substr(0,books.length()-1);
            return;
        }
    }
}

bool User::findBook(string genre, string bookName) {
    map<string, vector<Book *> *>::iterator iter = bookMap->find(genre);
    if (iter != bookMap->end()) {
        for (int i = 0; i < iter->second->size(); i++) {
            if (iter->second->at(i)->getName() == bookName & iter->second->at(i)->getIsMineAtTheMoment()) {
                return true;
            }
        }
        return false;
    }
}

void User::addRequest(Requests *requests) {
    openRequests->push_back(requests);
}

bool User::removeRequest(string bookName, string genre, int subscribeID) {
    for(auto req:*openRequests){
        if(bookName==req->getBookName()&&genre==req->getGenre())
        {
            openRequests->erase(std::find(openRequests->begin(), openRequests->end(), req));
            return true;
        }
    }
    return false;
}

int User::getSubscribeIDbyTopic(string genre) {
    return subscribeByID->find(genre)->second;
}

void User::setLogOutId(int logOutId) {
    logOutID = logOutId;
}

int User::getLogOutId() const {
    return logOutID;
}

bool User::getisLoggedOut() const {
    return isLoggedOut;
}

void User::setIsLoggedOut(bool isLoggedOut) {
    User::isLoggedOut = isLoggedOut;
}

bool User::findRequest(string bookName, string genre, int subscribeID) {
    for(auto req:*openRequests){
        if(bookName==req->getBookName()&&genre==req->getGenre())
        {
            return true;
        }
    }
    return false;

}


