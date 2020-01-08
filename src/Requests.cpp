//
// Created by tamirsku@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/Requests.h"

int Requests::getSubscribeId() const {
    return subscribeID;
}

const string &Requests::getGenre() const {
    return genre;
}

const string &Requests::getBookName() const {
    return bookName;
}

Requests::Requests(int _subscribeID, string _genre, string _bookName):subscribeID(_subscribeID),genre(_genre),bookName(_bookName) {}
