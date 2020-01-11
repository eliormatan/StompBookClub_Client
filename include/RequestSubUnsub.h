//
// Created by tamirsku@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_REQUESTSUBUNSUB_H
#define BOOST_ECHO_CLIENT2_REQUESTSUBUNSUB_H

#include <string>

using namespace std;

class RequestSubUnsub {
public:
    RequestSubUnsub(int _receiptID, int _subID,string _genre,string _type);
    ~RequestSubUnsub();

    int getSubId() const;

    int getReceiptId() const;

    const string &getGenre() const;

private:
    int subID;
    int receiptID;
    string genre;
    string type;
};


#endif //BOOST_ECHO_CLIENT2_REQUESTSUBUNSUB_H
