//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/Book.h"

Book::Book(string _name, string _borrowedFrom): name(_name),borrowedFrom(_borrowedFrom) {}

Book::~Book() {
    name = nullptr;
    borrowedFrom = nullptr;
}

string Book::toString() {
    return name;
}

string Book::getBorrowedFrom() {
    return borrowedFrom;
}

const string &Book::getName() const {
    return name;
}

