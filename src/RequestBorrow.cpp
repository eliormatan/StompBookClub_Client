//
// Created by tamirsku@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/RequestBorrow.h"


const string &RequestBorrow::getGenre() const {
    return genre;
}

const string &RequestBorrow::getBookName() const {
    return bookName;
}

RequestBorrow::RequestBorrow(string _genre, string _bookName): genre(_genre), bookName(_bookName),handled(false) {}

bool RequestBorrow::isHandled() const {
    return handled;
}

RequestBorrow::~RequestBorrow() {

}

void RequestBorrow::setHandled(bool handled) {
    RequestBorrow::handled = handled;
}
