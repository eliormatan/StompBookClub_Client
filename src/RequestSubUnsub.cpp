//
// Created by tamirsku@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include "../include/RequestSubUnsub.h"

int RequestSubUnsub::getSubId() const {
    return subID;
}

int RequestSubUnsub::getReceiptId() const {
    return receiptID;
}

const string &RequestSubUnsub::getGenre() const {
    return genre;
}

RequestSubUnsub::RequestSubUnsub(int _receiptID, int _subID, string _genre,string _type) {
    receiptID = _receiptID;
    subID = _subID;
    genre = _genre;
    type = _type;
}

RequestSubUnsub::~RequestSubUnsub() {

}
