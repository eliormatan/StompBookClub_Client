//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/User.h"


User::User(string _name,string _password):name(_name),password(_password) {
    bookMap = map<string,vector<Book*>*>();
    subscribeByID = map<string,int>();
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
    Book newBook(bookName,borrowedFrom);
    map<string,vector<Book*>*>::iterator iter = bookMap.find(bookName);
    if(iter!=bookMap.end()){
        iter->second->insert(iter->second->begin(),new Book(bookName,borrowedFrom));
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
//    {
        for(int i=0;i<iter->second->size();i++)
        {
            if(iter->second->at(i)->getName()==bookName)
            {
                string ownerName = iter->second->at(i)->getBorrowedFrom();
                iter->second->erase(iter->second->begin()+i);
            }
        }

    return nullptr;
}

void User::removeAllSubscribe() {
    for(map<string,vector<Book*>*>::iterator iter=bookMap.begin();iter!=bookMap.end();iter++){
        for(int i=0;i<iter->second->size();i++)
        {
            delete iter->second->at(i);
        }
        delete (iter->second);
    }
}

void User::subscribeWithID(string genre, int subscribeID) {
    subscribeByID.insert(pair<string,int>(genre,subscribeID));
}


