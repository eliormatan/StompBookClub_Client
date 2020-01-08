//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/User.h"


User::User(string _name,string _password):name(_name),password(_password) {
    bookMap = map<string,vector<Book*>*>();
    subscribeByID = map<string,int>();

}

User::~User() {
//    delete bookMap;
//    delete subscribeByID;
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
    Book newBook(bookName,borrowedFrom);
    map<string,vector<Book*>>::iterator iter = bookMap.find(bookName);
    if(iter!=bookMap.end()){
        iter->second.insert(iter->second.begin(),new Book(bookName,borrowedFrom));
    }
    else{
        vector<Book*>* vectorToInsert = new vector<Book*>();
        vectorToInsert->insert(vectorToInsert->begin(),new Book(bookName,borrowedFrom));
        bookMap.insert(bookMap.begin(),pair<string,vector<Book*>*>(genre,vectorToInsert));
    }
}

string User::removeBookFromInventory(string genre, string bookName) {
    map<string,vector<Book*>*>::iterator iter = bookMap.find(genre);
    if(iter!=bookMap.end())
    {
        for(vector<Book*>::iterator b=iter->second->begin();b<iter->second->end();b++){
            if(b->getName()==bookName){
                string borrowerName =  b->getBorrowedFrom();
                iter->second->erase(b);
            }
        }
    }
    return nullptr;
}

void User::removeAllSubscribe() {

}

