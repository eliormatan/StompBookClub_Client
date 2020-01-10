//
// Created by tamirsku@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/Requests.h"


const string &Requests::getGenre() const {
    return genre;
}

const string &Requests::getBookName() const {
    return bookName;
}

Requests::Requests(string _genre, string _bookName):genre(_genre),bookName(_bookName) {}
